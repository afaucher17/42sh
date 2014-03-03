/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 12:19:35 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/03 12:33:28 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"libft.h"

char				*ft_concat(t_list *list)
{
	char			*res;
	char			*tmp;

	res = NULL;
	while (list)
	{
		tmp = res;
		res = ft_strjoin(tmp, (char*)(list->content));
		if (list->next)
			res = ft_strjoin(res, " ");
		list = list->next;
	}
	return (res);
}
