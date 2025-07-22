/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:02:58 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/11/28 12:24:52 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	while (i >= 0 && s[i] != (unsigned char)c)
	{
		i--;
	}
	if (i < 0)
		return ((char *) NULL);
	else
		return ((char *)(s + i));
}

/*int main()
{
	const char  *str= "Bonjour, mondem";
	char    c = 'm';
	char    *result = ft_strrchr(str, c);

	if (result != NULL)
	{
		printf("caractere trouve a la position :%ld\n", result - str);
	}
	else
	{
		printf("caractere non trouve. \n");
	}
}*/