/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 01:22:57 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/06 21:43:56 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		path_cmp(char **path1, char **path2, t_map *in)
{
	int	i;
	int	b;

	i = 0;
	while (path1[i])
	{
		b = 0;
		while (ft_strcmp(path1[i], in->start) && ft_strcmp(path1[i], in->end) && path2[b])
		{
			if (!ft_strcmp(path1[i], path2[b]) && ft_strcmp(path2[b], in->start) && ft_strcmp(path2[b], in->end))
				return (0);
			b++;
		}
		i++;
	}
	return (1);
}

int		ft_strstrstr(char **strs, char *str)
{
	int	i;
	int	b;

	i = 0;
	while (strs[i])
	{
		b = 0;
		if (ft_strstr(str, strs[i++]))
			return (1);
	}
	return (0);
}

int		start_end_check(char *str, t_map *in)
{
	if (ft_strcmp(str, in->start) && ft_strcmp(str, in->end))
		return (0);
	return (1);
}

int		independant_paths(char **path, t_map *in)
{
	int		i;
	int		y;
	int		x;
	char	*currooms;

	i = 0;
	y = 0;
	currooms = ft_strjoin_array(path, "");
	while (in->paths[i])
	{
		x = 0;
		while (in->paths[i][x])
		{
			if (!start_end_check(in->paths[i][x], in) && ft_strstr(currooms, in->paths[i][x]))
				break;
			x++;
		}
		if (is_valid_path(in->paths[i], in) && path_cmp(path, in->paths[i], in) && !ft_strcmp(in->end, in->paths[i][x - 1]))
		{
			y++;
			currooms = ft_strjoin(currooms, ft_strjoin_array(in->paths[i], ""));
		}
		i++;
	}
	return (y);
}

int		complimentary_path(char ***paths, char **path, t_map *in)
{
	int		i;
	int		b;
	char	*currooms;

	i = 0;
	currooms = ft_strjoin_array(path, "");
	while (paths[i])
	{
		b = 0;
		while (paths[i][b])
		{
			if (ft_strstr(currooms, paths[i][b]) && ft_strcmp(paths[i][b], in->start) && ft_strcmp(paths[i][b], in->end))
				return (0);
			b++;
		}
		i++;
	}
	return (1);
}

int		max_flow(t_map *in)
{
	int		i;
	int		b;
	char	**links;

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

char	***add_to_list(char ***paths, char **path)
{
	int	i;
	int	b;
	int	x;

	i = 0;
	b = 0;
	x = 0;
	while (paths[i])
		i++;
	if (paths[0])
		paths = ft_realloc(paths, sizeof(char**) * (i + 1), sizeof(char**) * (i + 2));
	while (path[b])
		b++;
	paths[i] = (char**)malloc(sizeof(char*) * (b + 1));
	paths[i + 1] = NULL;
	paths[i][b] = NULL;
	while (path[x])
	{
		paths[i][x] = path[x];
		x++;
	}
	return (paths);
}

int		paths_len(char ***paths)
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
			b++;
			ret++;
		}
		i++;
	}
	return (ret);
}

int		path_num(char ***paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}

char	***best_paths(t_map *in)
{
	int		i;
	char	***ret;
	int		flow;
	int		paths;

	flow = max_flow(in);
	ret = (char***)malloc(sizeof(char**) * 2);
	ret[1] = NULL;
	ret[0] = NULL;
	paths = 0;
	while (flow >= 0)
	{
		i = 0;
		while (in->paths[i])
		{
			if (independant_paths(in->paths[i], in) >= flow && complimentary_path(ret, in->paths[i], in) && is_valid_path(in->paths[i], in))
				ret = add_to_list(ret, in->paths[i]);
			if (path_num(ret) == flow + 1)
				break;
			i++;
		}
		if (in->ants < paths_len(ret) / (flow + 1) && flow > 0)
		{
			free(ret);
			ret = NULL;
			ret = (char***)malloc(sizeof(char**) * 2);
			ret[1] = NULL;
			ret[0] = NULL;
		}
		flow--;
	}
	return (ret);
}
