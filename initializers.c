/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:52:28 by oidrissi          #+#    #+#             */
/*   Updated: 2021/03/03 18:16:24 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	t_file_data	init_map_data(void)
{
	g_file->r = NULL;
	g_file->f = NULL;
	g_file->c = NULL;
	g_file->we = NULL;
	g_file->ea = NULL;
	g_file->no = NULL;
	g_file->so = NULL;
	g_file->sp = NULL;
	g_file->ry = 0;
	g_file->i = 0;
	g_file->erreur = 0;
	g_file->nblines = 0;
	g_file->sizeline = 0;
	g_file->count = 0;
	g_file->index = 0;
	g_file->sum = 0;
	g_file->insidemap = 0;
	g_file->wrongcharmap = 0;
	g_file->emptyline = 0;
	return (*g_file);
}