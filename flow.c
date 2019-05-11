/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 01:22:57 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/11 15:20:41 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_independant(unsigned long *path, unsigned long **pathlist, t_map *in)
{
	int	i;
	int	n;
	int	b;

	i = 0;
	if (!is_valid_hash_path(path, in))
			return (0);
	while (pathlist[i]) {
		b = 0;
		while (pathlist[i][b]) {
			n = 0;
			while (path[n]) {
				if (path[n] == pathlist[i][b] &&
						path[n] != in->hash_start && path[n] != in->hash_end)
					return (0);
				n++;
			}
			b++;
		}
		i++;
	}
	return (1);
}

int		independant_hash_paths(unsigned long *path, t_map *in)
{
	int				i;
	int				ret;
	unsigned long	**cur;

	if (!(cur = (unsigned long**)malloc(sizeof(unsigned long*) * 2)))
		return (0);
	cur[0] = path;
	cur[1] = NULL;
	i = -1;
	ret = 0;
	while (in->hash_paths[++i])
	{
		if (is_independant(in->hash_paths[i], cur, in))
		{
			ret++;
			cur = ft_realloc(cur, sizeof(unsigned long*) * (ret + 1), sizeof(unsigned long*) * (ret + 2));
			cur[ret + 1] = NULL;
			cur[ret] = in->hash_paths[i];
		}
	}
	return (ret);
}

int		max_flow(t_map *in)
{
	int		i;
	int		b;
	unsigned long	*links;

	i = 0;
	b = 0;
	links = get_links(in, in->start);
	while (links[i])
		i++;
	links = get_links(in, in->end);
	while (links[b])
		b++;
	return (i > b ? i : b);
}

unsigned long **add_to_hash_list(unsigned long **hashlist, unsigned long *hashes)
{
	int	i;
	int	b;
	int	x;
	
	i = 0;
	b = 0;
	x = 0;
	while (hashlist[i])
		i++;
	if (hashlist[0])
		hashlist = ft_realloc(hashlist, sizeof(unsigned long*) * (i + 1), sizeof(unsigned long*) * (i + 2));
	while (hashes[b])
		b++;
	hashlist[i] = (unsigned long*)malloc(sizeof(unsigned long) * (b + 1));
	hashlist[i + 1] = 0;
	hashlist[i][b] = 0;
	while (hashes[x])
	{
		hashlist[i][x] = hashes[x];
		x++;
	}
	return (hashlist);
}

int		hash_path_num(unsigned long **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}

int		hash_paths_len(unsigned long **paths)
{
	int	i;
	int	b;
	int	ret;

	i = 0;
	ret = 0;
	while (paths[i])
	{
		b = 0;
		while (paths[i][b])
		{
			ret++;
			b++;
		}
		i++;
	}
	return (ret);
}

unsigned long	**best_hash_paths(t_map *in)
{
	int		i;
	unsigned long	**ret;
	int		flow;
	int		paths;

	flow = max_flow(in);
	ret = (unsigned long**)malloc(sizeof(unsigned long*) * 2);
	ret[1] = 0;
	ret[0] = 0;
	paths = 0;
	while (flow >= 0)
	{
		i = 0;
		while (in->hash_paths[i])
		{
			if (independant_hash_paths(in->hash_paths[i], in) >= flow && is_independant(in->hash_paths[i], ret, in) && is_valid_hash_path(in->hash_paths[i], in))
				ret = add_to_hash_list(ret, in->hash_paths[i]);
			if (hash_path_num(ret) == flow + 1)
				break;
			i++;
		}
		if (in->ants < hash_paths_len(ret) / (flow + 1) && flow > 0)
		{
			free(ret);
			ret = NULL;
			ret = (unsigned long**)malloc(sizeof(unsigned long*) * 2);
			ret[1] = NULL;
			ret[0] = NULL;
		}
		flow--;
	}
	return (ret);
}
