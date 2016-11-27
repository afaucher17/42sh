/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/08/15 19:55:59 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/29 10:54:26 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		<string.h>
#include		"libft.h"

size_t			ft_strlen(const char *s)
{
	size_t		count;

	count = 0;
	if (s)
		while (*s != '\0')
		{
			count++;
			s++;
		}
	return (count);
}
