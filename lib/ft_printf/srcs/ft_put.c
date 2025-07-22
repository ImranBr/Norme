/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:04:15 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/12/24 11:28:32 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_str(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
	{
		len += write(1, "(null)", 6);
	}
	else
	{
		while (*str)
		{
			len += write(1, str, 1);
			str++;
		}
	}
	return (len);
}

int	ft_nb(int nb)
{
	long	nbr;
	int		len;

	nbr = nb;
	len = 0;
	if (nbr < 0)
	{
		ft_char('-');
		nbr = -nbr;
		len++;
	}
	if (nbr > 9)
	{
		len = len + ft_nb(nbr / 10);
	}
	len = len + ft_char(nbr % 10 + '0');
	return (len);
}

int	ft_xlo(unsigned int nb)
{
	int		len;
	char	*hex;

	len = 0;
	hex = "0123456789abcdef";
	if (nb >= 16)
	{
		len += ft_xlo(nb / 16);
	}
	len += ft_char(hex[nb % 16]);
	return (len);
}

int	ft_xup(unsigned int nb)
{
	int		len;
	char	*hex;

	len = 0;
	hex = "0123456789ABCDEF";
	if (nb >= 16)
	{
		len += ft_xup(nb / 16);
	}
	len += ft_char(hex[nb % 16]);
	return (len);
}
