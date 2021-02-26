/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:38:44 by oidrissi          #+#    #+#             */
/*   Updated: 2021/02/26 18:05:30 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mapX = 8;
int mapY = 8;
int mapS = 64;

int map[] = {
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,1,0,1,
	1,0,0,1,0,0,0,1,
	1,0,1,1,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void	draw_square(int x, int y, int x1, int y1)
{
	int tmp;
	tmp = x;
	while (y1 > y)
	{
		x = tmp;
		while (x1 > x)
		{
			my_mlx_pixel_put(&g_img, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	draw_line(int x, int y, int x1, int y1)
{
	while (x1 > x)
	{
		my_mlx_pixel_put(&g_img, x, y, 0x00FF00);
		x++;
	}
}

void draw_circle(int x, int y, int r)
{
      static const double PI = 3.1415926535;
      double i, angle, x1, y1, rayon;
	  
	  for (rayon = 0; rayon <= r; rayon++)
	  {
		for(i = 0; i < 360; i += 0.1)
      	{
        	angle = i;
        	x1 = rayon * cos(angle * PI / 180);
        	y1 = rayon * sin(angle * PI / 180);
        	my_mlx_pixel_put(&g_img, x + x1, y + y1, 0xFF0000);
      	}
	  }
}

void	drawmap_2d(void)
{
	int x, y, xo, yo;
	y = 0;
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			xo = (x * mapS) + mapS - 1;
			yo = (y * mapS) + mapS - 1;
			if (map[y * mapX + x] == 1)
				draw_square(x * mapS, y * mapS, xo, yo);
			x++;
		}
		y++;
	}
}

int			key_hook(int keycode, t_vars *vars)
{
	g_img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	g_img.addr = mlx_get_data_addr(g_img.img, &g_img.bits_per_pixel, &g_img.line_length,
								&g_img.endian);
	
	drawmap_2d();
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == 0)
		g_px -= 10;
	else if (keycode == 1)
		g_py += 10;
	else if (keycode == 2)
		g_px += 10;
	else if (keycode == 13)
		g_py -= 10;
	draw_circle(g_px, g_py, 5);
	mlx_put_image_to_window(vars->mlx, vars->win, g_img.img, 0, 0);
	return (0);
}