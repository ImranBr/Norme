/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:59:41 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/22 22:33:04 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

pid_t	g_heredoc_interrupted = 0;

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
}

void	read_heredoc_lines(int fd_input, char *delimiter)
{
	char	*line;
	int		line_number;

	line_number = 1;
	while (!g_heredoc_interrupted)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			printf("minishell: warning: here-document");
			printf(" line %d delimited by end-of-file", line_number);
			printf(" (wanted `%s')\n", delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			printf("HERE\n");
			free(line);
			break ;
		}
		if (write(fd_input, line, strlen(line)) == -1 || write(fd_input, "\n",
				1) == -1)
		{
			perror("write");
			free(line);
			close(fd_input);
			exit(EXIT_FAILURE);
		}
		free(line);
		line_number++;
	}
}

void	process_heredoc(t_ast_node *heredoc_node, t_env *env_list,
		t_token **token, char *input, t_ast_node *node)
{
	char	rand_name[33];
	int		fd_input;
	pid_t	pid_heredoc;
	int		status;

	if (!heredoc_node)
	{
		fprintf(stderr, "Erreur: heredoc_node est NULL\n");
		return ;
	}
	create_rand(rand_name);
	heredoc_node->heredoc_tmpfile = ft_strdup(rand_name);
	// allocation dynamique
	if (!heredoc_node->heredoc_tmpfile)
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	g_heredoc_interrupted = 0;
	pid_heredoc = fork();
	if (pid_heredoc == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid_heredoc == 0)
	{
		signal(SIGINT, sigint_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
		fd_input = open(rand_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_input == -1)
		{
			perror(rand_name);
			free_in_child(env_list, heredoc_node, NULL);
			free_tokens(token);
			free(input);
			exit(EXIT_FAILURE);
		}
		read_heredoc_lines(fd_input, heredoc_node->filename);
		// filename contient le délimiteur
		close(fd_input);
		free_in_child(env_list, node, NULL);
		free_tokens(token);
		free(input);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN); // Ignore SIGINT pendant attente
		waitpid(pid_heredoc, &status, 0);
		signal(SIGINT, check_signal);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			unlink(rand_name);
			free(heredoc_node->heredoc_tmpfile);
			heredoc_node->heredoc_tmpfile = NULL;
		}
	}
}

void	preprocess_all_heredocs(t_ast_node *node, t_env *env_list,
		t_token **token, char *input)
{
	t_ast_node	*tmp;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND && node->redirections)
	{
		tmp = node->redirections;
		while (tmp)
		{
			if (tmp->redir_type == HEREDOC)
				process_heredoc(tmp, env_list, token, input, node);
			tmp = tmp->right;
		}
	}
	preprocess_all_heredocs(node->left, env_list, token, input);
	preprocess_all_heredocs(node->right, env_list, token, input);
}

int	no_cmd_process_redirect_in(t_ast_node *redirect_in_node)
{
	int	fd_input;

	fd_input = open(redirect_in_node->filename, O_RDONLY);
	if (fd_input == -1)
	{
		perror("open");
		return (-1);
	}
	close(fd_input);
	return (0);
}
