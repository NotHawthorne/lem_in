/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:18:46 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/17 20:45:51 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_node(t_room *rm, t_path *path)
{
	t_path	*tmp;
	t_path	*ret;
	int		i;

	i = 0;
	if (!(ret = (t_path*)malloc(sizeof(t_path))))
		return ;
	tmp = path;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	ret->len = i;
	ret->room = rm;
	ret->prev = tmp;
	if (!tmp->room)
		*path = *ret;
	else
		tmp->next = ret;
}

t_path	*move_back_one(t_path *p)
{
	t_path *tmp;

	tmp = p;
	while (tmp->next)
		tmp = tmp->next;
	tmp = tmp->prev;
	free(tmp->next);
	tmp->next = NULL;
	return (tmp);
}

int		visited(t_room *tmp, t_room *stack)
{
	t_room *tst;

	tst = stack;
	while (tst && tmp && tst->next)
	{
		if (!(tst->room_id))
			break ;
		if (ft_strcmp(tmp->room_id, tst->room_id) == 0)
			return (1);
		tst = tst->next;
	}
	return (0);
}

void	add_to_stack(t_room *room, t_room *stack)
{
	t_room	*tmp;

	tmp = stack;
	if (!tmp->room_id)
	{
		*stack = *room;
		stack->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = room;
		tmp->next->next = NULL;
	}
}

t_path	*find_end(t_map *in)
{
	t_path	*ret;
	t_room	*tmp;
	t_room	*stack;
	int		i;

	if (!(stack = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	if (!(ret = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	tmp = in->start;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->room_id, in->end->room_id) == 0)
			break ;
		if (visited(tmp, stack))
			tmp = move_back_one(ret)->room;
		else
		{
			add_to_stack(tmp, stack);
			add_node(tmp, ret);
			if (ft_strcmp(tmp->room_id, in->end->room_id) == 0)
				return (ret);
			while (tmp->links->dst_room && visited(tmp->links->dst_room, stack))
				tmp->links = tmp->links->next;
			if (!tmp->links)
				tmp = move_back_one(ret)->room;
			else
			{
				tmp = tmp->links->dst_room;
				if (ret->next)
					ret = ret->next;
			}
		}
	}
	return (ret);
}

void	print_path(t_path *p, t_map *m)
{
	t_path	*tmp;

	tmp = p;
	ft_printf("%s\n", m->end->room_id);
	while (tmp)
	{
		if (ft_strcmp(tmp->room->room_id, m->start->room_id) == 0)
			break ;
		ft_printf("%s\n", tmp->room->room_id);
		tmp = tmp->prev;
	}
	ft_printf("%s\n", m->start->room_id);
}

int		guide_ants(t_map *in)
{
	init_map(in);
	return (0);
}
