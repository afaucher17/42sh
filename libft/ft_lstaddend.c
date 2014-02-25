/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 15:41:19 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/04 10:35:44 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void		ft_lstaddend(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		while (*alst)
			*alst = (*alst)->next;
		*alst = new;
	}
}
