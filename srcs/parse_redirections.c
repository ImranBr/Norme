/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joudafke <joudafke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:11:31 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/20 17:43:59 by joudafke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	handle_input_redirections(char *input, t_token **token_list, int i)
{
	if (input[i + 1] == '<')
	{
		if (input[i + 2] == '<' || input[i + 2] == '>')
		{
			printf("syntax error near unexpected token '%c'\n", input[i + 2]);
			return (-1);
		}
		add_token(token_list, create_token(HEREDOC, "<<"));
		return (i + 1);
	}
	else
	{
		add_token(token_list, create_token(REDIRECT_IN, "<"));
		return (i);
	}
}

int	handle_output_redirections(char *input, t_token **token_list, int i)
{
	if (input[i + 1] == '>')
	{
		if (input[i + 2] == '>' || input[i + 2] == '<')
		{
			printf("syntax error near unexpected token '%c'\n", input[i + 2]);
			return (-1);
		}
		add_token(token_list, create_token(APPEND, ">>"));
		return (i + 1);
	}
	else
	{
		add_token(token_list, create_token(REDIRECT_OUT, ">"));
		return (i);
	}
}
