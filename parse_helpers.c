/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:51:33 by oidrissi          #+#    #+#             */
/*   Updated: 2021/03/03 19:21:08 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi_resolution(char *str)
{
	int		i;

	i = 0;
	if (str[1] != ' ' || ft_charinstr((char *)str, ',') == 1)
		g_file->erreur = 2;
	while (str[g_file->i] == ',' && (str[g_file->i] == '\n' ||
			str[g_file->i] == '\r' || str[g_file->i] == ' ' ||
			str[g_file->i] == '\t' || str[g_file->i] == '\v' ||
			str[g_file->i] == '\f'))
		g_file->i++;
	if (str[g_file->i] == '-' || str[g_file->i] == '+')
		g_file->erreur = 2;
	while (str[g_file->i] >= '0' && str[g_file->i] <= '9')
	{
		if (i > 21474836)
			break;
		i = i * 10 + (str[g_file->i] - 48);
		g_file->i++;
	}
	while (str[g_file->i] >= '0' && str[g_file->i] <= '9')
		g_file->i++;
	return (i);
}

int		ft_nb_virgule(char *str)
{
	int		i;
	int		size;
	int 	checked;
	
	checked = 0;
	i = 0;
	if ((size = ft_strlen(str)) == 0)
		return (0);
	while (i++ <= size)
	{
		if (str[i] == ',')
			checked++;
	}
	return (checked);
}

void	ft_atoi_check_color(char *str)
{
    int     i;
    int		comma_check;
    
    i = 0;
	comma_check = 0;
    while (str[i] != ',')
        i++;
    if (str[i] == ',')
		comma_check = 1;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
    while ((str[i] < '0' && str[i] > '9') && str[i])
	{
		if (str[i] == ',')
			comma_check++;
		i++;
	}
	if (comma_check != 2)
		g_file->erreur = 2;
	if (ft_nb_virgule(str) != 2)
		g_file->erreur = 2;
}

int		ft_atoi_color(char *str)
{
	int		i;
	
	i = 0;
	if (str[1] != ' ')
		g_file->erreur = 2;
	ft_atoi_check_color(str);
	while (str[g_file->i] == ',' && (str[g_file->i] == '\n' ||
			str[g_file->i] == '\r' || str[g_file->i] == ' ' ||
			str[g_file->i] == '\t' || str[g_file->i] == '\v' ||
			str[g_file->i] == '\f'))
	{
		g_file->i++;
		i = 0;
		if (str[g_file->i] >= '0' && str[g_file->i] <= '9')
			g_file->index++;
		while (str[g_file->i] >= '0' && str[g_file->i] <= '9')
		{
			i = i * 10 + (str[g_file->i] - 48);
			g_file->sum = (g_file->sum * 10) + (str[g_file->i] - 48);
			g_file->i++;
		}
		if (str > 255 || str < 0)
		g_file->erreur = 2;
	}
	return (g_file->sum);
}

void	ft_texture(char *str)
{
	int		i;

	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O')
		ft_set_path_texture(g_file->no);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		ft_set_path_texture(g_file->so);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		ft_set_path_texture(g_file->we);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		ft_set_path_texture(g_file->ea);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		ft_set_path_texture(g_file->sp);
}

void	ft_color_resolution(char **str)
{
	int			i;

	i = 0;
	g_file->i = 1;
	if (g_file->sizeline > 0 && (g_file->no == NULL || g_file->so == NULL ||
				g_file->we == NULL || g_file->ea == NULL || g_file->sp == NULL))
		g_file->erreur = 2;
	if ((g_file->no != NULL || g_file->so != NULL || g_file->we != NULL ||
				g_file->ea != NULL || g_file->sp != NULL) && (g_file->rx == 0
				|| g_file->ry == 0))
		g_file->erreur = 2;
	if (*str[i] == 'R')
	{
		if (g_file->rx != 0 && g_file->ry != 0)
			g_file->erreur = 2;
		g_file->rx = ft_atoi_resolution(*str);
		g_file->ry = ft_atoi_resolution(*str);
		if (ft_atoi_resolution(*str) > 0 || g_file->rx == 0 || g_file->ry == 0)
			g_file->erreur = 2;
	}
	else if (*str[i] == 'F')
		g_file->f = ft_atoi_color(*str);
	else if (*str[i] == 'C')
		g_file->c = ft_atoi_color(*str);
}
