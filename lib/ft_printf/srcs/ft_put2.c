/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:07:32 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/12/18 22:13:18 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned(unsigned int nb)
{
	int		len;
	long	nbr;

	nbr = nb;
	len = 0;
	if (nbr > 9)
	{
		len += ft_unsigned(nbr / 10);
	}
	len += ft_char(nbr % 10 + '0');
	return (len);
}

int	ft_p(unsigned long long int nb)
{
	static int	i;
	char		*hexa;

	i = 2;
	hexa = "0123456789abcdef";
	if (nb == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	if (nb >= 16)
	{
		ft_p(nb / 16);
	}
	if (i == 2)
	{
		write(1, "0x", 2);
	}
	i++;
	ft_char(hexa[nb % 16]);
	return (i);
}
