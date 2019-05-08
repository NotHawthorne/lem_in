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

void	new_path(t_path **paths)
{
	t_path *new;

	new = ft_memalloc(sizeof(t_path));
	new->rooms = NULL;
	new->next = *paths;
	*paths = new;
}

void	list_makeroom(t_room **room, char *name)
{
	t_room *new;

	new = ft_memalloc(sizeof(t_room));
	new->name = name;
	new->next = NULL;
	if (*room)
		(*room)->next = new;
	else
		*room = new;
}

void	list_addroom(t_path *path, char *name)
{
	t_room	*rooms;

	if (path->rooms)
	{
		rooms = path->rooms;
		while (rooms->next)
			rooms = rooms->next;
		list_makeroom(&rooms, name);
	}
	else
	{
		list_makeroom(&(path->rooms), name);
	}
}

void	list_printpaths(t_path *paths)
{
	t_room *rooms;
	int i = 0;
	if (!paths)
		return ;
	while (paths)
	{
		ft_printf("path: %d\n", i++);
		rooms = paths->rooms;
		while (rooms)
		{
			ft_printf("%s->", rooms->name);
			rooms = rooms->next;
		}
		ft_printf("end\n");
		paths = paths->next;
	}
}

void	list_makeant(t_ant **ants, t_room *rooms, int ant_nb)
{
	t_ant	*new;

	new = ft_memalloc(sizeof(t_ant));
	*new = (t_ant){ant_nb, rooms, NULL, NULL};
	if (*ants)
	{
		(*ants)->next = new;
		new->last = *ants;
	}
	else
		*ants = new;
}

void	list_addant(t_ant **ants, t_room *rooms, int ant_nb)
{
	t_ant	*cpy_ants;

	
	if (*ants)
	{
		cpy_ants = *ants;
		while (cpy_ants->next)
			cpy_ants = cpy_ants->next;
		list_makeant(&cpy_ants, rooms, ant_nb);
	}
	else
	{
		list_makeant(ants, rooms, ant_nb);
	}
	//ft_printf("adding ant #%d, room: %s", ant_nb, rooms->name);
}

void	remove_ant(t_ant **cpy, t_ant **ants)
{
	t_ant *tmp;
	t_ant	*next;

	tmp = *cpy;
	if (!(*ants)->next)
	{
		free(*ants);
		*ants = NULL;
		*cpy = NULL;
	}
	else if ((*cpy)->next)
	{
		next = (*cpy)->next;
		if ((*cpy)->last)
			(*cpy)->last->next = (*cpy)->next;
		(*cpy)->next->last = (*cpy)->last;
		if ((*cpy)->nb == (*ants)->nb)
			*ants = next;
		free(*cpy);
		*cpy = next;
	}
	else if ((*cpy)->last)
	{
		(*cpy)->last->next = NULL;
		free(tmp);
		*cpy = NULL;
	}
	else if (!(*cpy)->next)
	{
		free(tmp);
		*cpy = NULL;
	}
}

void	step_ants(t_ant **ants)
{
	t_ant	*cpy;

	cpy = *ants;
	while (cpy)
	{
		if (cpy->rooms)
		{
			cpy->rooms = cpy->rooms->next;
			if (cpy->rooms)
			{
				ft_printf("L%d-%s ", cpy->nb, cpy->rooms->name);
				cpy = cpy->next;
			}
			else
				remove_ant(&cpy, ants);
		}
		else
			cpy = cpy->next;
	}
}

void	release_ants(t_path *paths, int nb_ants)
{
	int	placed_ants;
	t_ant	*ants;
	t_path	*head;

	head = paths;
	ants = NULL;
	placed_ants = 0;
	while (++placed_ants <= nb_ants)
	{
		list_addant(&ants, paths->rooms, placed_ants);
		//ft_printf("%d ants placed of %d\n", placed_ants, nb_ants);
		step_ants(&ants);
		ft_printf("\n");
		if (!(paths)->next)
			paths = head;
		else
			paths = paths->next;
	}
	while (ants)
	{
		step_ants(&ants);
		ft_printf("\n");
	}
}

void	print_paths(t_map *map)
{
	int	i;
	int	n;
	t_path	*paths;

	paths = NULL;
	i = 0;
	while (map->paths[i])
	{
		if (is_valid_path(map->paths[i], map))
		{
			n = 0;
			new_path(&paths);
			while (map->paths[i][n])
			{
				list_addroom(paths, map->paths[i][n]);
				ft_printf("%s->", map->paths[i][n++]);
			}
			ft_printf(" (%d independant paths)\n", independant_paths(map->paths[i], map));
		}
		i++;
	}
	release_ants(paths, map->ants);
	//list_printpaths(paths);
}
