/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:23:22 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/06 16:38:06 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "fcntl.h"

t_map	*init_map(void)
{
	t_map	*map;
	char	*line;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	get_next_line(0, &line);
	ft_printf("%s\n", line);
	map->start = NULL;
	map->ants = ft_atoi(line);
	map->end = NULL;
	map->rooms = NULL;
	map->links = (char**)malloc(sizeof(char*) * 2);
	map->links[0] = NULL;
	map->links[1] = NULL;
	map->paths = (char***)malloc(sizeof(char**) * 2);
	map->paths[0] = (char**)malloc(sizeof(char*) * 2);
	map->paths[1] = NULL;
	map->paths[0][0] = NULL;
	map->paths[0][1] = NULL;
	return (map);
}

void	free_map(t_map *map)
{
	free(map->start);
	free(map->end);
	free(map->rooms);
	free(map->links);
	map->start = NULL;
	map->end = NULL;
	map->rooms = NULL;
	map->links = NULL;
	free(map);
	map = NULL;
}

int		main(void)
{
	char	*line;
	char	*tmp;
	t_map	*map;

	if (!(map = init_map()))
		return (0);
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (line[0] == '#')
		{
			tmp = ft_strdup(line);
			if (get_next_line(0, &line) == 0)
				break;
			ft_printf("%s\n", line);
			if (ft_strcmp(tmp, "##start") == 0)
			{
				map->start = ft_strsplit(line, ' ')[0];
				map->paths[0][0] = ft_strdup(map->start);
			}
			if (ft_strcmp(tmp, "##end") == 0)
				map->end = ft_strsplit(line, ' ')[0];
			free(tmp);
			tmp = NULL;
		}
		else
		{
			if (ft_strchr(line, '-'))
				add_link(map, line);
			else if (ft_strchr(line, ' '))
				add_room(map, ft_strsplit(line, ' ')[0]);
		}
	}
	ft_printf("\n");
	step(map);
	map->paths = best_paths(map);
	print_paths(map);
	free_map(map);
}

void	print_paths(t_map *map)
{
	int	i;
	int	n;

	i = 0;
	while (map->paths[i])
	{
		if (is_valid_path(map->paths[i], map))
		{
			n = 0;
			while (map->paths[i][n])
				ft_printf("%s->", map->paths[i][n++]);
			ft_printf(" (%d independant paths)\n", independant_paths(map->paths[i], map));
		}
		i++;
	}
}
