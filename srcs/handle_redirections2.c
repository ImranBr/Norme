/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:36:05 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/07/22 22:30:37 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*process_redirections(t_ast_node *redir_list)
{
	t_ast_node	*current_node;

	current_node = redir_list;
	while (current_node)
	{
		if (current_node->redir_type == HEREDOC)
			process_redirect_in(current_node);
		else if (current_node->redir_type == REDIRECT_IN)
			process_redirect_in(current_node);
		else if (current_node->redir_type == REDIRECT_OUT)
			process_redirect_out(current_node);
		else if (current_node->redir_type == APPEND)
			process_append(current_node);
		current_node = current_node->right;
	}
	return (NULL);
}

void	process_append(t_ast_node *append_node)
{
	int	fd_output;

	fd_output = open(append_node->filename, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (fd_output == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_output, 1);
	close(fd_output);
}

int	process_redirect_out(t_ast_node *redirect_out_node)
{
	int	fd_output;

	fd_output = open(redirect_out_node->filename, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (fd_output == -1)
	{
		perror(redirect_out_node->filename);
		return (-1);
	}
	if (dup2(fd_output, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd_output);
		return (-1);
	}
	close(fd_output);
	return (0);
}

void	no_cmd_process_append(t_ast_node *append_node)
{
	int	fd_output;

	fd_output = open(append_node->filename, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (fd_output == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	close(fd_output);
}
