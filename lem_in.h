/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:17:34 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/15 16:36:53 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include <unistd.h>

typedef struct		s_room
{
	int				ant_id;
	char			*room_id;
	struct	t_link	*links;
}					t_room;

typedef struct		s_link
{
	struct	t_room	*dst_room;
	struct	t_link	*next;
}					t_link;

typedef struct		s_map
{
	int				ants;
	struct	s_room	*rooms;
}					t_map;

#endif
