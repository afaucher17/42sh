/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 18:10:11 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/04 10:43:05 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include				<string.h>
#include				"libft.h"

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*save_ptr;
	const unsigned char	*save_ptr_2;

	if (n == 0)
		return (0);
	save_ptr = s1;
	save_ptr_2 = s2;
	while (n--)
	{
		if (*save_ptr != *save_ptr_2)
			return (*save_ptr - *save_ptr_2);
		save_ptr++;
		save_ptr_2++;
	}
	return (0);
}
