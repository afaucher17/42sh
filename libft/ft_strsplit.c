/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 11:35:27 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/03 12:33:47 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"libft.h"

t_list				*ft_strsplit(char const *s, char *special)
{
	t_list			*list;
	char			*buff;
	int				i;

	list = NULL;
	buff = ft_strnew(ft_strlen(s));
	i = 0;
	while (s && *s)
		if (ft_strchr(special, *s))
		{
			if (buff[0])
				ft_lstpushback(&list, buff, ft_strlen(buff) + 1);
			ft_bzero(buff, i);
			i = 0;
			s++;
		}
		else
		{
			buff[i] = *s;
			i++;
			s++;
		}
	free(buff);
	return (list);
}
