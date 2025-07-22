/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:56:51 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/11/28 16:55:16 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*recherche de la premiere occurence de c dans la chaine s
et retourne un pointeur vers ce caractère */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/*int main()
{
	char	c;
	char	*result;

	const char  *str= "Bonjour, monde";
	c = 'm';
	result = ft_strchr(str, c);
	if (result != NULL)
	{
		printf("caractere trouve a la position :%ld\n", result - str);
	}
	else
	{
		printf("caractere non trouve. \n");
	}
}*/
