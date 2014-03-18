/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 12:04:11 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 20:52:09 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include		"42sh.h"

void			ft_backspace(t_dlist **list, int visual, t_mlist *mlist)
{
	if (g_idx > 0)
	{
		ft_l_arrow(list, visual, mlist);
		ft_delete(list, visual, mlist);
	}
}

void			ft_delete(t_dlist **list, int visual, t_mlist *mlist)
{
	int			j;

	j = g_idx;
	if (!visual)
	{
		ft_memmove(g_cmd + g_idx, g_cmd + g_idx + 1, ft_strlen(g_cmd + g_idx));
		ft_putstr(g_cmd + g_idx);
		g_idx += ft_strlen(g_cmd + g_idx);
		ft_putchar(' ');
		tputs(tgetstr("le", NULL), 1, ft_putchar_tc);
		if (ft_get_winsz()->ws_col > 0 && ((g_idx + ft_strlen(PROMPT))
			% ft_get_winsz()->ws_col) == (u_int)ft_get_winsz()->ws_col - 1)
			tputs(tgetstr("nd", NULL), 1, ft_putchar_tc);
		while (g_idx > 0 && g_idx > j)
			ft_l_arrow(list, 0, mlist);
	}
}

void			ft_home(t_dlist **list, int visual, t_mlist *mlist)
{
	while (g_idx > 0)
	{
		ft_l_arrow(list, visual, mlist);
		if (ft_get_copy()->visual_mode)
			visual--;
	}
}

void			ft_end(t_dlist **list, int visual, t_mlist *mlist)
{
	while (g_cmd[g_idx])
	{
		ft_r_arrow(list, visual, mlist);
		if (ft_get_copy()->visual_mode)
			visual++;
	}
}

void			ft_ctrl_d(t_dlist **list, int visual, t_mlist *mlist)
{
	(void)visual;
	g_idx = 0;
	ft_dlist_clear(list);
	ft_list_clear(&(mlist->env));
	ft_close_fdlist(&(mlist->fdlist));
	free(mlist);
	free(g_cmd);
	ft_putendl("");
	ft_reset_term();
	exit(EXIT_SUCCESS);
}
