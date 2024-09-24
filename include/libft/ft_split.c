/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:20:30 by lstorey           #+#    #+#             */
/*   Updated: 2024/03/27 16:26:48 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static size_t	str_cntr(char const *str, char delim)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == delim)
			++str;
		if (*str == '\0')
			return (count);
		++count;
		while (*str && *str != delim)
			++str;
	}
	return (count);
}

static char	**free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	arr_pnt;
	size_t	count;

	arr_pnt = 0;
	count = str_cntr(s, c);
	array = malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (arr_pnt < count)
	{
		while (*s == c)
			s++;
		array[arr_pnt] = ft_substr(s, 0, str_len(s, c));
		if (!array[arr_pnt])
			return (free_array(array));
		s += str_len(s, c);
		arr_pnt++;
	}
	array[arr_pnt] = NULL;
	return (array);
}

// #include<stdio.h>

// int main()
// {
//     char    *str;
//     char    del;
//     char    **result;
//     int i;

//     i = 0;
//     str = "lorem ipsum dolor Suspendisse";
//     del = ' ';

//     result = ft_split(str, del);

//     for(; i < 5;)
//         printf("%s\n", result[i++]);
//     return  (0);
// }
