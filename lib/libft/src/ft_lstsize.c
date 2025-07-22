/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:14:33 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/13 23:54:48 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_node *lst)
{
	t_node	*tmp;
	int		i;

	i = 1;
	tmp = lst->next;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
