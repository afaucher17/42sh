/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/06 15:03:45 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/06 15:53:21 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							ft_atoi_base(const char *str, int basenb)
{
	int						result;
	int						i;
	int						is_neg;
	static const char		*base = "0123456789ABCDEF";
	char					*sub;

	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	is_neg = (str[i] == '-') ? -1 : 1;
	i += (str[i] == '+' || str[i] == '-');
	sub = ft_strsub(base, 0, basenb);
	while (str[i] && ft_strchr(sub, ft_toupper(str[i])))
	{
		result = result * basenb;
		result = result + (ft_strchr(sub, ft_toupper(str[i])) - sub);
		i++;
	}
	free(sub);
	result = result * is_neg;
	return (result);
}
