/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:15:48 by alkozma           #+#    #+#             */
/*   Updated: 2019/04/27 09:03:32 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;

	i = 0;
	ret = 0;
	if (s1 && s2)
	{
		if (!(ret = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
			return (NULL);
		while (*s1)
			ret[i++] = *s1++;
		while (*s2)
			ret[i++] = *s2++;
		ret[i] = '\0';
	}
	return (ret);
}

char	*ft_strjoin_array(char **strs, char *tok)
{
	char	*ret;
	int		i;

	ret = ft_strnew(1);
	i = 0;
	while (strs[i])
	{
		ret = ft_strjoin(ret, strs[i++]);
		if (strs[i])
			ret = ft_strjoin(ret, tok);
	}
	return (ret);
}
