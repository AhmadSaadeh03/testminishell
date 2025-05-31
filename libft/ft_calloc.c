/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghanem <fghanem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:09:08 by asaadeh           #+#    #+#             */
/*   Updated: 2025/05/31 13:06:03 by fghanem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	sum;

	sum = nmemb * size;
	p = malloc(sum);
	if (!p)
		return (NULL);
	else
		ft_bzero(p, sum);
	return (p);
}
