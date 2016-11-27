/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 20:14:11 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/26 20:16:58 by jlinden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_cd_freejoin(t_list *tmp, const char *str, char *to_join)
{
	if (tmp)
		free(tmp->content);
	tmp->content = ft_strjoin(str, to_join);
}
