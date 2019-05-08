#include "lem_in.h"

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
	while (placed_ants <= nb_ants)
	{
        if (!paths)
            paths = head;
        while (paths && ++placed_ants <= nb_ants)
        {
		    list_addant(&ants, paths->rooms, placed_ants);
            paths = paths->next;
		}
		step_ants(&ants);
		ft_printf("\n");
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
}