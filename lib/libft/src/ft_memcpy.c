/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:19:32 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/11/28 14:18:52 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*copier un bloc memoire dans un nvl emplacement
dest	: adresse du bloc memoire qui recoit les donnees
src		: adresse du bloc memoire a dupliquer 
n 		: nombre doctets a dupliquer
*/
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*int	main(void)
{
	char dest[500];
	char src[] = "salut abdcef";
	ft_memcpy(dest, src, sizeof(src));
	printf("%s", dest);
}*/
