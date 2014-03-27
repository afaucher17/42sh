/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_fun4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 13:56:53 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/27 14:07:57 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void			ft_insert_comp(char *str, int j)
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
	str = NULL;
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
		ft_insert_comp(str, j);
	ft_strdel(&str);
}
