/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 16:46:20 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/25 16:15:37 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"
#include	<string.h>

int			ft_strequ(char const *s1, char const *s2)
{
	int		result;

	result = ft_strcmp(s1, s2);
	return (result == 0);
}
