/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:18:46 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/22 14:02:15 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*copy_path(t_path *path, t_room *room)
{
	t_path	*tmp;
	t_path	*ret;

	tmp = path;
	ret = (t_path*)malloc(sizeof(t_path));
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (!ret->room)
		{
			ret->room = tmp->room;
			ret->prev = NULL;
			ret->next = NULL;
		}
		else
		{
			ret->next = (t_path*)malloc(sizeof(t_path));
			ret->next->room = tmp->room;
			ret->next->prev = ret;
			ret->next->next = NULL;
			ret = ret->next;
		}
		tmp = tmp->next;
	}
	ret->next = (t_path*)malloc(sizeof(t_path));
	ret->next->room = room;
	ret->next->prev = ret;
	ret->next->next = NULL;
	while (ret->prev)
		ret = ret->prev;
	return (ret);
}

void	add_new_path(t_path_list *lst, t_path *path, t_room *room, t_map *in)
{
	t_path_list	*tmp;
	t_map		*m;
	t_path		*tmpath;
	int			i;

	i = 0;
	m = in;
	tmp = lst;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	tmpath = copy_path(path, room);
	tmp->next = (t_path_list*)malloc(sizeof(t_path_list));
	tmp->next->path = tmpath;
	tmp->next->next = NULL;
	tmp->next->length = 0;
}

int		step(t_path_list *lst, t_map *in)
{
	t_path_list	*tmp;
	t_path		*tmp_path;
	t_link		*tmp_link;

	tmp = lst;
	while (tmp)
	{
		tmp_path = tmp->path;
		while (tmp_path->next)
			tmp_path = tmp_path->next;
		tmp_link = tmp_path->room->links;
		while (tmp_link)
		{
			add_new_path(lst, tmp_path, tmp_link->dst_room, in);
			if (ft_strcmp(tmp_link->dst_room->room_id, in->end->room_id) == 0)
				return (1);
			tmp_link = tmp_link->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

int		is_full_path(t_path *path, t_map *in)
{
	t_path	*tmp;
	int		found_start;
	int		found_end;

	tmp = path;
	found_end = 0;
	found_start = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->room->room_id, in->end->room_id) == 0)
			found_end = 1;
		if (ft_strcmp(tmp->room->room_id, in->start->room_id) == 0)
			found_start = 1;
		if (found_end == 1 && found_start == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	print_path_list(t_path_list **p, t_map *in)
{
	t_path_list	*tmp;
	int			i;

	i = 0;
	tmp = *p;
	while (tmp)
	{
		if (is_full_path(tmp->path, in))
		{
			ft_printf("PATH %d\n", i++);
			print_path(tmp->path, in);
		}
		tmp = tmp->next;
	}
}

t_path	*find_end(t_map *in)
{
	t_path_list	*lst;
	t_path		*initpath;

	if (!(lst = (t_path_list*)malloc(sizeof(t_path_list))))
		return (NULL);
	if (!(initpath = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	initpath->room = in->start;
	initpath->prev = NULL;
	initpath->next = NULL;
	lst->path = initpath;
	while (step(lst, in) == 0) ;
	print_path_list(&lst, in);
	return (initpath);
}

void	print_path(t_path *p, t_map *m)
{
	t_path	*tmp;
	t_map	*map;

	map = m;
	tmp = p;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->room)
			ft_printf("%s\n", tmp->room->room_id);
		tmp = tmp->next;
	}
}

int		guide_ants(t_map *in)
{
	init_map(in);
	return (0);
}
