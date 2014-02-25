/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 16:30:37 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/04 10:41:40 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		<stdlib.h>
#include		"libft.h"

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*newlst;

	newlst = (t_list*)malloc(sizeof(t_list));
	if (!newlst)
		return (NULL);
	if (content)
	{
		newlst->content = malloc(content_size);
		if (newlst->content)
		{
			ft_memcpy(newlst->content, content, content_size);
			newlst->content_size = content_size;
			newlst->next = NULL;
		}
		else
			return (NULL);
	}
	else
	{
		newlst->content = NULL;
		newlst->content_size = 0;
		newlst->next = NULL;
	}
	return (newlst);
}
