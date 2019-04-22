/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:17:11 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/22 13:24:03 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		add_room(t_map *in, char *str, char flag)
{
	t_room	*rm;
	t_room	*tmp;
	char	**arr;

	if (!(rm = (t_room*)malloc(sizeof(t_room))))
		return (0);
	arr = ft_strsplit(str, ' ');
	rm->ant_id = -1;
	rm->room_id = arr[0];
	rm->links = NULL;
	rm->flag = flag;
	rm->next = NULL;
	tmp = in->rooms;
	if (!tmp)
		in->rooms = rm;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = rm;
	}
	if (flag == 's')
		in->start = rm;
	if (flag == 'e')
		in->end = rm;
	return (1);
}

int		create_link(t_room *src, t_room *dst)
{
	t_link	*out;
	t_link	*tmp;

	if (!(out = (t_link*)malloc(sizeof(t_link))))
		return (0);
	out->dst_room = dst;
	tmp = src->links;
	if (!tmp)
		src->links = out;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = out;
	}
	return (1);
}

int		room_link(char *str, t_map *in)
{
	t_room	*tmp;
	t_room	*one;
	t_room	*two;
	char	*room_one;
	char	*room_two;

	tmp = in->rooms;
	room_one = ft_strsplit(str, '-')[0];
	room_two = ft_strsplit(str, '-')[1];
	while (tmp)
	{
		if (ft_strcmp(room_one, tmp->room_id) == 0)
			one = tmp;
		if (ft_strcmp(room_two, tmp->room_id) == 0)
			two = tmp;
		tmp = tmp->next;
	}
	create_link(one, two);
	create_link(two, one);
	return (0);
}

int		init_map(t_map *in)
{
	char	*line;
	int		line_num;
	char	flag;
	t_path	*tst;
	int		i;

	i = -1;
	if (!(in = (t_map*)malloc(sizeof(t_map))))
		return (0);
	in->ants = 0;
	in->rooms = NULL;
	line_num = 0;
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (line_num == 0)
			in->ants = ft_atoi(line);
		else
		{
			while (line[0] == '#' &&
					ft_strcmp("##start", line) != 0 &&
					ft_strcmp("##end", line) != 0)
				if ((i = get_next_line(0, &line)) == 0)
					break ;
			if (i == 0)
				break ;
			flag = ft_strcmp("##start", line) == 0 ? 's' : 'm';
			flag = ft_strcmp("##end", line) == 0 ? 'e' : flag;
			if (ft_strcmp(line, "##start") == 0 || ft_strcmp(line, "##end") == 0)
			{
				get_next_line(0, &line);
				ft_printf("%s\n", line);
			}
			if (ft_strchr(line, ' '))
				add_room(in, line, flag);
			else if (line)
				room_link(line, in);
		}
		line_num++;
	}
	ft_printf("\n");
	tst = find_end(in);
	ft_printf("MAX FLOW: %d\n", max_flow(in));
	return (0);
}
