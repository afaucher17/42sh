/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_fun3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 12:27:20 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/18 18:56:52 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

void				ft_alt_u_arrow(t_dlist **list, int visual, t_mlist *mlist)
{
	int					x;

	x = 0;
	while (x < ft_get_winsz()->ws_col && g_idx > 0)
	{
		ft_l_arrow(list, visual, mlist);
		if (ft_get_copy()->visual_mode)
			visual--;
		x++;
	}
}

void					ft_alt_d_arrow(t_dlist **list, int visual, t_mlist *mlist)
{
	int					x;

	x = 0;
	while (x < ft_get_winsz()->ws_col && g_cmd[g_idx])
	{
		ft_r_arrow(list, visual, mlist);
		if (ft_get_copy()->visual_mode)
			visual++;
		x++;
	}
}

void					ft_alt_l_arrow(t_dlist **list, int visual, t_mlist *mlist)
{
	while ((g_idx - 1) >= 0 && g_cmd[g_idx - 1] == ' ')
	{
		ft_l_arrow(list, visual, mlist);
		if (ft_get_copy()->visual_mode)
			visual--;
	}
	while ((g_idx - 1) >= 0 && g_cmd[g_idx - 1] != ' ')
	{
		ft_l_arrow(list, visual, mlist);
		if (ft_get_copy()->visual_mode)
			visual--;
	}
}

void				ft_alt_r_arrow(t_dlist **list, int visual, t_mlist *mlist)
{
	while (g_cmd[g_idx] && g_cmd[g_idx] != ' ')
	{
		ft_r_arrow(list, visual, mlist);
		if (ft_get_copy()->visual_mode)
			visual++;
	}
	while (g_cmd[g_idx] && g_cmd[g_idx] == ' ')
	{
		ft_r_arrow(list, visual, mlist);
		if (ft_get_copy()->visual_mode)
			visual++;
	}
}

void				ft_return(t_dlist **list, int visual, t_mlist *mlist)
{
	(void)visual;
	ft_get_copy()->visual_mode = 0;
	tputs(tgetstr("me", NULL), 1, ft_putchar_tc);
	ft_end(list, 0, mlist);
	g_cmd[g_idx] = '\n';
	ft_putchar('\n');
	ft_dlist_clear(list);
}
