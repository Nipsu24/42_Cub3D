/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:31:59 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/22 14:38:47 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*n;
	char	*h;

	i = 0;
	j = 0;
	h = (char *)haystack;
	n = (char *)needle;
	if (*n == 0)
		return (h);
	if (*h == 0 || ft_strlen(n) > len)
		return (NULL);
	while ((i < len && *h) && (ft_strlen(n) <= len - i))
	{
		if ((ft_strncmp(h + i, n + j, ft_strlen(n))) == 0)
			return (h + i);
		else
			i++;
	}
	return (0);
}
