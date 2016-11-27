/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpushfront.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 13:22:18 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/05 14:57:00 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"libft.h"

void			ft_dlstpushfront(t_dlist **list,
						void *content, size_t content_size)
{
	t_dlist		*new;
	t_dlist		*cur;

	new = ft_dlstnew(content, content_size);
	cur = *list;
	if (!cur)
		*list = new;
	else
	{
		new->next = cur;
		cur->prev = new;
		*list = new;
	}
}
