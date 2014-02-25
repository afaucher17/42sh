/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 14:57:38 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/04 10:45:26 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<stdlib.h>
#include	"libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*rslt_lst;
	t_list	*rslt_save;

	rslt_lst = NULL;
	while (lst)
	{
		rslt_save = f(lst);
		ft_lstaddend((&rslt_lst), ft_lstnew(rslt_save->content,
					rslt_save->content_size));
		lst = lst->next;
	}
	return (rslt_lst);
}
