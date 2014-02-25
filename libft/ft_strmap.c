/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 13:41:10 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/23 19:33:03 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	char	*save_ptr;

	str = ft_strdup(s);
	save_ptr = str;
	while (*str != '\0' && f)
	{
		*str = f(*s);
		str++;
		s++;
	}
	str = save_ptr;
	return (str);
}
