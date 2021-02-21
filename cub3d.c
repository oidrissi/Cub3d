/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:28:59 by oidrissi          #+#    #+#             */
/*   Updated: 2021/02/21 19:10:50 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		cube_put(int i, int j, t_data img)
{
	while (i-- > 0)
	{
		j++;
		my_mlx_pixel_put(&img, 150 + j, 150, 0x00FF0000);
		my_mlx_pixel_put(&img, 150, 150 + j, 0x00FF0000);
		my_mlx_pixel_put(&img, 180, 150 + j, 0x00FF0000);
		my_mlx_pixel_put(&img, 150 + j, 180, 0x00FF0000);
	}
}

int			main(void)
{
	t_vars	vars;
	t_data	img;
	static int i;
	int j;

	i = 30;
	j = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 150, 150, 0x00FF0000);
	cube_put(i, j, img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}
