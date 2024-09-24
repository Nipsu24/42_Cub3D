/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:30:56 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/14 13:44:47 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		(*f)(i, &s[i]);
		i++;
	}
}
