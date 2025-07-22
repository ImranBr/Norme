/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:56:46 by ibarbouc          #+#    #+#             */
/*   Updated: 2024/11/28 12:22:37 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Cette fonction permet de remplir une zone mémoire,
 		identifiée par son adresse et sa taille, avec une valeur précise.
		
    	*b		: pointeur vers l'adresse du bloc mémoire à ré-initialiser.
    	c 		: valeur à utiliser pour remplir le bloc de mémoire.
    	len 	: nombre d'octets à initialiser.

*/

#include "libft.h" 

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
