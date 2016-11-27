/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/01 12:55:28 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/13 22:07:58 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		<string.h>
#include		<stdlib.h>
#include		"libft.h"

void			ft_lstpushback(t_list **alst, void const *content,
								size_t content_size)
{
	t_list		*list;

	list = NULL;
	if (alst)
	{
		if (*alst == NULL)
			*alst = ft_lstnew(content, content_size);
		else
		{
			list = *alst;
			while (list->next)
				list = list->next;
			list->next = ft_lstnew(content, content_size);
		}
	}
}
