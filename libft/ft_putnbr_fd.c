/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 17:49:36 by tdieumeg          #+#    #+#             */
/*   Updated: 2013/12/29 15:23:14 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include            "libft.h"

void				ft_putnbr_fd(int nb, int fd)
{
	unsigned int	storage;

	storage = 1;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	if (nb == 0)
		ft_putchar_fd('0', fd);
	while (nb > 0)
	{
		storage = storage * 10 + (nb % 10);
		nb = nb / 10;
	}
	while (storage > 1)
	{
		ft_putchar_fd((storage % 10) + 48, fd);
		storage = storage / 10;
	}
}
