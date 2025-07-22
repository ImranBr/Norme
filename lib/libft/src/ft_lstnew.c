/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 00:16:09 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/04/13 23:51:30 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Alloue (avec malloc(3)) et renvoie un nouvel élément. La variable membre
// ’content’ est initialisée à l’aide de la valeur du paramètre ’content’.
// La variable ’next’ est initialisée à NULL.

#include "libft.h"

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*new;
// 	new = malloc(sizeof(t_list));
// 	if (!new)
// 		return (NULL);
// 	new->content = content;
// 	(*new).next = NULL;
// 	return (new);
// }
// typedef struct s_node
// {
// 	int nbr;
// 		*next
// }			t_node

// typedef struct s_stack
// {
// 	t_node head;
// 	t_node last;
// 	size_t len;
// }			t_stack