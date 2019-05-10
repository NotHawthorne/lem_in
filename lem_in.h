/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:17:34 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/06 21:43:57 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/libft.h"
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

typedef struct 		s_room
{
	char			*name;
	struct s_room	*next;
}					t_room;

typedef struct		s_path
{
	t_room			*rooms;
	struct s_path	*next;
}					t_path;

typedef struct 		s_ant
{
	int				nb;
	t_room			*rooms;
	struct s_ant	*next;
	struct s_ant	*last;
}					t_ant;

int				add_room(t_map *in, char *room);
int				add_link(t_map *in, char *link);
int				step(t_map *in);
int				independant_paths(char **path, t_map *in);
int				path_length(char **path);
int				is_valid_path(char **path, t_map *in);
int				complimentary_path(char ***paths, char **path, t_map *in);
int				max_flow(t_map *in);
char			***add_to_list(char ***paths, char **path);
char			***best_paths(t_map *in);
void			print_rooms(t_map *in);
void			print_paths(t_map *map);
void			print_path(char **path);
char			**get_links(t_map *in, char *room);

#endif
