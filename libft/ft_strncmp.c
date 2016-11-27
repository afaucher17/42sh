/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/08/19 13:15:51 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/26 14:51:19 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include					<string.h>
#include					"libft.h"

int							ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int						result;
	const unsigned char		*s_one;
	const unsigned char		*s_two;

	if (n == 0)
		return (0);
	s_one = (const unsigned char*)s1;
	s_two = (const unsigned char*)s2;
	while (*s_one == *s_two && *s_one != '\0' && n > 1)
	{
		n--;
		s_one++;
		s_two++;
	}
	result = *s_one - *s_two;
	return (result);
}
