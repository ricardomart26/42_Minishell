/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:16:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/03 00:00:45 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>

// # define ABS(X) if (X < 0) X *= -1;
// # define PRINT(X, F) printf(#X " is %"#F " and the address is %p\n", X, &X);
// # define SQR(X, C)  \
// 	while (C-- > 1) \
// 		X *= X;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_vec
{
	size_t	bytes;
	size_t	lenght;
	size_t	capacity;
	void	*buffer;
}	t_vec;

bool	is_space(char c);
void	malloc_guard(void **alloc_var, int size, int data_type_size);
void	pow_int(int *nbr, const int power);
void	pow_long(long *nbr, const int power);
void	pow_float(float *nbr, const int power);
void	pow_double(double *nbr, const int power);
void	pow_biglong(long long *nbr, const int power);
bool	range_biglong(long long nbr, long long min, long long max);
bool	range_long(long nbr, long min, long max);
bool	range_int(int nbr, int min, int max);
bool	range_float(float nbr, float min, float max);
bool	range_double(double nbr, double min, double max);
char	*search_word_sp(char *str, char *word, bool debug);
char	*search_word(char *str, char *word, bool debug);
t_vec	init_vec(size_t	capacity, size_t bytes);
void	error_msg(const char *str);
char	*convert_hexa(unsigned int n, const int control);
char	*get_env_path(char **envp);
bool	check_ext(const char *file, const char *ext);
char	*strjoin3(const char *s1, const char *s2, const char *s3);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
bool	ft_isalnum(const int c);
bool	ft_isalpha(const int c);
bool	ft_isascii(const int c);
bool	ft_isdigit(const int c);
bool	ft_isprint(const int c);
char	*ft_itoa(const int n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, const int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, const int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(const char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strnstr(const char *haystack, const char *needle,
			size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putchar_fd(const char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
char	*ft_strndup(const char *s1, int len);
char	*ft_strdup_and_free(char **s1);
char	*ft_str3join(const char *s1, const char *s2, const char *s3);
int		ft_strlen_range(const char *str, size_t st, size_t end);
int		ft_strlen_c(const char *str, char c);
char	*ft_strdup_range(const char *s1, int st, int end);
int		get_next_line(int fd, char **line);
int		ft_strlen_dp(const char	**s1);
char	**ft_strdup_dp(const char **s1);
void	print_dp(void **r, int fd, int len);
char	*magic_eraser(char *str, char *set, bool f);
bool	find_c_in_str(int c, char *str);
char	**convert_list_to_array(t_list *lista);

#endif
