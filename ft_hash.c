/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 02:28:33 by alkozma           #+#    #+#             */
/*   Updated: 2019/05/11 07:26:40 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtables.h"

unsigned long	ft_hash(const void *s)
{
	unsigned long	hash;
	unsigned char	x;

	hash = 5381;
	while ((x = *(char*)s++)) {
		hash = ((hash << 5L) + hash) + x;
	}
	return (hash % 5000);
}

void			add_to_table(const void *data, t_table *table,
		size_t data_size)
{
	int		bit_size;
	t_data	*new_data;

	bit_size = data_size * 8;
	if (!table->data)
	{
		table->data = (t_data**)malloc(sizeof(t_data*) * 2);
		table->data[1] = NULL;
		table->data[0] = NULL;
	}
	else
		table->data = ft_realloc(table->data, (table->size + 1) * 8, (table->size + 2) * 8);
	if (!(new_data = (t_data*)malloc(sizeof(t_data))))
		return ;
	new_data->data = (void*)data;
	new_data->hash = ft_hash(data);
	table->data[table->size] = new_data;
	table->data[table->size + 1] = NULL;
	table->size++;
}

void			*find_in_table(t_table *table, unsigned long hash)
{
	int	i;

	i = 0;
	while (table->data && table->data[i])
	{
		if (table->data[i]->hash == hash)
			return (table->data[i]->data);
		i++;
	}
	return (NULL);
}

t_hash_list		*create_hash_list(int n, unsigned long list[])
{
	t_hash_list	*ret;
	int			size;
	int			i;
	int			probe;

	size = (int) (n * 1.1 + 1);
	ret = malloc(sizeof(*ret) + sizeof(unsigned long) * (size - 1));
	if (!ret)
		return (NULL);
	ret->size = size;
	i = 0;
	while (i < size) {
		ret->hashes[i++] = 0;
	}
	for(i = 0; i < n; i++) {
		for(probe = list[i] % ret->size;
				ret->hashes[probe] != 0;
				probe = (probe + 1) % ret->size);
		ret->hashes[probe] = list[i];
	}
	return ret;	
}

void			*fetch_from_table(t_table *table, unsigned long key)
{
	int		i;

	i = key % table->size;
	while (table->data[i])
	{
		ft_printf("STEP");
		if (table->data[i]->hash == key)
			return (table->data[i]->data);
		i++;
	}
	return (NULL);
}

int				hash_list_contains(unsigned long *list, unsigned long hash, size_t size)
{
	unsigned long	probe;
	int				i;

	i = 0;
	ft_printf("probe starting at %d | %lu %d\n", hash % size, hash, size);
	for(probe = hash % size;
        list[probe] != 0;
        probe = (probe + 1) % size) 
	{
		//ft_printf("|||||||||%lu\n", list[probe]);
		i++;
        if(list[probe] == hash) {
			ft_printf("Found in %d steps\n", i);
            return (probe);
        }
    }
	return (0);
}
