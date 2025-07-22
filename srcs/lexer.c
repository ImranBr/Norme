/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:00:47 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/22 01:21:54 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	tokenize_operators(char *input, t_token **token_list, int i)
{
	int	result;

	if (input[i] == '|')
		add_token(token_list, create_token(PIPE, "|"));
	else if (input[i] == '<')
	{
		result = handle_input_redirections(input, token_list, i);
		if (result == -1)
			return (-1);
		else
			i = result;
	}
	else if (input[i] == '>')
	{
		result = handle_output_redirections(input, token_list, i);
		if (result == -1)
			return (-1);
		else
			i = result;
	}
	return (i);
}

size_t	quoted_word(char *input, size_t i, char *assembled_word, int *pos)
{
	char	quote;

	quote = input[i];
	i++;
	while (i < strlen(input) && input[i] != quote)
	{
		assembled_word[(*pos)++] = input[i++];
	}
	if (i < strlen(input) && input[i] == quote)
		i++;
	return (i);
}

int	tokenize_words(char *input, t_token **token_list, size_t start_index)
{
	size_t	i;
	char	*assembled_word;
	int		pos;

	i = start_index;
	assembled_word = malloc(100000);
	pos = 0;
	while (i < strlen(input) && !is_space(input[i]) && input[i] != '|'
		&& input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '\'' || input[i] == '"')
			i = quoted_word(input, i, assembled_word, &pos);
		else
			assembled_word[pos++] = input[i++];
	}
	assembled_word[pos] = '\0';
	add_token(token_list, create_token(WORD, assembled_word));
	free(assembled_word);
	return (i - 1);
}

t_token	*tokenize(char *input, int i)
{
	t_token	*token_list;
	int		len_input;

	token_list = NULL;
	len_input = ft_strlen(input);
	while (i < len_input)
	{
		if (is_space(input[i]))
		{
			i++;
			continue ;
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			i = tokenize_operators(input, &token_list, i);
			if (i == -1)
			{
				free_tokens(&token_list);
				return (NULL);
			}
		}
		else
			i = tokenize_words(input, &token_list, i);
		i++;
	}
	add_token(&token_list, create_token(EOF_TOKEN, NULL));
	return (token_list);
}
