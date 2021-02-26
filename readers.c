/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:13:28 by oidrissi          #+#    #+#             */
/*   Updated: 2021/02/26 18:48:48 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file_data	init_map_data()
{
	g_file->r = {0, 0};
	g_file->f = {0, 0, 0};
	g_file->c = {0, 0, 0};
	g_file->w = NULL;
	g_file->ea = NULL;
	g_file->n = NULL;
	g_file->so = NULL;
	return (*g_file);
}



void	parse_init(char *line)
{
	if (line[0] != g_file)
	{
		ft_printf("Error in the .cub file");
		exit(0);
	}
	else
		if (g_file->r != {0, 0})
			ft_set_right_res(g_file->r);
		if (g_file->f != {0, 0, 0} || g_file->c != {0, 0, 0})
			ft_set_color(g_file->f, g_file->c);
		if (g_file->w != NULL)
			ft_set_w_text(g_file->w);
		if (g_file->ea != NULL)
			ft_set_ea_text(g_file->ea);
		if (g_file->n != NULL)
			ft_set_n_text(g_file->n);
		if (g_file->so != NULL)
			ft_set_so_text(g_file->so);
		
}

void	read_file(int fd, char *filename)
{
	/**
	** STORE RESOLUTION OF WINDOW THEN
	** STORE MAP->DETAILS: R: Resolution, F: Floor Color, S: Sky Color,
	** 					  Textures: W: West, E: East, N: North, SO: South
	**
	** OPENS .cub file starts reading line by line then compares
	** each line with get_next_line::
	** if (line[0] = MAP->DETAILS [array of char: R F S W, E, N, SO])
	**	treat_specific_detail;
	** else
	** If First line different than MAP->DETAILS
	** Return Error Message with STDERROR
	** ELSE
	**
	**
	**
	**/

	t_file_data map_data;
	char	*line;
	int		ret;
	
	fd = open("world.cub", O_RDONLY);
	ret = get_next_line(fd, &line);
	// if file descriptor has no lines return 
	if (ret == -1)
		ft_printf("File Cannot be Read");
	else if (ret == 0)
		ft_printf("Nothing to show");
	else
		parse_init(line);
	// if (line[i] != 
}

int		ft_cub(char *str)
{
	init_map_data();
	if ()
	
}

int		ft_check_save(int save)
{
	char *saved;
	
	if (saved == "--save")
		return (1);
	return (0);
}

int		main(int argc, char *argv[])
{
	g_file->save = 0;
	ft_init()
	if (argc == 2 || (argc == 3 && ft_check_save(argv[2]) == 1))
	{
		if (argc == 3)
			recup.save = 1;
		ft_cub(argv[1], &recup);
	}
	else
		write(1, "Error\nArguments invalides\n", 30);
}