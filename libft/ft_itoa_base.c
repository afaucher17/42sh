/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/06 14:55:38 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/25 21:56:15 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"libft.h"

char				*ft_itoa_base(int n, int base)
{
	int				digit;
	const char		*tab = "0123456789abcdef";
	unsigned long	numb;
	char			*str;

	digit = 0;
	numb = n;
	while (n >= base)
	{
		digit++;
		n /= base;
	}
	str = ft_strnew(digit);
	str[digit + 1] = '\0';
	while (digit >= 0)
	{
		str[digit] = tab[numb % base];
		digit--;
		numb /= base;
	}
	return (str);
}
