/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:36:59 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/23 10:50:51 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*nstr;

	if (!s1 || !set)
		return ((char *)s1);
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	len = ft_strlen(s1);
	if (len == 0)
	{
		nstr = ft_calloc(1, sizeof(char));
		return (nstr);
	}
	while (ft_strchr(set, s1[len - 1]))
		len--;
	return (ft_substr(s1, 0, len));
}
