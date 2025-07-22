/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:31:14 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/01/11 18:58:10 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// cspdiuxX%	p
int	ft_param(char i, va_list args)
{
	int	len;

	len = 0;
	if (i == 'd' || i == 'i')
		len = ft_nb(va_arg(args, int));
	else if (i == 'c')
		len = ft_char(va_arg(args, int));
	else if (i == 's')
		len = ft_str(va_arg(args, char *));
	else if (i == '%')
		len = ft_char('%');
	else if (i == 'x')
		len = ft_xlo(va_arg(args, int));
	else if (i == 'X')
		len = ft_xup(va_arg(args, int));
	else if (i == 'u')
		len = ft_unsigned(va_arg(args, int));
	else if (i == 'p')
		len = ft_p(va_arg(args, size_t));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			len = len + ft_param(str[i], args);
		}
		else
		{
			ft_char(str[i]);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}

/*int	main(void)
{
	int	x;
	int	y;

	x = printf("mon prenom commence par %c, je m'apl %s, j'ai %d ans et %i
       	chat et je suis a 100 %%, %x, %X, %u\n", 'i', "imran", 25, 1, 255, 255,
       	4294967295U);
	printf("%d\n", x);
	y = ft_printf("mon prenom commence par %c, je m'apl %s, j'ai %d ans et 
	%i chat et je suis a 100 %%, %x, %X, %u\n", 'i', "imran", 25, 1, 255,
       	255, 4294967295U);
	printf("%d\n", y);
	return (0);
}*/
