/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:45:45 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/24 11:35:08 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*nstr;
	size_t		m;

	if (start > ft_strlen(s))
		return ((char *) ft_calloc(1, 1));
	if (ft_strlen(s) - (size_t)start < len)
		m = ft_strlen(s) - start;
	else
		m = len;
	nstr = (char *) malloc(m * sizeof(char) + 1);
	if (!nstr)
		return (NULL);
	i = 0;
	while (i < m)
	{
		nstr[i] = s[start];
		i++;
		start++;
		if (!s)
			return (nstr);
	}
	nstr[i] = '\0';
	return (nstr);
}
