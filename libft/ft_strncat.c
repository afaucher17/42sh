/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/08/19 16:36:23 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/26 14:51:03 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		<string.h>
#include		"libft.h"

char			*ft_strncat(char *s1, const char *s2, size_t n)
{
	char		*save_ptr;

	save_ptr = s1;
	while (*s1)
		s1++;
	while (n > 0 && *s2)
	{
		*s1 = *s2;
		s2++;
		s1++;
		n--;
	}
	*s1 = '\0';
	return (save_ptr);
}
