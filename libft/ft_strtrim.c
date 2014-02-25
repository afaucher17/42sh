/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 19:27:59 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/01/15 12:17:02 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"libft.h"

static char const	*findstrend(char const *s)
{
	while (*s != '\0')
		s++;
	return (s);
}

char				*ft_strtrim(char const *s)
{
	unsigned int	start;
	size_t			len;
	char			*str;
	char const		*save_ptr;

	start = 0;
	len = ft_strlen(s);
	save_ptr = s;
	while (*s == ' ' || *s == '\n' || *s == '\t')
	{
		start++;
		s++;
	}
	s = findstrend(s);
	if (save_ptr == s)
		return ("");
	while (*s == ' ' || *s == '\n' || *s == '\t' || *s == '\0')
	{
		len--;
		s--;
	}
	len = len - start + 1;
	s = save_ptr;
	str = ft_strsub(s, start, len);
	return (str);
}
