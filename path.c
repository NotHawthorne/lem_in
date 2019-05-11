/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 05:10:42 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/11 09:59:32 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_hash_path(unsigned long **paths, unsigned long *path,
					unsigned long room, t_map *in)
{
	int	i;
	int	n;
	int x;

	i = 0;
	while (paths[i])
		i++;
	paths = (unsigned long**)ft_realloc(paths, sizeof(unsigned long*) * (i + 1), sizeof(unsigned long*) * (i + 2));
	n = 0;
	while (path[n])
		n++;
	paths[i] = (unsigned long*)ft_memalloc(sizeof(unsigned long) * (n + 2));
	paths[i + 1] = 0;
	x = 0;
	while (path[x] && x < n)
	{
		paths[i][x] = path[x];
		x++;
	}
	paths[i][n] = room;
	paths[i][n + 1] = 0;
	in->hash_paths = paths;
}

int		is_valid_hash_path(unsigned long *path, t_map *in)
{
	int		i;
	int		fs;
	int		fe;

	i = 0;
	fs = 0;
	fe = 0;
	while (path[i])
	{
		if (path[i] == in->hash_start)
			fs += 1;
		if (path[i] == in->hash_end)
			fe += 1;
		if (fs >= 1 && fe >= 1)
			return (1);
		i++;
	}
	return (0);
}

int		check_hash_path(unsigned long *path, unsigned long room, t_map *in)
{
	int	i;

	i = -1;
	while (path[++i])
		if (path[i] == room || path[i] == in->hash_end)
			return (0);
	return (1);
}

int		hash_step(t_map *in)
{
	int		i;
	int		x;
	int		n;
	unsigned long	*links;

	i = 0;
	while (in->hash_paths[i])
	{
		n = 0;
		while (in->hash_paths[i][n])
			n++;
		n--;
		links = get_links(in, in->hash_info->data[in->hash_paths[i][n]]);
		x = 0;
		while (links[x])
		{
			if (check_hash_path(in->hash_paths[i], links[x], in))
				add_hash_path(in->hash_paths, in->hash_paths[i], links[x], in);
			x++;
		}
		i++;
	}
	return (1);
}
