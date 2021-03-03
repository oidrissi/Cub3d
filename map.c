/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:53:58 by oidrissi          #+#    #+#             */
/*   Updated: 2021/03/03 17:55:17 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map(char *str)
{
	int			i;
	static int	stringnblines = 0;
	static int	stringsizeline = 0;

	i = 0;
	if (ft_is_map(str) == 1)
	{
		if (g_file->f == -1 || g_file->c == -1 || g_file->no == NULL ||
				g_file->so == NULL || g_file->we == NULL ||
				g_file->ea == NULL || g_file->sp == NULL)
			g_file->erreur = 2;
		if ((i = ft_strlen(str)) > stringsizeline)
			stringsizeline = i;
		stringnblines = stringnblines + 1;
	}
	g_file->nblines = stringnblines;
	g_file->sizeline = stringsizeline;
}

int		ft_is_map(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (ft_charinstr(str, '1') == 1 || ft_charinstr(str, '0') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
					&& str[i] != '\t')
			{
				if (g_file->insidemap == 1)
					g_file->wrongcharmap = 2;
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}