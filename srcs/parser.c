/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:33:48 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/22 22:34:57 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_args_to_cmd(t_ast_node *cmd, char *arg)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (cmd->args_count + 2));
	if (!tmp)
		return (0);
	while (i < cmd->args_count)
	{
		tmp[i] = cmd->args[i];
		i++;
	}
	tmp[cmd->args_count] = arg;
	tmp[cmd->args_count + 1] = NULL;
	free(cmd->args);
	cmd->args = tmp;
	cmd->args_count++;
	return (1);
}

void	add_redir_to_cmd(t_ast_node *cmd, t_ast_node *redir)
{
	t_ast_node	*current;

	if (!cmd || !redir)
		return ;
	if (!cmd->redirections)
		cmd->redirections = redir;
	else
	{
		current = cmd->redirections;
		while (current->right)
			current = current->right;
		current->right = redir;
	}
}

t_ast_node	*parse_command(t_token **token_list, t_ast_node *cmd)
{
	t_ast_node	*redir;
	char		*tmp1;

	if (!token_list || !*token_list)
		return (NULL);
	while (*token_list && (*token_list)->type != PIPE
		&& (*token_list)->type != EOF_TOKEN)
	{
		if ((*token_list)->type == WORD)
		{
			if (!cmd)
				cmd = create_ast_node(NODE_COMMAND);
			tmp1 = ft_strdup((*token_list)->value);
			add_args_to_cmd(cmd, tmp1);
		}
		else if ((*token_list)->type == 2 || (*token_list)->type == 3
			|| (*token_list)->type == 4 || (*token_list)->type == 5)
		{
			if (!cmd)
				cmd = create_ast_node(NODE_COMMAND);
			redir = create_redir_node(cmd, *token_list);
			if (redir)
			{
				add_redir_to_cmd(cmd, redir);
				*token_list = (*token_list)->next;
			}
			else
				return (NULL);
		}
		*token_list = (*token_list)->next;
	}
	return (cmd);
}

t_ast_node	*handle_pipe_sequence(t_token **token_list, t_ast_node *left)
{
	t_ast_node	*right;
	t_ast_node	*node_pipe;

	*token_list = (*token_list)->next;
	right = parse_command(token_list, NULL);
	if (!right)
	{
		write(STDERR_FILENO, "syntax error\n", 13);
		free_ast(left);
		return (NULL);
	}
	node_pipe = create_ast_node(NODE_PIPE);
	node_pipe->left = left;
	node_pipe->right = right;
	return (node_pipe);
}

t_ast_node	*parse_pipeline(t_token **token_list)
{
	t_ast_node	*left;

	if (*token_list && (*token_list)->type == PIPE)
	{
		write(STDERR_FILENO,
			"minishell: syntax error near unexpected token `|'\n", 50);
		return (NULL);
	}
	left = parse_command(token_list, NULL);
	if (!left)
		return (NULL);
	while (*token_list && (*token_list)->type == PIPE)
	{
		left = handle_pipe_sequence(token_list, left);
		if (!left)
			return (NULL);
	}
	if (*token_list && (*token_list)->type == EOF_TOKEN)
		*token_list = (*token_list)->next;
	return (left);
}
