/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:15:42 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/22 21:19:16 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <stdio.h> // pour perror
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	free_in_child(t_env *env_list, t_ast_node *node, char *path)
{
	free_list(env_list);
	free_ast(node);
	if (path)
		free(path);
}

char	**get_path(t_env *env_list)
{
	char	*path_name;
	char	**tab;

	path_name = "PATH";
	tab = NULL;
	while (env_list)
	{
		if (env_list->name && ft_strcmp(env_list->name, path_name) == 0)
		{
			if (env_list->value)
				tab = ft_split(env_list->value, ':');
			return (tab);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_cmd(t_env *env_list, char *s1)
{
	int		i;
	char	**str;
	char	*pathname;

	i = 0;
	if (!s1 || s1[0] == '\0')
		return (ft_putendl_fd("Command not found", STDERR_FILENO), NULL);
	if (ft_strchr(s1, '/'))
	{
		if (access(s1, F_OK | X_OK) == 0)
			return (ft_strdup(s1));
		return (perror(s1), NULL);
	}
	str = get_path(env_list);
	if (!str)
		return (perror("PATH not found"), NULL);
	while (str[i])
	{
		pathname = ft_strjoin2(str[i], s1);
		if (pathname && access(pathname, F_OK | X_OK) == 0)
			return (free_split(str), pathname);
		free(pathname);
		i++;
	}
	return (free_split(str), perror(s1), NULL);
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	needs_child_process(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0);
}

void	cleanup_heredocs(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->redir_type == HEREDOC && node->heredoc_tmpfile)
	{
		unlink(node->heredoc_tmpfile);
		free(node->heredoc_tmpfile);
		node->heredoc_tmpfile = NULL;
	}
	cleanup_heredocs(node->left);
	cleanup_heredocs(node->right);
	cleanup_heredocs(node->redirections);
}

int	execute_ast(t_ast_node *node, char **envp, t_env *env_list, t_token *token,
		char *input, t_ast_node *first_node, bool is_pipe)
{
	pid_t	pid_left;
	pid_t	pid_right;
	pid_t	pid_cmd;
	int		pipe_fd[2];
	char	*path;
	int		status;
	int		sig;

	path = NULL;
	if (node->type == NODE_PIPE)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (EXIT_FAILURE);
		}
		pid_left = fork();
		if (pid_left == -1)
		{
			perror("fork");
			return (EXIT_FAILURE);
		}
		if (pid_left == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			execute_ast(node->left, envp, env_list, token, input, first_node,
				true);
			free_in_child(env_list, first_node, path);
			free(input);
			free_tokens(&token);
			exit(EXIT_FAILURE);
		}
		pid_right = fork();
		if (pid_right == -1)
		{
			perror("fork");
			return (EXIT_FAILURE);
		}
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (pid_right == 0)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			execute_ast(node->right, envp, env_list, token, input, first_node,
				true);
			free_in_child(env_list, first_node, path);
			free(input);
			free_tokens(&token);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(pid_left, NULL, 0);
		waitpid(pid_right, NULL, 0);
	}
	else if (node->type == NODE_COMMAND)
	{
		if ((!node->args || !node->args[0]) && node->redirections)
		{
			no_cmd_process_redirections(node->redirections);
			return (0);
		}
		if (node->args && node->args[0] && is_builtin(node->args[0])
			&& !needs_child_process(node->args[0]))
		{
			exec_builtin(node, env_list, NULL, token, input);
			cleanup_heredocs(node->redirections);
			return (0);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (!is_pipe)
			pid_cmd = fork();
		if (!is_pipe && pid_cmd == -1)
		{
			perror("fork");
			return (EXIT_FAILURE);
		}
		if (is_pipe || pid_cmd == 0)
		{
			process_redirections(node->redirections);
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (node->args && node->args[0] && is_builtin(node->args[0])
				&& needs_child_process(node->args[0]))
			{
				exec_builtin(node, env_list, NULL, token, input);
				free_in_child(env_list, first_node, path);
				free_tokens(&token);
				free(input);
				exit(0);
			}
			path = get_cmd(env_list, node->args[0]);
			if (!path)
			{
				ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
				ft_putendl_fd(node->args[0], STDERR_FILENO);
				free_in_child(env_list, first_node, NULL);
				free_tokens(&token);
				free(input);
				exit(127);
			}
			execve(path, node->args, envp);
			free_in_child(env_list, first_node, path);
			perror("execve");
			free_tokens(&token);
			free(input);
			exit(EXIT_FAILURE);
		}
		else if (!is_pipe)
			waitpid(pid_cmd, &status, 0);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
				ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
			else if (sig == SIGINT)
				ft_putchar_fd('\n', STDERR_FILENO);
		}
		cleanup_heredocs(node->redirections);
	}
	return (0);
}
