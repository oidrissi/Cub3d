/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:54:19 by oidrissi          #+#    #+#             */
/*   Updated: 2021/02/26 17:59:01 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int		get_red(int trgb)
{
	return (rgb & (0xFF << 16));
}

int		get_green(int trgb)
{
	return (rgb & (0xFF << 8));
}

int		get_blue(int trgb)
{
	return (rgb & 0xFF);
}