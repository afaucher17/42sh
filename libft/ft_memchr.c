/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 18:24:21 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/26 14:44:09 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		<string.h>
#include		"libft.h"

void			*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*save_ptr;

	i = 0;
	save_ptr = s;
	while (i < n)
	{
		if (*save_ptr == c)
			return ((void*)save_ptr);
		i++;
		save_ptr++;
	}
	return (NULL);
}
