/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_fun2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 12:16:52 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/24 17:34:31 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

void				ft_u_arrow(t_dlist **list, int visual)
{
	visual = 0;
	if (*list && (*list)->next)
	{
		*list = (*list)->next;
		ft_get_copy()->visual_mode = 0;
		ft_end(list, visual);
		ft_bzero(g_cmd, BUFF_SIZE);
		ft_strcpy(g_cmd, (*list)->content);
		while (g_idx > 0)
		{
			g_idx--;
			tputs(tgetstr("le", NULL), 1, ft_putchar_tc);
			tputs(tgetstr("dc", NULL), 1, ft_putchar_tc);
		}
		ft_putstr(g_cmd);
		g_idx = ft_strlen(g_cmd);
	}
}

void				ft_d_arrow(t_dlist **list, int visual)
{
	visual = 0;
	if (*list && (*list)->prev)
	{
		(*list) = (*list)->prev;
		ft_get_copy()->visual_mode = 0;
		ft_end(list, visual);
		ft_bzero(g_cmd, BUFF_SIZE);
		ft_strcpy(g_cmd, (*list)->content);
		while (g_idx > 0)
		{
			g_idx--;
			tputs(tgetstr("le", NULL), 1, ft_putchar_tc);
			tputs(tgetstr("dc", NULL), 1, ft_putchar_tc);
		}
		ft_putstr(g_cmd);
		g_idx = ft_strlen(g_cmd);
	}
}

/*void				ft_l_arr_bis(int i, t_dlist **list, char *g_cmd)
{
	if (g_cmd[i])
	{
		tputs(tgetstr("dc", NULL), 1, ft_putchar_tc);
		ft_putchar(g_cmd[i]);
		if (((g_idx + ft_strlen(PROMPT)) % ft_get_winsz()->ws_col)
				== ft_get_winsz()->ws_col - 1)
			tputs(tgetstr("do", NULL), 1, ft_putchar_tc);
		ft_get_copy()->visual_mode = 0;
		ft_l_arrow(g_idx + 1, list, g_cmd, 0);
		ft_get_copy()->visual_mode = 1;
	}
}*/

void				ft_l_arrow(t_dlist **list, int visual)
{
	int				j;

	(void)list;
	(void)visual;
	if (g_idx > 0)
	{
		if (((g_idx + ft_strlen(PROMPT)) % ft_get_winsz()->ws_col) == 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar_tc);
			j = 0;
			while (j < ft_get_winsz()->ws_col + 1)
			{
				tputs(tgetstr("nd", NULL), 1, ft_putchar_tc);
				j++;
			}
		}
		else
			tputs(tgetstr("le", NULL), 1, ft_putchar_tc);
		g_idx--;
	}
}

void				ft_r_arrow(t_dlist **list, int visual)
{
	(void)list;
	(void)visual;
	if (g_cmd[g_idx])
	{
		g_idx++;
		tputs(tgetstr("nd", NULL), 1, ft_putchar_tc);
		if (((g_idx + ft_strlen(PROMPT)) % ft_get_winsz()->ws_col) == 0)
			tputs(tgetstr("do", NULL), 1, ft_putchar_tc);
	}
}
