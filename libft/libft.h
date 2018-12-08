/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:03:22 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/11 21:06:13 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdarg.h>
# include <wchar.h>

# define BUFF_SIZE 1
# define DIOUX(x) (x == 'd' || x == 'i' || x == 'x' || x == 'o' || x == 'u')
# define DOUX(x) (x == 'D' || x == 'U' || x == 'O' || x == 'X')
# define CCSS(x) (x == 'c' || x == 's' || x == 'C' || x == 'S')
# define WIDTH(x) (x == '*' || (x >= '1' && x <= '9'))
# define FLAGS(x) (x == '#' || x == '0' || x == '-' || x == '+' || x == ' ')
# define LONGS(x) (x == 'h' || x == 'l' || x == 'j' || x == 'z')

typedef struct		s_listik
{
	int				fd;
	char			*str;
	struct s_listik	*next;
}					t_listik;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

union				u_n
{
	int				i;
	long int		li;
	long long int	lli;
	unsigned int	u;
	unsigned long	uli;
	unsigned long	ulli;
	short int		sh;
	unsigned short	ush;
	char			c;
	unsigned char	uc;
	char			*s;
	intmax_t		im;
	uintmax_t		uim;
	size_t			st;
	ssize_t			sst;
}					u_n;

typedef	struct		s_prf
{
	union u_n		u_n;
	int				pre;
	int				wid;
	int				holder;
	int				zero;
	int				plus;
	int				minus;
	int				hash;
	int				space;
	int				dioux;
	int				doux;
	int				octal;
	int				sign;
	int				wipre;
	int				decrem;
	int				dcrmnt;
	int				minsign;
	int				hex;
	int				null;
	int				counter;
	int				dot;
	int				unicount;
}					t_prf;

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putnbr(int n);
int					ft_atoi(const char *s);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_bzero(void *s, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_memdel(void **p);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memalloc(size_t size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(char *s1, const char *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnstr(const char *big, const char *lit, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putendl(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_swap(int *a, int *b);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isws(char c);
int					ft_isgraph(int c);
int					get_next_line(const int fd, char **line);
int					wr_big_uni_c(unsigned int v, int res, t_prf *pf, int un);
int					write_d_help_d(t_prf *pf, int *res, int *un, int len);
void				write_d_help_fin(t_prf *pf, int *res, int *un, char *s);
void				write_big_x_help(t_prf *pf, int *res, int *un, int len);
void				write_x_help(t_prf *pf, int *res, int *un, int len);
void				write_u_help(t_prf *pf, int *res, int *un, int len);
void				write_o_help(t_prf *pf, int *un, int len, int *res);
void				initialize_prf(t_prf *pf);
int					ft_dec_to_bin(unsigned int i);
int					unichr_write(unsigned int v, int res);
int					unistr_write(va_list ap, int res, t_prf *pf, int un);
void				prec_counter(const char **format, va_list ap, t_prf *pf);
int					precision_write(t_prf *pf, int res, int un, int len);
void				wid_handle(const char **format, va_list ap, t_prf *pf);
int					wid_write(t_prf *pf, int res, int un, int len);
int					write_p(va_list ap, t_prf *pf, int res);
int					write_x(va_list ap, t_prf *pf, int res, int un);
int					write_o(va_list ap, t_prf *pf, int res, int un);
int					write_u(va_list ap, t_prf *pf, int res, int un);
int					write_d_help(t_prf *pf, int len, int un, int *res);
int					write_d(va_list ap, t_prf *pf, int res, int un);
int					dioux(const char *format, va_list ap, t_prf *pf, int res);
int					write_ld(va_list ap, t_prf *pf, int res, int un);
int					write_lo(va_list ap, t_prf *pf, int res, int un);
int					write_lu(va_list ap, t_prf *pf, int res, int un);
int					write_big_x(va_list ap, t_prf *pf, int res, int un);
int					doux(const char *format, va_list ap, t_prf *pf, int res);
int					write_s(va_list ap, t_prf *pf, int res, int un);
int					write_c(int c, t_prf *pf, int res);
int					sscc(const char *format, va_list ap, t_prf *pf, int res);
int					write_lld(va_list ap, t_prf *pf, int res, int un);
int					write_llo(va_list ap, t_prf *pf, int res, int un);
int					write_llu(va_list ap, t_prf *pf, int res, int un);
int					write_llx(va_list ap, t_prf *pf, int res, int un);
int					write_ll_big_x(va_list ap, t_prf *pf, int res, int un);
int					write_lx(va_list ap, t_prf *pf, int res, int un);
int					write_l_big_x(va_list ap, t_prf *pf, int res, int un);
int					l_handl(const char **form, va_list ap, t_prf *pf, int res);
int					write_hhd(va_list ap, t_prf *pf, int res, int un);
int					write_hho(va_list ap, t_prf *pf, int res, int un);
int					write_hhu(va_list ap, t_prf *pf, int res, int un);
int					write_hhx(va_list ap, t_prf *pf, int res, int un);
int					write_hh_big_x(va_list ap, t_prf *pf, int res, int un);
int					write_hd(va_list ap, t_prf *pf, int res, int un);
int					write_ho(va_list ap, t_prf *pf, int res, int un);
int					write_hu(va_list ap, t_prf *pf, int res, int un);
int					write_hx(va_list ap, t_prf *pf, int res, int un);
int					h_handl(const char **form, va_list ap, t_prf *pf, int res);
int					write_zd(va_list ap, t_prf *pf, int res, int un);
int					write_zo(va_list ap, t_prf *pf, int res, int un);
int					write_zu(va_list ap, t_prf *pf, int res, int un);
int					write_zx(va_list ap, t_prf *pf, int res, int un);
int					write_z_big_x(va_list ap, t_prf *pf, int res, int un);
int					z_handl(const char **form, va_list ap, t_prf *pf, int res);
int					write_jd(va_list ap, t_prf *pf, int res, int un);
int					write_jo(va_list ap, t_prf *pf, int res, int un);
int					write_jx(va_list ap, t_prf *pf, int res, int un);
int					write_j_big_x(va_list ap, t_prf *pf, int res, int un);
int					j_handl(const char **form, va_list ap, t_prf *pf, int res);
int					sp_hand(const char **form, va_list ap, t_prf *pf, int res);
int					easy_wr(const char *form, va_list ap, t_prf *pf, int res);
int					flags(const char *format, t_prf *pf, int res);
int					parsing(const char **form, va_list ap, t_prf *pf, int res);
int					parsedata(const char *form, va_list ap, t_prf pf, int res);
int					write_ll_big_d(va_list ap, t_prf *pf, int res, int un);
int					write_hh_big_o(va_list ap, t_prf *pf, int res, int un);
int					write_h_big_d(va_list ap, t_prf *pf, int res, int un);
int					write_h_big_x(va_list ap, t_prf *pf, int res, int un);
char				*ft_itoa_b_s(intmax_t n, int base);
char				*ft_itoa_b_u(uintmax_t n, int base);
char				*ft_itoa_b_u_up(uintmax_t n, int base);
char				*ft_itoa_b_u_l(unsigned int nbr, int base);
char				*ft_itoa_base_u(unsigned int nbr, int base);
char				*ft_itoa_base(unsigned long long nbr, int base);
char				*ft_itoa_b_l(unsigned long long int nbr, int base);
int					ft_printf(const char *format, ...);

#endif
