/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:22:11 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/11/28 18:42:04 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* recherche la première occurrence de la sous-chaîne souch dans la chaîne chpr,
mais seulement dans les len premiers caractères de chpr
chpr	: La chaîne dans laquelle rechercher
souch	: La sous-chaîne à rechercher
len		: Le nombre de caractères à examiner dans chpr
*/

#include "libft.h"

char	*ft_strnstr(const char *chpr, const char *souch, size_t len)
{
	size_t	i;
	size_t	j;

	if (*souch == '\0')
	{
		return ((char *)chpr);
	}
	i = 0;
	while (i < len && chpr[i] != '\0')
	{
		j = 0;
		while (chpr[i + j] == souch[j] && souch[j] != '\0' && (i + j) < len)
		{
			j++;
		}
		if (souch[j] == '\0')
		{
			return ((char *)&chpr[i]);
		}
		i++;
	}
	return (NULL);
}

/*int main()
{
	const char *chpr = "Hello, world!";
	const char *souch = "orld";
	size_t len = 13;

	char *result = ft_strnstr(chpr, souch, len);

	if (result != NULL)
	{
		printf("Sous-chaîne trouvée à l'index %ld\n", result - chpr);
	}
	else
	{
		printf("Sous-chaîne non trouvée\n");
	}
	return (0);
}*/
