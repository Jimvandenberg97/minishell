/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:10:37 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/11/23 13:51:18 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdarg.h>

/*
** Defines
*/

# define GNL_BUFFER_SIZE 128
# define CHARSET_BASE "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

/*
** Structs
*/

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** Converter Functions
*/

char				*ft_itoa(int n);
char				*ft_lotoa(long n);
char				*ft_uitoa(unsigned int n);
char				*ft_uitohex(unsigned int n);
int					ft_atoi(const char *str);
long long			ft_atol(const char *str);
size_t				ft_getnumlen(long long num, int base);

/*
** ASCII Functions
*/

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isspace(char c);

/*
** Memory Functions
*/

int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);

/*
** String Functions
*/

char				**ft_split(char const *s, char c);
char				*ft_str_replace(const char *haystack, const char *needle, \
						size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free1(char const *s1, char const *s2);
char				*ft_strjoin_free2(char const *s1, char const *s2);
char				*ft_strjoin_free12(char const *s1, char const *s2);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);

/*
** IO Functions
*/

int					ft_get_next_line(int fd, char **line);

/*
** Write Functions
*/

int					ft_putint_base(long num, size_t base, int uc);
int					ft_putnbr_base(unsigned long long num, size_t base, \
						int sign, int uc);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char *s);
void				ft_putstr_fd(char *s, int fd);

/*
** List Functions
*/

int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));

/*
** Printf
*/

typedef struct		s_struct
{
	size_t			i;
	int				padd;
	char			padd_dir;
	char			padd_char;
	int				prec;
	int				prec_zero;
	int				prec_neg;
	int				len;
	int				upper;
	int				sign;
	int				min;
	int				width;
	int				zero;
	int				error;
}					t_config;

int					ft_printf(const char *format, ...);
void				parse(const char *format, t_config *cfg, va_list ap);
t_config			*cfg_init(void);
void				cfg_reset(t_config *cfg);
void				printer(const char *format, t_config *cfg, va_list ap);
void				print_pcnt(t_config *cfg);
int					print_padd(char c, int count);
void				ft_print_num(t_config *cfg, va_list ap);
void				ft_print_hex(const char *format, t_config *cfg, va_list ap);
void				ft_print_char(t_config *cfg, va_list ap);
void				ft_print_string(t_config *cfg, va_list ap);
void				ft_print_uint(t_config *cfg, va_list ap);
void				ft_print_pointer(t_config *cfg, va_list ap);
void				print_clear(t_config *cfg);
void				ft_error(t_config *cfg);

#endif
