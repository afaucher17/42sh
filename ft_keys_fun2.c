/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_fun2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 12:16:52 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 21:31:42 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

void				ft_u_arrow(t_dlist **list, int visual, t_mlist *mlist)
{
	visual = 0;
	if (*list && (*list)->next)
	{
		free((*list)->content);
		(*list)->content = ft_strdup(g_cmd);
		*list = (*list)->next;
		ft_get_copy()->visual_mode = 0;
		ft_end(list, visual, mlist);
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

void				ft_d_arrow(t_dlist **list, int visual, t_mlist *mlist)
{
	visual = 0;
	if (*list && (*list)->prev)
	{
		free((*list)->content);
		(*list)->content = ft_strdup(g_cmd);
		(*list) = (*list)->prev;
		ft_get_copy()->visual_mode = 0;
		ft_end(list, visual, mlist);
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

void				ft_l_arrow(t_dlist **list, int visual, t_mlist *mlist)
{
	int				j;

	(void)mlist;
	(void)list;
	(void)visual;
	if (g_idx > 0)
	{
		if (ft_get_winsz()->ws_col > 0
				&& ((g_idx + ft_strlen(PROMPT)) % ft_get_winsz()->ws_col) == 0)
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

void				ft_r_arrow(t_dlist **list, int visual, t_mlist *mlist)
{
	(void)mlist;
	(void)list;
	(void)visual;
	if (g_cmd[g_idx])
	{
		g_idx++;
		tputs(tgetstr("nd", NULL), 1, ft_putchar_tc);
		if (ft_get_winsz()->ws_col > 0
				&& ((g_idx + ft_strlen(PROMPT)) % ft_get_winsz()->ws_col) == 0)
			tputs(tgetstr("do", NULL), 1, ft_putchar_tc);
	}
}

void				ft_tab(t_dlist **list, int visual, t_mlist *mlist)
{
	int				i;
	int				j;
	int				k;
	int				exec;
	char			*sub;
	char			*str;

	k = 0;
	while (g_cmd[g_idx] && g_cmd[g_idx] != ' ')
		ft_r_arrow(list, visual, mlist);
	i = g_idx;
	while (g_cmd[k] && g_cmd[k] != ' ')
		k++;
	exec = (k == i) ? 1 : 0;
	while (i > 0 && g_cmd[i - 1] != ' ')
		i--;
	sub = ft_strsub(g_cmd, i, g_idx - i);
	str = ft_autocomp(sub, exec, mlist);
	free(sub);
	j = g_idx;
	if (str)
	{
		ft_memmove(g_cmd + g_idx + ft_strlen(str),
					g_cmd + g_idx, ft_strlen(g_cmd + g_idx));
		ft_memmove(g_cmd + g_idx, str, ft_strlen(str));
		ft_putstr(g_cmd + g_idx);
		g_idx += ft_strlen(g_cmd + g_idx);
		if (ft_get_winsz()->ws_col > 0 
			&& ((ft_strlen(g_cmd) + ft_strlen(PROMPT))
			% ft_get_winsz()->ws_col) == 0)
			tputs(tgetstr("do", NULL), 1, ft_putchar_tc);
		while (g_idx > (int)(j + ft_strlen(str)))
			ft_l_arrow(NULL, 0, NULL);
		free(str);
	}
}
