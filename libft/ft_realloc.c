/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 03:05:57 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/23 03:29:54 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *thing, size_t orig_size, size_t size)
{
	void	*ret;
	int		i;

	i = -1;
	if (!(ret = (void*)malloc(size)))
		return (NULL);
	if (!thing)
		return (ret);
	if (orig_size <= size)
		ft_memcpy(ret, thing, size);
	else
		ft_memcpy(ret, thing, orig_size);
	free(thing);
	thing = NULL;
	return (ret);
}
