/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:43:46 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/17 04:03:19 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(char *input, int *i, t_env *env_list, int exit_status)
{
	char	var_name[256];
	int		len;
	char	*value;

	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(exit_status));
	}
	len = extract_var_name(input, *i, var_name);
	if (len == 0)
		return (ft_strdup(""));
	*i += len;
	value = get_env_value(var_name, env_list);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

void	add_char_to_result(t_expand *exp, char c)
{
	exp->temp[0] = c;
	exp->temp[1] = '\0';
	exp->tmp = exp->result;
	exp->result = ft_strjoin(exp->result, exp->temp);
	free(exp->tmp);
}

void	update_quote_state(char c, t_quote_state *quote)
{
	if (c == '\'' && *quote == NO_QUOTE)
		*quote = SINGLE_QUOTE;
	else if (c == '\'' && *quote == SINGLE_QUOTE)
		*quote = NO_QUOTE;
	else if (c == '"' && *quote == NO_QUOTE)
		*quote = DOUBLE_QUOTE;
	else if (c == '"' && *quote == DOUBLE_QUOTE)
		*quote = NO_QUOTE;
}

char	*expand_variables(char *input, t_env *env_list, int exit_status)
{
	t_expand	exp;

	exp.quote = NO_QUOTE;
	exp.i = 0;
	exp.result = ft_strdup("");
	while (input[exp.i])
	{
		update_quote_state(input[exp.i], &exp.quote);
		if (input[exp.i] == '$' && exp.quote != SINGLE_QUOTE)
		{
			exp.expanded = expand_dollar(input, &exp.i, env_list, exit_status);
			exp.tmp = exp.result;
			exp.result = ft_strjoin(exp.result, exp.expanded);
			free(exp.tmp);
			free(exp.expanded);
			continue ;
		}
		else
			add_char_to_result(&exp, input[exp.i]);
		exp.i++;
	}
	return (exp.result);
}
