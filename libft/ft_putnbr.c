/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 17:00:34 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/11/26 11:33:14 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include			"libft.h"

void				ft_putnbr(int nb)
{
	long int		storage;
	long int		nbis;

	storage = 1;
	nbis = nb;
	if (nbis < 0)
	{
		ft_putchar('-');
		nbis = nbis * -1;
	}
	if (nbis == 0)
		ft_putchar('0');
	while (nbis > 0)
	{
		storage = storage * 10 + (nbis % 10);
		nbis = nbis / 10;
	}
	while (storage > 1)
	{
		ft_putchar((storage % 10) + 48);
		storage = storage / 10;
	}
}
