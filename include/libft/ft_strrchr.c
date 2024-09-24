/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:06:35 by lstorey           #+#    #+#             */
/*   Updated: 2023/11/23 14:19:21 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	ch;

	ch = (char)c;
	len = 0;
	while (s[len] != 0)
		len++;
	if (ch == '\0')
		return ((char *)s + len);
	while (len >= 0)
	{
		if (s[len] == ch)
			return ((char *)(s + len));
		len--;
	}
	return (0);
}
