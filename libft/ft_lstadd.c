/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 12:22:43 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/27 15:50:16 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void		ft_lstadd(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			new->next = *alst;
			*alst = new;
		}
	}
}
