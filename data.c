/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:41:11 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/11 09:53:32 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_link_arr(unsigned long **tst, unsigned long room)
{
	int				i;
	unsigned long	*rooms;

	i = 0;
	rooms = *tst;
	while (rooms && rooms[i])
		i++;
	if (!rooms[0])
	{
		rooms = (unsigned long*)ft_realloc(rooms, sizeof(unsigned long), sizeof(unsigned long) * 2);
		rooms[0] = room;
		rooms[1] = 0;
	}
	else
	{
		rooms = (unsigned long*)ft_realloc(rooms, sizeof(unsigned long) * (i + 1), sizeof(unsigned long) * (i + 2));
		rooms[i] = room;
		rooms[i + 1] = 0;
	}
	*tst = rooms;
}

unsigned long *get_links(t_map *in, char *room)
{
	unsigned long	*ret;
	unsigned long	hash;
	int				i;

	i = 0;
	hash = ft_hash(room);
	if (!(ret = (unsigned long*)ft_memalloc(sizeof(unsigned long))) || hash == 0)
		return (NULL);
	ret[0] = 0;
	while (in->hash_links[i])
	{
		if (hash == in->hash_links[i][0])
			add_link_arr(&ret, in->hash_links[i][1]);
		else if (hash == in->hash_links[i][1])
			add_link_arr(&ret, in->hash_links[i][0]);
		i++;
	}
	return (ret);
}

int		add_hash_link(t_map *in, char *link)
{
	int		i;
	char	**splitres;

	splitres = ft_strsplit(link, '-');
	if (!splitres || !splitres[1])
		return (0);
	i = 0;
	while (in->hash_links && in->hash_links[i])
		i++;
	in->hash_links = ft_realloc(in->hash_links, (i + 1) * sizeof(unsigned long*), (i + 2) * sizeof(unsigned long*));
	in->hash_links[i] = ft_memalloc(3 * sizeof(unsigned long));
	in->hash_links[i][0] = ft_hash(splitres[0]);
	in->hash_links[i][1] = ft_hash(splitres[1]);
	in->hash_links[i][2] = 0;
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

void	hash_rooms(t_map *in)
{
	int		i;
	t_table	*ret;
	if (!in->rooms)
		return ;
	if (!(ret = (t_table*)malloc(sizeof(t_table))))
		return ;
	ret->data = NULL;
	ret->size = 0;
	i = -1;
	while (in->rooms[++i])
		in->hash_info->data[ft_hash(in->rooms[i])] = in->rooms[i];
}
