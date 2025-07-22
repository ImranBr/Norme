/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:44:21 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/22 22:29:15 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

pid_t	g_signal_pid = 0;

void	check_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*readline_stderr(const char *prompt)
{
	int		saved_stdout;
	int		devnull;
	char	*line;

	saved_stdout = dup(STDOUT_FILENO);
	devnull = open("/dev/null", O_WRONLY);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	line = readline(prompt);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(devnull);
	return (line);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	create_rand(char *str)
{
	int		fd;
	int		len;
	char	buff[64 + 1];
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return ;
	len = 0;
	while (len < 32)
	{
		buff[read(fd, buff, 64)] = 0;
		i = 0;
		while (buff[i] && len < 32)
		{
			if (ft_isalnum(buff[i]))
			{
				str[len] = buff[i];
				++len;
			}
			++i;
		}
	}
	str[len] = 0;
	close(fd);
}

void	get_rand(void)
{
	char	rand[32 + 1];

	create_rand(rand);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	char		*expanded;
	t_env		*env_list;
	int			exit_status;
	t_token		*tokens;
	t_token		*tokens_head;
	t_ast_node	*ast;

	(void)ac;
	(void)av;
	env_list = create_env_list(envp);
	exit_status = 0;
	while (1)
	{
		input = NULL;
		expanded = NULL;
		tokens = NULL;
		tokens_head = NULL;
		ast = NULL;
		signal(SIGINT, check_signal);
		signal(SIGQUIT, SIG_IGN);
		input = readline_stderr("minishell : ");
		if (!input)
			break ;
		add_history(input);
		if (is_quote_closed(input) != 0)
		{
			free(input);
			continue ;
		}
		expanded = expand_variables(input, env_list, exit_status);
		free(input);
		input = expanded;
		tokens = tokenize(input, 0);
		if (!tokens)
		{
			ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
			free(input);
			continue ;
		}
		tokens_head = tokens;
		ast = parse_pipeline(&tokens);
		if (!ast)
		{
			cleanup_shell(tokens_head, ast, input);
			continue ;
		}
		preprocess_all_heredocs(ast, env_list, &tokens_head, input);
		execute_ast(ast, envp, env_list, tokens_head, input, ast, false);
		cleanup_heredocs(ast);
		cleanup_shell(tokens_head, ast, input);
	}
	cleanup_shell(tokens_head, ast, input);
	clear_history();
	rl_clear_history();
	free_list(env_list);
	return (0);
}
