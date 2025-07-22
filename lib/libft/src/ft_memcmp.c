/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:28:32 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/11/28 18:20:19 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* compare les n premiers octets des zones memoires pointees par ptr1 et 2
*/
#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)ptr1;
	p2 = (const unsigned char *)ptr2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return ((int)p1[i] - (int)p2[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	char	str1[10] = "Hello";
	char	str2[10] = "Hello";
	char	str3[10] = "Hella";
	int		result1;
	int		result2;

	result1 = ft_memcmp(str1, str2, 5);
	result2 = ft_memcmp(str1, str3, 5);
	printf("Comparaison de str1 et str2 : %d\n", result1);
	printf("Comparaison de str1 et str3 : %d\n", result2);
	return (0);
}*/
