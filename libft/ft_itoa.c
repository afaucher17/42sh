/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 19:33:58 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/01/15 12:01:16 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static int	get_digit_nb(int n)
{
	int		i;
	int		m;

	m = n / 10;
	i = 0;
	while (m != 0)
	{
		i++;
		m = m / 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;

	i = get_digit_nb(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		i++;
	str = ft_strnew(i + 1);
	str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (i-- >= 0 && n != 0)
	{
		str[i + 1] = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}
