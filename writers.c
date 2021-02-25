/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:48:45 by oidrissi          #+#    #+#             */
/*   Updated: 2021/02/25 12:26:44 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_putchar(int c)
{
	if (c == '\0')
		return (write(1, &c, 1));
	return (write(1, &c, 1));
}

int		ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int		ft_atoi(const char *str)
{
	int			i;
	int			signe;
	long		z;

	z = 0;
	signe = 1;
	i = 0;
	while (str[i] && (str[i] == '\n' || str[i] == '\r' || str[i] == ' ' ||
				str[i] == '\t' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		z = z * 10 + (str[i] - 48);
		i++;
		if (z < 0 && signe > 0)
			return (-1);
		if (z < 0 && signe < 0)
			return (0);
	}
	return (signe * z);
}

void		ft_putnbr(int n)
{
	unsigned int nb;

	nb = n;
	if (n < 0)
	{
		ft_putchar('-');
		nb = -n;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}
