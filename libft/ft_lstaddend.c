/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 15:41:19 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/07 18:27:59 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void		ft_lstaddend(t_list **alst, t_list *new)
{
	t_list	*cur;

	cur = *alst;
	if (alst && new)
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	else if (!alst)
	{
		*alst = new;
	}
}
