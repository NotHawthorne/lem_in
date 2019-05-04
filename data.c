/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:41:11 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/27 09:15:41 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_rooms(t_map *in)
{
	int	i;

	i = 0;
	while (in->rooms[i])
		ft_printf("%s\n", in->rooms[i++]);
}

void	add_link_arr(char ***tst, char *room)
{
	int	i;
	char	**rooms;

	i = 0;
	rooms = *tst;
	while (rooms && rooms[i])
		i++;
	if (!rooms[0])
	{
		rooms = (char**)ft_realloc(rooms, sizeof(char*), sizeof(char*) * 2);
		rooms[0] = room;
		rooms[1] = NULL;
	}
	else
	{
		rooms = (char**)ft_realloc(rooms, sizeof(char*) * (i + 1), sizeof(char*) * (i + 2));
		rooms[i] = ft_strdup(room);
		rooms[i + 1] = NULL;
	}
	*tst = rooms;
}

char	**get_links(t_map *in, char *room)
{
	char	**ret;
	char	**tmp;
	int		i;

	i = 0;
	if (!(ret = (char**)malloc(sizeof(char*))))
		return (NULL);
	ret[0] = NULL;
	while (in->links && in->links[i])
	{
		tmp = ft_strsplit(in->links[i], '-');
		if (ft_strcmp(room, tmp[0]) == 0)
			add_link_arr(&ret, tmp[1]);
		if (ft_strcmp(room, tmp[1]) == 0)
			add_link_arr(&ret, tmp[0]);
		i++;
	}
	return (ret);
}

int		add_link(t_map *in, char *link)
{
	int		i;

	i = 0;
	while (in->links && in->links[i])
		i++;
	in->links = ft_realloc(in->links, (i + 1) * sizeof(char*), (i + 2) * sizeof(char*));
	in->links[i] = ft_strdup(link);
	in->links[i + 1] = NULL;
	return (1);
}

int		add_room(t_map *in, char *room)
{
	int		i;

	i = 0;
	while (in->rooms && in->rooms[i])
		i++;
	in->rooms = ft_realloc(in->rooms, (i + 1) * sizeof(char*), (i + 2) * sizeof(char*));
	in->rooms[i] = ft_strdup(room);
	in->rooms[i + 1] = NULL;
	return (1);
}

