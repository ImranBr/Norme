/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:59:05 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/11/28 14:58:59 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*copier un nb specifie d'octets dune src vers une dest
en gerant les cas ou les blocs de memoir se chevauchent
dest	: ptr vers la zone qui recoit les donnees copiees
src		: ptr vers la zone dou on copie les donnees
n 		: nombre doctets a copier de src vers dest
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s = (const char *)src;

	d = (char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}

/*int main(void)
{
	char	dest[] = "goodbye, world!";
	char	src[] = "hello, world!";

	printf("Before memmove: dest = %s, src = %s\n", dest, src);
	ft_memmove(dest, src, sizeof(src));
	printf("After memmove: dest = %s\n", dest);
	return (0);
}
*/