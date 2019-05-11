/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:23:22 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/11 10:25:17 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "fcntl.h"

t_map	*init_map(void)
{
	t_map	*map;
	char	*line;

	if (!(map = (t_map*)ft_memalloc(sizeof(t_map))))
		return (NULL);
	get_next_line(0, &line);
	ft_printf("%s\n", line);
	map->start = NULL;
	map->ants = ft_atoi(line);
	map->end = NULL;
	map->rooms = NULL;
	map->links = (char**)ft_memalloc(sizeof(char*) * 2);
	map->links[0] = NULL;
	map->links[1] = NULL;
	map->paths = (char***)ft_memalloc(sizeof(char**) * 2);
	map->paths[0] = (char**)ft_memalloc(sizeof(char*) * 2);
	map->paths[1] = NULL;
	map->paths[0][0] = NULL;
	map->paths[0][1] = NULL;
	map->hash_paths = (unsigned long**)ft_memalloc(sizeof(unsigned long*) * 2);
	map->hash_paths[0] = (unsigned long*)ft_memalloc(sizeof(unsigned long) * 2);
	map->hash_paths[1] = NULL;
	map->hash_paths[0][0] = 0;
	map->hash_paths[0][1] = 0;
	map->hash_info = (t_hashes*)malloc(sizeof(t_hashes));
	map->hash_info->size = 0;
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
				map->hash_paths[0][0] = ft_hash(map->start);
				map->hash_start = ft_hash(map->start);
			}
			if (ft_strcmp(tmp, "##end") == 0)
			{
				map->end = ft_strsplit(line, ' ')[0];
				map->hash_end = ft_hash(map->end);
			}
			free(tmp);
			tmp = NULL;
		}
			if (ft_strchr(line, '-'))
				add_hash_link(map, line);
			else if (ft_strchr(line, ' '))
				add_room(map, ft_strsplit(line, ' ')[0]);
	}
	ft_printf("\n");
	hash_rooms(map);
	hash_step(map);
	map->hash_paths = best_hash_paths(map);
	print_paths(map);
	free_map(map);
	while (1)
	{

	}
}
