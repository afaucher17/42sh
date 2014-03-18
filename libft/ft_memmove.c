/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 18:07:59 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/04 10:54:09 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		<string.h>
#include		"libft.h"

void			*ft_memmove(void *s1, const void *s2, size_t n)
{
	char		*save_ptr;
	const char	*save_ptr_2;

	save_ptr = s1;
	save_ptr_2 = s2;
	if ((save_ptr <= save_ptr_2) || ((save_ptr + n) <= save_ptr_2))
		while (n > 0)
		{
			*save_ptr = *save_ptr_2;
			save_ptr++;
			save_ptr_2++;
			n--;
		}
	else
	{
		save_ptr = save_ptr + n - 1;
		save_ptr_2 = save_ptr_2 + n - 1;
		while (n-- > 0)
		{
			*save_ptr = *save_ptr_2;
			save_ptr--;
			save_ptr_2--;
		}
	}
	return (s1);
}
