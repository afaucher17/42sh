/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 12:24:09 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/27 11:49:02 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	key_dispatch(t_select *g_slct, int key, int *pfd)
{
	int						i;
	static const t_keys2	keys[7] =

	{
	{SLCT_KEY_DOWN, slct_key_down},
	{SLCT_KEY_UP, slct_key_up},
	{SLCT_KEY_RETURN, slct_key_return},
	{SLCT_KEY_ESCAPE, slct_key_escape},
	{SLCT_KEY_RIGHT, slct_key_right},
	{SLCT_KEY_LEFT, slct_key_left},
	{0, NULL}
	};
	i = 0;
	while (keys[i].key)
	{
		if (keys[i].key == key)
		{
			keys[i].key_run(g_slct, pfd);
			return ;
		}
		i++;
	}
}
