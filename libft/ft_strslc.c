/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 12:56:09 by alkozma           #+#    #+#             */
/*   Updated: 2019/02/17 20:07:28 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strslc(char *str, size_t start, size_t end)
{
	size_t	i;
	size_t	plc;
	size_t	len;
	char	*tmp;

	i = 0;
	plc = 0;
	len = ft_strlen(str) + 1;
	if (!(tmp = ft_strdup(str)))
		return (NULL);
	ft_bzero(str, len);
	while (i <= len)
	{
		if (i >= start && i <= end)
			i++;
		else
			str[plc++] = tmp[i++];
	}
	ft_strdel(&tmp);
	return (str);
}
