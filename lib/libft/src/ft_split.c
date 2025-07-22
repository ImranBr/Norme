/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:59:52 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/16 14:55:32 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static int	count_lettre(char const *s, int c)
{
	char	*pos;

	pos = ft_strchr(s, c);
	if (pos)
		return (pos - s);
	return (ft_strlen(s));
}

void	**ft_free(char **split, int j)
{
	while (j > 0)
	{
		free(split[--j]);
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	size_t	nb_lettre;
	char	**split;

	i = ((j = 0));
	split = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			nb_lettre = count_lettre(&s[i], c);
			split[j] = ft_substr(s, i, nb_lettre);
			if (!split[j])
				return ((char **)ft_free(split, j));
			i = i + nb_lettre;
			j++;
		}
	}
	split[j] = NULL;
	return (split);
}

/*int	main(void)
{
	char **tab = ft_split("salut comment ca-va ?", ' ');

	int i = 0;
	while (tab[i] != NULL)
		printf("%s\n", tab[i++]);
}*/