/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 20:49:44 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/22 14:02:18 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		max_flow(t_map *in)
{
	int		i;
	int		b;
	t_link	*tmp;
	t_room	*tmprm;

	i = 0;
	b = 0;
	tmp = in->start->links;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tmprm = in->start;
	while (tmprm)
	{
		tmp = tmprm->links;
		while (tmp)
		{
			if (ft_strcmp(tmp->dst_room->room_id, in->end->room_id) == 0)
				b++;
			tmp = tmp->next;
		}
		tmprm = tmprm->next;
	}
	return (i > b ? b : i);
}
