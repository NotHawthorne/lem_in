/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:11:47 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/27 06:20:11 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;

	ret = (char*)s;
	while (ret && *ret != (char)c && *ret != '\0')
		ret++;
	if (*ret == '\0' && (char)c != '\0')
		return (NULL);
	else
		return (ret);
}
