/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:36:25 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/11/28 15:16:08 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*recherche la premiere occurence d'un char dans un blocmemoir.
	bmem 	: pointeur vers ladresse du bloc memoir ou faire la recherche 
	schar 	: caractere a rechercher
	size 	: taille de la zone memoire a rechercher
	
*/

#include "libft.h"

void	*ft_memchr(const void *bmem, int schar, size_t size)
{
	const unsigned char	*ptr;
	unsigned char		uc;

	ptr = (const unsigned char *)bmem;
	uc = (unsigned char)schar;
	while (size > 0)
	{
		if (*ptr == uc)
		{
			return ((void *)ptr);
		}
		ptr++;
		size--;
	}
	return (NULL);
}

/*int	main(void)
{
	const char	str[] = "Hello, World!";
	char		*result;

	result = ft_memchr(str, 'W', sizeof(str));
	if (result != NULL)
	{
		printf("Caractère trouvé a l'index : %ld\n", result - str);
	}
	else
	{
		printf("Caractère non trouvé.\n");
	}
	return (0);
}*/