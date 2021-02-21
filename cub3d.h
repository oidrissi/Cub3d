/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:46:15 by oidrissi          #+#    #+#             */
/*   Updated: 2021/02/21 18:07:38 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "mlx.h"
# define WIDTH	1920
# define HEIGHT	1024
# define PX	150
# define PY	150

int g_a;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

int				main(void);
int				key_hook(int keycode, t_vars *vars);
int				mouse_hook(int button, int x, int y, void *param);
int				ft_putchar(int c);
void			ft_putnbr(int n);

#endif