/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:11:38 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/03/07 15:43:13 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		allouer un bloc de memoire en initialisant tous ces octets a 0
		count 		: nb d'elements a allouer
		size 		: taille de chaque element a allouer

		ptr 		: pointeur pr stocker ladresse de la memoire allouee
		len				: variable pr stocker la taille totale de la memoire allouee
*/
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	len;
	void	*ptr;

	if (count != 0 && size != 0 && count > SIZE_MAX / size)
		return (NULL);
	len = count * size;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}

/*int	main(void)
{
	size_t	result;

	result = 0;
	result -= 1;
	printf("result = %lu, ULONG_MAX = %lu\n", result, ULONG_MAX);
	// ft_calloc(-5, 1);
}
*/