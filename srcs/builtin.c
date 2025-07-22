/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:42:39 by joudafke          #+#    #+#             */
/*   Updated: 2025/07/22 21:18:19 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **args)
{
	char	cwd[PATH_MAX];

	if (args[1] && args[1][0] == '-')
	{
		printf("minishell: pwd: %s: invalid option\n", args[1]);
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}

int	builtin_env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		else
			printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 5) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	fflush(stdout);
	return (0);
}

void	error_cd(void)
{
	static char	*oldpwd;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		printf("oldpwd not set");
		free(cwd);
		return ;
	}
	printf("%s\n", oldpwd);
	if (chdir(oldpwd) == -1)
	{
		perror("cd");
		free(cwd);
		return ;
	}
	free(cwd);
	return ;
}

void	ft_cd(char *path)
{
	static char	*oldpwd;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!path || !path[0])
	{
		path = getenv("HOME");
		if (!path)
			return (printf("HOME not set"), free(cwd), free(oldpwd));
	}
	else if (strcmp(path, "-") == 0)
		return (error_cd());
	if (chdir(path) == -1)
	{
		perror("cd");
		free(cwd);
		return ;
	}
	oldpwd = cwd;
	free(cwd);
}
