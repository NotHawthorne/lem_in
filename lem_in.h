/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:17:34 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/22 14:02:17 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include <unistd.h>

typedef struct		s_room t_room;
typedef struct		s_link t_link;
typedef struct		s_path t_path;
typedef struct		s_path_list	t_path_list;

typedef struct		s_room
{
	int				ant_id;
	char			*room_id;
	t_link			*links;
	char			flag;
	t_room			*next;
}					t_room;

typedef struct		s_link
{
	t_room			*dst_room;
	t_link			*next;
}					t_link;

typedef struct		s_map
{
	int				ants;
	t_room			*rooms;
	t_room			*start;
	t_room			*end;
}					t_map;

typedef struct		s_path
{
	t_room			*room;
	t_path			*next;
	t_path			*prev;
	int				len;
}					t_path;

typedef struct		s_path_list
{
	t_path			*path;
	int				length;
	t_path_list		*next;
}					t_path_list;

void				print_path(t_path *p, t_map *m);
t_path				*find_end(t_map *in);
int					guide_ants(t_map *in);
int					add_room(t_map *in, char *str, char flag);
int					create_link(t_room *strc, t_room *dst);
int					room_link(char *str, t_map *in);
int					init_map(t_map *in);
int					max_flow(t_map *in);

#endif
