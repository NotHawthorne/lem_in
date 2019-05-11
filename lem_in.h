/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:17:34 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/11 15:59:58 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define MAX_ROOMS 5000

#include "libft/libft.h"
#include "ft_hashtables.h"
#include <unistd.h>

typedef struct		s_hashes
{
	char			*data[MAX_ROOMS];
	unsigned long	keys[MAX_ROOMS];
	unsigned long	dead_keys[MAX_ROOMS];
	size_t			size;
}					t_hashes;

typedef	struct		s_map
{
	int				ants;
	char			*start;
	char			*end;
	char			**rooms;
	char			**links;
	char			***paths;
	t_hash_list		*room_hashes;
	t_table			*hash_table;
	unsigned long	**hash_paths;
	unsigned long	hash_start;
	unsigned long	hash_end;
	unsigned long	**hash_links;
	t_hashes		*hash_info;
}					t_map;

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
int				max_flow(t_map *in);
int				add_hash_link(t_map *in, char *link);
int				hash_step(t_map *in);
int				is_valid_hash_path(unsigned long *path, t_map *in);
int				is_independant(unsigned long *path, unsigned long **pathlist, t_map *in);
int				independant_hash_paths(unsigned long *path, t_map *in);
int				hash_paths_len(unsigned long **path);
int				hash_path_num(unsigned long **paths);
unsigned long	**best_hash_paths(t_map *in);
unsigned long	**add_to_hash_list(unsigned long **hashlist, unsigned long *hashes);
unsigned long	*get_links(t_map *in, char *room);
void			add_link_arr(unsigned long **tst, unsigned long room);
void			hash_rooms(t_map *in);
void			print_paths(t_map *map);

#endif
