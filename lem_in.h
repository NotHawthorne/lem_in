/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:17:34 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/25 01:08:00 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include <unistd.h>

typedef	struct	s_map
{
	int			ants;
	char		*start;
	char		*end;
	char		**rooms;
	char		**links;
	char		***paths;
}				t_map;

int				add_room(t_map *in, char *room);
int				add_link(t_map *in, char *link);
int				step(t_map *in);
int				is_valid_path(char **path, t_map *in);
void			print_rooms(t_map *in);
void			print_paths(t_map *map);
char			**get_links(t_map *in, char *room);

#endif
