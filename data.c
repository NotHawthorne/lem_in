/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:41:11 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/13 05:10:38 by alkozma          ###   ########.fr       */
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
	return (in->hash_info->matrix[ft_hash(room)]);
}

int		add_hash_link(t_map *in, char *link)
{
	unsigned long	h1;
	unsigned long	h2;
	char	**splitres;
	size_t	arr_sz;

	splitres = ft_strsplit(link, '-');
	if (!splitres || !splitres[1] || !splitres[0])
		return (0);
	h1 = ft_hash(splitres[0]);
	h2 = ft_hash(splitres[1]);
	arr_sz = 0;
	while (in->hash_info->matrix[h1][arr_sz])
		arr_sz++;
	in->hash_info->matrix[h1][arr_sz] = h2;
	arr_sz = 0;
	while (in->hash_info->matrix[h2][arr_sz])
		arr_sz++;
	in->hash_info->matrix[h2][arr_sz] = h1;
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
