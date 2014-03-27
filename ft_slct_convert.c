/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slct_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 14:12:01 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/27 14:13:06 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

t_lst		*ft_convert(t_list *file_l, int *size)
{
	t_lst	*new;
	t_list	*save;

	new = NULL;
	save = file_l;
	while (save)
	{
		(*size)++;
		lst_pushback(&new, (char*)(save->content));
		save = save->next;
	}
	ft_list_clear(&file_l);
	return (new);
}
