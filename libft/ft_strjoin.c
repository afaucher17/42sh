/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 18:54:37 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/25 21:56:47 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char		*ft_strjoinx(int nb, ...)
{
	va_list	ap;
	char	*args[nb + 1];
	char	*res;
	int		i;
	int		len;

	i = 0;
	va_start(ap, nb);
	while (i < nb)
	{
		args[i] = va_arg(ap, char *);
		len = ft_strlen(args[i]);
		i++;
	}
	args[i] = NULL;
	res = ft_strnew(len);
	i = 0;
	while (i < nb)
	{
		ft_strcat(res, args[i]);
		i++;
	}
	va_end(ap);
	return (res);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*join;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (ft_strdup(""));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	join = ft_strnew(total_len);
	join = ft_strcpy(join, s1);
	join = ft_strcat(join, s2);
	return (join);
}
