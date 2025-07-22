/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:47:40 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/13 23:50:16 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_node **last, int nbr)
{
	t_node	*new_node;

	new_node = create_node(nbr);
	if (!new_node || !last)
		return ;
	if (*last)
		ft_lstlast(*last)->next = new_node;
	else
		*last = new_node;
}
