/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/08/21 15:03:33 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/03 16:55:58 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			<stdlib.h>
#include			<string.h>
#include			"libft.h"

char				*ft_strdup(const char *s1)
{
	size_t			i;
	char			*duplicate;
	size_t			str_len;

	i = 0;
	str_len = ft_strlen(s1);
	duplicate = (char*)malloc(str_len + 1);
	if (!duplicate)
		return (NULL);
	while (i < str_len)
	{
		duplicate[i] = s1[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
