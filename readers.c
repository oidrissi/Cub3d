/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:13:28 by oidrissi          #+#    #+#             */
/*   Updated: 2021/03/03 17:42:15 by oidrissi         ###   ########.fr       */
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

int		ft_atoi_color(char *str)
{
	int		i;
	
	i = 0;
	if (str[1] != ' ')
		g_file->erreur = 2;
	ft_atoi_check_color();
	while (str[g_file->i] =                                                                                                  = ',' && (str[g_file->i] == '\n' ||
			str[g_file->i] == '\r' || str[g_file->i] == ' ' ||
			str[g_file->i] == '\t' || str[g_file->i] == '\v' ||
			str[g_file->i] == '\f')
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
		if (ft_atoi2(*str, g_file) > 0 || g_file->rx == 0 || g_file->ry == 0)
			g_file->erreur = 2;
	}
	else if (*str[i] == 'F')
		g_file->f = ft_atoi_color(*str);
	else if (*str[i] == 'C')
		g_file->c = ft_atoi_color(*str);
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
