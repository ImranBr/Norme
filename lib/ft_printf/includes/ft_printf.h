/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:58:55 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/12/18 22:13:33 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

int	ft_char(char c);
int	ft_str(char *str);
int	ft_nb(int nb);
int	ft_param(char i, va_list args);
int	ft_printf(const char *str, ...);
int	ft_xup(unsigned int nb);
int	ft_xlo(unsigned int nb);
int	ft_unsigned(unsigned int nb);
int	ft_p(unsigned long long int nb);

#endif