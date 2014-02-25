/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 18:02:51 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/26 10:52:04 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<string.h>
#include	"libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = ft_strnew(len);
	if (sub == NULL)
		return (NULL);
	while (start > 0)
	{
		s++;
		start--;
	}
	sub = ft_strncpy(sub, s, len);
	return (sub);
}
