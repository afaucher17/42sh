/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/07 16:45:51 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 15:47:37 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "ft_select.h"
#include "libft.h"

size_t	get_margin(t_select *slct)
{
	size_t	size;
	t_lst	*current;

	size = 0;
	if (!(slct->list))
		return (size);
	current = slct->list;
	while (current->next)
	{
		if (current->length > size)
			size = current->length;
		current = current->next;
	}
	return (size + 3);
}

void	draw_list(t_select *slct)
{
	t_lst	*list;
	int		style;
	int		x;
	int		y;

	list = slct->list;
	put_flag(GO_TOP_LEFT);
	put_flag(CLEAR_NEXT);
	x = 0;
	y = 0;
	while (list)
	{
		move_to(x, y);
		style = 0;
		style = (list->selected) ? style | REV_VIDEO : style;
		style = (list == slct->current) ? style | UNDERLINE : style;
		putstr_flag(list->label, style);
		list = list->next;
		x = (y < ft_get_winsz()->ws_row - 1) ? x : x + (int)slct->margin;
		y = (y < ft_get_winsz()->ws_row - 1) ? y + 1 : 0;
	}
}
