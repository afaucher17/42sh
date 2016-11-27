/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/05 13:14:59 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/05 13:30:08 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"libft.h"

t_dlist			*ft_dlstnew(void *content, size_t content_size)
{
	t_dlist		*new;

	if ((new = (t_dlist*)malloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	if (content)
	{
		if ((new->content = malloc(content_size)) == NULL)
			return (NULL);
		new->content_size = content_size;
		ft_memcpy(new->content, content, content_size);
	}
	else
	{
		new->content_size = 0;
		new->content = NULL;
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
