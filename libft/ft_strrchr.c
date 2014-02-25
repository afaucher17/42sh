/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 14:13:07 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/26 14:52:23 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<string.h>
#include	"libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*save_ptr;

	save_ptr = (char*)s;
	while (*save_ptr != '\0')
		save_ptr++;
	while ((save_ptr != s) && (*save_ptr != c))
		save_ptr--;
	if ((save_ptr == s) && (*s != c))
		return (NULL);
	return (save_ptr);
}
