/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/06 19:37:44 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/07 18:24:15 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static char				*ft_solverdep(char **mold, char *seq,
										int size, char *res)
{
	int					i;
	int					j;
	int					k;

	i = 0;
	k = 0;
	while (i < size)
	{
		j = 0;
		while (mold[i][j])
		{
			if (mold[i][j] == 'x')
				mold[i][j] = seq[k++];
			j++;
		}
		i++;
	}
	i = -1;
	while (++i < size)
		res[i] = (char)ft_atoi_base(mold[i], 2);
	free(seq);
	ft_clear_tab(mold);
	return (res);
}

static char					*ft_solver(int size, char *seq)
{
	char					**mold;
	char					*res;
	int						i;
	int						j;

	i = 1;
	j = 0;
	res = ft_strnew(size);
	if ((mold = (char**)malloc(sizeof(char*) * (size + 1))) == NULL)
		return (0);
	mold[size] = NULL;
	mold[0] = ft_strnew(8);
	ft_memset(mold[0], 'x', 8);
	if (size == 1)
		mold[0][0] = '0';
	else
	{
		while (j < size && mold[0][j])
			mold[0][j++] = '1';
		mold[0][j] = '0';
	}
	while (i < size)
		mold[i++] = ft_strdup("10xxxxxx");
	return (ft_solverdep(mold, seq, size, res));
}

void						ft_itoutf(int nb)
{
	int						bound;
	static const int		bocp[6] = {7, 11, 16, 21, 26, 31};
	char					*str;
	char					*sequence;
	char					*res;

	bound = (nb >= 0 && nb <= 0x7F) ? 0 : 0; 
	bound = (nb >= 0x80 && nb <= 0x7FF) ? 1 : bound; 
	bound = (nb >= 0x800 && nb <= 0xFFFF) ? 2 : bound; 
	bound = (nb >= 0x10000 && nb <= 0x1FFFFF) ? 3 : bound; 
	bound = (nb >= 0x200000 && nb <= 0x3FFFFFF) ? 4 : bound; 
	bound = (nb >= 0x4000000 && nb <= 0x7FFFFFFF) ? 5 : bound;
	sequence = ft_strnew(bocp[bound]);
	ft_memset(sequence, '0', bocp[bound]);
	str = ft_itoa_base(nb, 2);
	ft_strcpy(sequence + (bocp[bound] - ft_strlen(str)), str);
	free(str);
	res = ft_solver(bound + 1, sequence);
	ft_putstr(res);
	free(res);
}
