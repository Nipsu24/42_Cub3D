/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:13:07 by lstorey           #+#    #+#             */
/*   Updated: 2024/04/11 13:44:35 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# define FT_LONG_MAX 9223372036854775807L

/* ************************************************************************** */
/*                           Libft library                                    */
/* ************************************************************************** */
void		ft_bzero(void *s, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		**ft_split(char const *s, char c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char*s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strrchr(const char *s, int c);
char		*ft_itoa(int n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
int			ft_tolower(int c);
int			ft_toupper(int c);

/* ************************************************************************** */
/*							ft_printf library                                 */
/* ************************************************************************** */

int			print_format(char specifier, va_list ap, int *check);
int			print_char(int c, int *check);
int			print_str(char *s, int *check);
int			print_digit(long n, int base, int *check);
int			ft_printf(const char *format, ...);
int			print_pnt(unsigned long n, unsigned long base, int *check);
int			print_hex_upper(long n, int base, int *check);
int			print_hex_lower(long n, int base, int *check);

/* ************************************************************************** */
/*							GNL library      		                          */
/* ************************************************************************** */

typedef struct s_list
{
	char			*content;
	struct s_list	*next;

}	t_list;

char	*get_next_line(int fd);
void	create_list(t_list **list, int fd);
int		found_newline(t_list *list);
void	append(t_list **list, char *buf);
char	*get_lin(t_list	*list);
void	polish_list(t_list **list);
int		len_to_newline(t_list *list);
void	copy_str(t_list *list, char *next_str);
void	dealloc(t_list **list, t_list *clean_node, char *buf);
t_list	*find_last_node(t_list *list);

#endif