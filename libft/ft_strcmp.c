/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/08/19 12:27:14 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/26 14:48:25 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"libft.h"

int				ft_strcmp(const char *s1, const char *s2)
{
	int			result;
	const char	*s_one;
	const char	*s_two;

	s_one = s1;
	s_two = s2;
	while (*s_one == *s_two && *s_one != '\0')
	{
		s_one++;
		s_two++;
	}
	result = *s_one - *s_two;
	return (result);
}
