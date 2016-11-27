/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 16:50:24 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/04 10:56:55 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "libft.h"
#include	<string.h>

int			ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int		result;

	result = ft_strncmp(s1, s2, n);
	if (result == 0)
		return (1);
	else
		return (0);
}
