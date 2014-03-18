/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:15:28 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/27 10:37:51 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"
#include	<stdlib.h>
#include	<string.h>

void		*ft_memalloc(size_t size)
{
	void	*new_mem;

	new_mem = malloc(size);
	if (!new_mem)
		return (NULL);
	ft_bzero(new_mem, size);
	return (new_mem);
}
