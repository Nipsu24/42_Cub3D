/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:01:33 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/23 15:03:12 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	di;
	size_t	si;
	size_t	srcl;
	size_t	dstl;

	srcl = ft_strlen((char *) src);
	dstl = ft_strlen(dst);
	if (dstsize < dstl || dstsize == 0)
		return (srcl + dstsize);
	di = dstl;
	si = 0;
	while ((di < dstsize - 1) && (src[si] != '\0'))
	{
		dst[di] = src[si];
		di++;
		si++;
	}
	dst[di] = '\0';
	return (dstl + srcl);
}
