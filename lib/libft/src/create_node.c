/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:15:09 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/14 00:15:46 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*create_node(int nbr)
{
	t_node	*entier;

	entier = malloc(sizeof(t_node));
	if (entier == NULL)
		return (NULL);
	entier->value = nbr;
	entier->next = NULL;
	return (entier);
}
