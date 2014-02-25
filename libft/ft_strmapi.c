/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 16:35:55 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/29 15:22:35 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    		"libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	str = ft_strdup(s);
	i = 0;
	while (str[i] != '\0' && f)
	{
		str[i] = f(i, *s);
		s++;
		i++;
	}
	return (str);
}
