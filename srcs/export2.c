/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joudafke <joudafke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:44:07 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/19 16:02:16 by joudafke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_exp(char *cmd)
{
	int	i;

	if (!cmd || !cmd[0])
		return (0);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		ft_putstr_fd("minishell: export: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier2\n", STDERR_FILENO);
		return (0);
	}
	i = 1;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			ft_putstr_fd("minishell: export: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

void	print_export(char **env_cpy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_cpy[i])
	{
		ft_putstr_fd("declare -x ", 1);
		while (env_cpy[i][j] && env_cpy[i][j] != '=')
		{
			write(1, &env_cpy[i][j], 1);
			j++;
		}
		if (env_cpy[i][j] == '=')
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			ft_putstr_fd(&env_cpy[i][j + 1], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
		j = 0;
	}
}

void	export_sorted(char **env_cpy, int len_env)
{
	int		i;
	int		sorted;
	char	*swp;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < len_env - 1)
		{
			if (ft_strcmp(env_cpy[i], env_cpy[i + 1]) > 0)
			{
				swp = env_cpy[i + 1];
				env_cpy[i + 1] = env_cpy[i];
				env_cpy[i] = swp;
				sorted = 0;
			}
			i++;
		}
	}
}

char	**cpy_env_to_tab(t_env *env, int i, int count)
{
	char	**tab;
	t_env	*tmp;
	char	*tmp_egal;

	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			tmp_egal = ft_strjoin(tmp->name, "=");
			tab[i] = ft_strjoin(tmp_egal, tmp->value);
			free(tmp_egal);
		}
		else
			tab[i] = ft_strdup(tmp->name);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	builtin_export(t_env *env_list, char **cmd)
{
	int		i;
	int		len;
	char	**cpy_env;

	i = 1;
	len = 0;
	if (!cmd[1])
	{
		cpy_env = cpy_env_to_tab(env_list, 0, 0);
		while (cpy_env[len])
			len++;
		export_sorted(cpy_env, len);
		print_export(cpy_env);
		return (free_split(cpy_env), 1);
	}
	else
	{
		if (is_valid_exp(cmd[i]) && ft_strchr(cmd[i], '='))
			add_or_replace(&env_list, cmd[i]);
	}
	return (1);
}
