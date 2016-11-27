/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:50:21 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/26 14:45:33 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		<string.h>
#include		"libft.h"

void			*ft_memset(void *b, int c, size_t len)
{
	size_t		i;
	char		*save_ptr;

	i = 0;
	save_ptr = b;
	while ((i < len) && (b != NULL))
	{
		*save_ptr = c;
		i++;
		save_ptr++;
	}
	return (b);
}
