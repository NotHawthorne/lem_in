/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtables.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 02:27:38 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/11 05:12:16 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASHTABLES_H
# define FT_HASHTABLES_H

# include "libft/libft.h"

typedef struct		s_data
{
	unsigned long	hash;
	void			*data;
}					t_data;

typedef struct		s_table
{
	size_t			size;
	t_data			**data;
}					t_table;

typedef struct		s_hash_list
{
	size_t			size;
	unsigned long	hashes[1];
}					t_hash_list;

unsigned long		*seed_table(const char *salt, size_t arr_size);
unsigned long		ft_hash(const void *s);
void				add_to_table(const void *data, t_table *table,
									size_t data_size);
void				*find_in_table(t_table *table, unsigned long hash);
t_hash_list			*create_hash_list(int n, unsigned long list[]);
int					hash_list_contains(unsigned long *list,
										unsigned long hash, size_t size);
void				*fetch_from_table(t_table *table, unsigned long key);
void				compare_boi();

#endif
