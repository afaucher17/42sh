/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 18:19:27 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/17 20:48:43 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

char 				*g_cmd = NULL;
int					g_idx = 0;

static int			ft_get_fun(int buff, t_dlist **list, int noctrld,
								t_mlist *mlist)
{
	int				j;
	static t_keys	key_tab[14] =
	{
		{DELETE, ft_delete}, {BACKSPACE, ft_backspace}, {HOME, ft_home},
		{END, ft_end}, {ALT_U_A, ft_alt_u_arrow}, {ALT_D_A, ft_alt_d_arrow},
		{ALT_L_A, ft_alt_l_arrow}, {ALT_R_A, ft_alt_r_arrow},
		{U_ARROW, ft_u_arrow}, {D_ARROW, ft_d_arrow}, {L_ARROW, ft_l_arrow},
		{R_ARROW, ft_r_arrow}, {TAB, ft_tab}, {CTRL_D, ft_ctrl_d}
	};

	j = 0;
	while (j < (14 - noctrld))
	{
		if (key_tab[j].key == buff)
		{
			if (!(ft_get_copy()->visual_mode))
				key_tab[j].f(list, 0, mlist);
			else
				key_tab[j].f(list, g_idx - ft_get_copy()->start, mlist);
		}
		j++;
	}
	return (j);
}

static void			ft_get_visual(int buff)
{
	if (buff == ALT_C)
	{
		ft_get_copy()->start = g_idx;
		ft_get_copy()->visual_mode ^= 1;
		if (!ft_get_copy()->visual_mode)
		{
			free(ft_get_copy()->copy);
			if (g_idx < ft_get_copy()->start)
				ft_get_copy()->copy =
						ft_strsub(g_cmd, g_idx, ft_get_copy()->start - g_idx);
			else
				ft_get_copy()->copy =
						ft_strsub(g_cmd, ft_get_copy()->start,
										g_idx - ft_get_copy()->start);
		}
	}
}

static void			ft_aff_key(char c)
{
	int				j;

	j = g_idx;
	if ((c >= 10 && c <= 15) || (c >= 32 && c <= 126))
	{
		ft_putstr(g_cmd + g_idx);
		g_idx += ft_strlen(g_cmd + g_idx);
		if (ft_get_winsz()->ws_col > 0
				&& ((ft_strlen(g_cmd) + ft_strlen(PROMPT))
				% ft_get_winsz()->ws_col) == 0)
			tputs(tgetstr("do", NULL), 1, ft_putchar_tc);
		while (g_idx > j + 1)
			ft_l_arrow(NULL, 0, NULL);
	}
}

static void			ft_insert(int j, char c, int noctrld)
{
	if (c >= 32 && c <= 126 && j == (14 - noctrld))
	{
		ft_memmove(g_cmd + g_idx + 1, g_cmd + g_idx, ft_strlen(g_cmd + g_idx));
		g_cmd[g_idx] = c;
	}
}

char				*ft_read_keys(t_dlist *list, int noctrld, t_mlist *mlist)
{
	t_dlist			*save;
	int				buff;
	int				j;
	char			c;

	save = list;
	if (g_cmd == NULL)
		g_cmd = ft_strnew(BUFF_SIZE);
	while (42)
	{
		buff = 0;
		if (read(0, &buff, sizeof(int)))
		{
			c = buff & 0x000000FF;
			if (buff == RETURN)
			{
				ft_return(&save, 0, mlist);
				return (ft_strdup(g_cmd));
			}
			j = ft_get_fun(buff, &list, noctrld, mlist);
			ft_insert(j, c, noctrld);
			ft_aff_key(c);
			ft_get_visual(buff);
		}
	}
}
