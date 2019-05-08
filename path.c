/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 05:10:42 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/06 21:43:59 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		ft_printf("%s->", path[i++]);
	ft_printf("\n");
}

void	add_path(char ***paths, char **path, char *room, t_map *in)
{
	int	i;
	int	n;
	int x;

	i = 0;
	while (paths[i])
		i++;
	paths = (char***)ft_realloc(paths, sizeof(char**) * (i + 1), sizeof(char**) * (i + 2));
	n = 0;
	while (path[n])
		n++;
	paths[i] = (char**)malloc(sizeof(char*) * (n + 2));
	paths[i + 1] = NULL;
	x = 0;
	while (paths[i][x] && x < n)
	{
		paths[i][x] = ft_strdup(path[x]);
		x++;
	}
	paths[i][n] = ft_strdup(room);
	paths[i][n + 1] = NULL;
	in->paths = paths;
}

void	append_path(char ***paths, char **path, char *room, t_map *in, int index)
{
	int	i;

	i = 0;
	ft_printf("BEFORE\n");
	print_path(path);
	while (path[i])
		i++;
	path = (char**)ft_realloc(path, sizeof(char*) * (i + 1), sizeof(char*) * (i + 2));
	path[i] = room;
	path[i + 1] = NULL;
	paths[index] = path;
	in->paths = paths;
	ft_printf("AFTER\n");
	print_path(path);
}

int		is_valid_path(char **path, t_map *in)
{
	int	i;
	int	fs;
	int	fe;

	i = 0;
	fs = 0;
	fe = 0;
	while (path[i])
	{
		if (ft_strcmp(path[i], in->start) == 0)
			fs += 1;
		if (ft_strcmp(path[i], in->end) == 0)
			fe += 1;
		if (fs == 1 && fe == 1)
			return (1);
		i++;
	}
	return (0);
}

int		check_path(char **path, char *room, t_map *in)
{
	int	i;

	i = -1;
	while (path[++i])
		if (ft_strcmp(path[i], room) == 0 || ft_strcmp(path[i], in->end) == 0)
			return (0);
	return (1);
}

int		step(t_map *in)
{
	int		i;
	int		x;
	int		n;
	char	**links;
	int		found;

	i = 0;
	found = 0;
	ft_printf("STEPPING\n");
	while (in->paths[i])
	{
		n = 0;
		while (in->paths[i][n])
			n++;
		n--;
		links = get_links(in, in->paths[i][n]);
		x = 0;
		while (links[x])
		{
			if (check_path(in->paths[i], links[x], in))
			{
				add_path(in->paths, in->paths[i], links[x], in);
				if (ft_strcmp(links[x], in->end) == 0)
					found++;
			}
			x++;
		}
		i++;
	}
	ft_printf("STEPPED\n");
	return (1);
}
