/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 18:54:37 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/25 18:37:29 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*join;

	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = ft_strnew(total_len);
	join = ft_strcpy(join, s1);
	join = ft_strcat(join, s2);
	return (join);
}
