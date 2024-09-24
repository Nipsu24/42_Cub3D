/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:10:53 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/22 11:34:59 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	p;
	size_t			i;

	str = (unsigned char *)s;
	p = (unsigned char)c;
	i = 0;
	if (p == '\0' && *str == '\0' && n != 0)
		return (str);
	while (i < n)
	{
		if (str[i] == p)
			return (str + i);
		else
			i++;
	}
	return (NULL);
}
