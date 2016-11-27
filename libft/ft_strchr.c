/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 14:06:08 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/04 10:46:39 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<string.h>
#include	"libft.h"

char		*ft_strchr(const char *s, int c)
{
	while ((*s != c) && (*s != '\0'))
		s++;
	if (*s != c)
		return (NULL);
	return ((char*)s);
}
