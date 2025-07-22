/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:53:51 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/11/29 20:29:26 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlena(int nb)
{
	int		len;
	long	n;

	len = 0;
	n = nb;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	long	nb;

	nb = n;
	i = ft_strlena(nb);
	res = malloc((ft_strlena(nb) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[i] = '\0';
	i--;
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		res[0] = '0';
	while (nb > 0)
	{
		res[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (res);
}

/*int	main(void)
{
	char *result;
	int number;

	number = -1;
	result = ft_itoa(number);
	if (result != NULL)
	{
		printf("ft_itoa(%d) = %s\n", number, result);
		free(result);
	}
	else
	{
		printf("ft_itoa(%d) = NULL (allocation echouee)\n", number);
	}
	return (0);
}*/