/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:13:28 by oidrissi          #+#    #+#             */
/*   Updated: 2021/03/03 17:55:08 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			ft_copy_map(str);
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
		print_error(".cub file is invalid\n");
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

int		ft_charinstr(char *str, char s)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == s)
			return (1);
	}
	return (0);
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
