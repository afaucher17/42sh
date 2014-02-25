/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_fun3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 12:27:20 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/02/24 15:31:46 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"42sh.h"

void				ft_alt_u_arrow(t_dlist **list, int visual)
{
	int					x;

	x = 0;
	while (x < ft_get_winsz()->ws_col && g_idx > 0)
	{
		ft_l_arrow(list, visual);
		if (ft_get_copy()->visual_mode)
			visual--;
		x++;
	}
}

void					ft_alt_d_arrow(t_dlist **list, int visual)
{
	int					x;

	x = 0;
	while (x < ft_get_winsz()->ws_col && g_cmd[g_idx])
	{
		ft_r_arrow(list, visual);
		if (ft_get_copy()->visual_mode)
			visual++;
		x++;
	}
}

void					ft_alt_l_arrow(t_dlist **list, int visual)
{
	while ((g_idx - 1) >= 0 && g_cmd[g_idx - 1] == ' ')
	{
		ft_l_arrow(list, visual);
		if (ft_get_copy()->visual_mode)
			visual--;
	}
	while ((g_idx - 1) >= 0 && g_cmd[g_idx - 1] != ' ')
	{
		ft_l_arrow(list, visual);
		if (ft_get_copy()->visual_mode)
			visual--;
	}
}

void				ft_alt_r_arrow(t_dlist **list, int visual)
{
	while (g_cmd[g_idx] && g_cmd[g_idx] != ' ')
	{
		ft_r_arrow(list, visual);
		if (ft_get_copy()->visual_mode)
			visual++;
	}
	while (g_cmd[g_idx] && g_cmd[g_idx] == ' ')
	{
		ft_r_arrow(list, visual);
		if (ft_get_copy()->visual_mode)
			visual++;
	}
}
