/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 14:44:11 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/04 11:00:38 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		<string.h>
#include		"libft.h"

char			*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	const char	*save_ptr;
	const char	*save_ptr_2;
	size_t		i;
	size_t		j;

	i = 0;
	if (*s2 == '\0')
		return ((char*)s1);
	save_ptr_2 = s2;
	while ((*s1) && (i < n))
	{
		j = i++;
		save_ptr = s1;
		while (((*save_ptr == *save_ptr_2) || (*save_ptr_2 == '\0'))
					&& (j <= n))
		{
			if (*save_ptr_2++ == '\0')
				return ((char*)s1);
			save_ptr++;
			j++;
		}
		save_ptr_2 = s2;
		s1++;
	}
	return (NULL);
}
