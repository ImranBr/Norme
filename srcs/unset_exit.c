/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:44:46 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/22 21:29:16 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_nbr(char *str)
{
	int			i;
	int			signe;
	long int	result;

	i = 0;
	signe = 1;
	result = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			signe = -1;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		result = result * 10 + (str[i] - 48);
		if ((result * signe) < INT_MIN || (result * signe) > INT_MAX)
			return (2);
		i++;
	}
	return (0);
}

void	cleanup(t_env *env_list, char **args, char *input)
{
	free_list(env_list);
	if (args)
		free_split(args);
	free(input);
	clear_history();
}

void	handle_non_numeric_exit_arg(t_env *env_list, char **args, char *input)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	if (args[1])
		ft_putstr_fd(args[1], STDERR_FILENO);
	else
		ft_putstr_fd("null", STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	cleanup(env_list, args, input);
	exit(2);
}

void	builtin_exit(t_env *env_list, t_ast_node *node, char *input,
		t_token *token, char *input_for_free)
{
	long	exit_code;

	if (!node->args || !node->args[1])
	{
		free_ast(node);
		free_list(env_list);
		free_tokens(&token);
		free(input_for_free);
		exit(0);
	}
	if (!ft_is_num(node->args[1]))
		handle_non_numeric_exit_arg(env_list, node->args, input);
	if (node->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return ;
	}
	exit_code = ft_valid_nbr(node->args[1]) % 256;
	if (exit_code < 0)
		exit_code += 256;
	free_ast(node);
	free_list(env_list);
	free_tokens(&token);
	free(input_for_free);
	exit(exit_code);
}

t_env	*builtin_unset(t_env *env, char *cmd)
{
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, cmd) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				env = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (env);
}
