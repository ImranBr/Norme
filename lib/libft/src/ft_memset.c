/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:58:24 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/03/10 23:38:15 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*		Cette fonction permet de remplir une zone mémoire,
 		identifiée par son adresse et sa taille, avec une valeur précise.
		
    	*b		: pointeur vers l'adresse du bloc mémoire à ré-initialiser.
    	c 		: valeur à utiliser pour remplir le bloc de mémoire.
    	len 	: nombre d'octets à initialiser.

*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = b;
	while (len != 0)
	{
		*str = (unsigned char)c;
		str++;
		len--;
	}
	return (b);
}

// ft_memset(&lst, 0, t_list);

/*int	main(void)
{
	char	str[20] = "Hello, World!";

	ft_memset(str, 0, 3);
	printf("%s\n", str);
}*/