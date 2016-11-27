/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 17:05:48 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/26 14:39:51 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		<string.h>
#include		"libft.h"

void			ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*save_ptr;

	i = 0;
	save_ptr = s;
	while (i < n)
	{
		*save_ptr = '\0';
		i++;
		save_ptr++;
	}
}
