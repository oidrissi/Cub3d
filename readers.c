/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:13:28 by oidrissi          #+#    #+#             */
/*   Updated: 2021/03/01 19:09:57 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file_data	init_map_data()
{
	g_file->r = 0;
	g_file->f = 0;
	g_file->c = 0;
	g_file->we = NULL;
	g_file->ea = NULL;
	g_file->no = NULL;
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
	{
		if (g_file->r != 0)
			ft_set_right_res(g_file->r);
		if (g_file->f != 0 || g_file->c != 0)
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
}

int		parse_map(char *file)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	fd = open(file, O_RDONLY);
	if (!(g_file->map = malloc(sizeof(char*) * g_file->nblines)))
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		if (g_file->insidemap == 1 && ft_emptyline(str) == 0 &&
				g_file->count < g_file->nblines)
			g_file->emptyline = 1;
		if ((g_file->insidemap = ft_is_map(str)) == 1)
		{
			g_file->count++;
			ft_copy_map(str, g_file);
		}
		free(str);
	}
	close(fd);
	ft_init_sprite();
	return (0);
}

void	parse_file(char *file)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	if ((fd = open(file, O_DIRECTORY)) != -1)
		print_error("Invalid : second argument is a directory\n");
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error("File .cub invalid\n");
	g_file->erreur = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		if (g_file->erreur == 2)
			print_error("Parsing can't be done, the file is corrupted\n");
		ft_color_resolution(&str);
		ft_texture(str);
		ft_map(str);
		free(str);
	}
	close(fd);
	if (g_file->sizeline == 0 || g_file->nblines == 0)
		ft_error("Map absente\n");
	parse_map(file);
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
		g_file->rx = ft_atoi2(*str, g_file);
		g_file->ry = ft_atoi2(*str, g_file);
		if (ft_atoi2(*str, g_file) > 0 || g_file->rx == 0 || g_file->ry == 0)
			g_file->erreur = 2;
	}
	else if (*str[i] == 'F')
		g_file->f = ft_atoi3(*str, g_file);
	else if (*str[i] == 'C')
		g_file->c = ft_atoi3(*str, g_file);
}

int		ft_charinstr(char *str, char s)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == s)
			return (1);
	}
	return (0);
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

void	ft_map(char *str)
{
	int			i;
	static int	snblines = 0;
	static int	ssizeline = 0;

	i = 0;
	if (ft_is_map(str) == 1)
	{
		if (g_file->f == -1 || g_file->c == -1 || g_file->no == NULL ||
				g_file->so == NULL || g_file->we == NULL ||
				g_file->ea == NULL || g_file->sp == NULL)
			g_file->erreur = 2;
		if ((i = ft_strlen(str)) > ssizeline)
			ssizeline = i;
		snblines = snblines + 1;
	}
	g_file->nblines = snblines;
	g_file->sizeline = ssizeline;
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

int		check_format_file(char *str)
{
	int		i;
	
	while(str[i])
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
			print_error("Invalid file");
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		parse_file(str);
	else
		print_error("Invalid file format");
}

int		ft_check_save(char *saved)
{
	if (saved != "--save")
		return (0);
	return (1);
}


 /* Function to save image to file without loading the game to the screen but secretly opening it in the background */
 
int		screenshot()
{
	if (g_file->save == 1)
		return (0);
	
}

int		main(int argc, char *argv[])
{
	g_file->save = 0;
	ft_init();
	if (argc == 2 || (argc == 3 && ft_check_save(argv[2]) == 1))
	{
		if (argc == 3)
			g_file->save = 1;
		check_format_file(argv[1]);
	}
	else
		write(1, "Error\nArguments invalides\n", 30);
}
