/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:35:49 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/21 14:37:57 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		strl;
	size_t		i;
	char		*scpy;

	i = 0;
	strl = ft_strlen(s1);
	scpy = (char *)malloc(sizeof (char) * (strl + 1));
	if (scpy == NULL)
		return (0);
	while (i < strl)
	{
		scpy[i] = s1[i];
		i++;
	}
	scpy[i] = '\0';
	return (scpy);
}
