/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 12:49:18 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/13 20:39:14 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdarg.h>
# include <wchar.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

/*
** BONUS 128 : 40 numbers > long long int : 20 numbers
*/
# ifndef __SIZEOF_INT128__
#  define MY_IMAX 		long long
#  define MY_UIMAX 		unsigned long long
# else
#  define MY_IMAX 		__int128
#  define MY_UIMAX 		unsigned __int128
# endif

# define MY_UINT		unsigned int
# define MY_ULONG		unsigned long int
# define MY_ULLONG		unsigned long long int

/*
** int flags > 32 bits
** each bit in sp->flags is changed by a define
** PRECIS_POINT = 0100 0000 0000 0000 0000 0000 0000 0000
** WAIT_CONV	= 1000 0000 0000 0000 0000 0000 0000 0000
** BONUS MODIF Q128 = int 128
*/
# define AST_WIDTH		0x00000020
# define AST_PRECIS		0x00000040
# define INVALIDCONV	0x00000080
# define STOP_PRECIS	0x00000100
# define PMALLOC		0x00000200
# define TMPMALLOC		0x00000400
# define STRNULL		0x00000800
# define CHARZERO		0x00001000
# define POINTERNULL	0x00002000
# define ICONVPOINTER	0x00004000
# define ICONVXINT		0x00008000
# define ICONVUPPER		0x00010000
# define ICONVNEG		0x00020000
# define MODIF_Q128		0x00040000
# define MODIF_Z		0x00080000
# define MODIF_J		0x00100000
# define MODIF_LL		0x00200000
# define MODIF_L		0x00400000
# define MODIF_HH		0x00800000
# define MODIF_H		0x01000000
# define ATT_SPACE		0x02000000
# define ATT_MINUS		0x04000000
# define ATT_PLUS		0x08000000
# define ATT_HASH		0x10000000
# define ATT_ZERO		0x20000000
# define PRECIS_POINT	0x40000000
# define WAIT_CONV		0x80000000

typedef struct	s_stock
{
	const char	*fmt;
	va_list		ap;
	char		*s1;
	char		s2[2];
	char		*tmp;
	int			nbc;
	char		n[2];
}				t_stock;

/*
** modif_len =  : hh h l ll j z  / Bonus : q
** precision : after '.'
** point : 0 default, 1 if '.' was found
** width : never starts with 0
** attribut : # 0 - + ' '
** conv : s S p d D i o O u U x X c C
*/
typedef struct	s_spec
{
	char		*w;
	char		*z;
	int			precis;
	int			width;
	int			flags;
	char		*p;
	wchar_t		*ws;
	wchar_t		wc;
	char		buf[128];
}				t_spec;

int				ft_printf(const char *format, ...);

void			printf_search(t_stock *stk, t_spec *sp);
void			printf_parse(t_stock *stk, t_spec *sp);

/*
** DEFINE %% / # 0 - + ' '/ hh h l ll j z (BONUS) q * / precis ---------
*/
void			printf_percent(t_stock *stk, t_spec *sp);
void			printf_attribute(t_stock *stk, t_spec *sp);
void			printf_modif_length(t_stock *stk, t_spec *sp);
void			printf_asterisk(t_stock *stk, t_spec *sp);

/*
** -- CONVERSIONS d i D u U o O x X p s c ---(BONUS) n --------------
*/
void			printf_int_conv(t_stock *stk, t_spec *sp);
void			printf_uint_conv(t_stock *stk, t_spec *sp);
MY_UIMAX		ft_uint_conv(MY_UIMAX uiconv, t_stock *stk, t_spec *sp);
void			printf_oint_conv(t_stock *stk, t_spec *sp);
void			printf_xint_conv(t_stock *stk, t_spec *sp);
void			ft_xint_hash_cas1(t_stock *stk, t_spec *sp);
void			ft_xint_hash_cas2(t_stock *stk, t_spec *sp);
void			int_uint_conv_bis(t_stock *stk, t_spec *sp);
void			ft_part1_4_bis(t_stock *stk, t_spec *sp, int l, int cas);
char			*ft_lltoa_base(MY_UIMAX uiconv, t_spec *sp, unsigned int base);
void			printf_str_conv(t_stock *stk, t_spec *sp);
void			printf_str_null_conv(t_stock *stk, t_spec *sp);
void			printf_char_conv(t_stock *stk, t_spec *sp);
void			printf_len_nbc(t_stock *stk, t_spec *sp);

/*
** -- WIDE CHAR ls / lc / C / S -------------------------------------
*/
char			*wstr_conv(wchar_t *wcs, int cas, int precis);
void			printf_wstr(t_stock *stk, t_spec *sp);
void			printf_wchar(t_stock *stk, t_spec *sp);

/*
** -- TOOLS ---------------------------------------------------------
*/
void			printf_strjoin_exit(t_stock *stk, char *s3);
void			printf_strjoin_ter(t_stock *stk, char *s3, char *s4);
void			printf_strjoin_c(char **s1, char c);
char			*printf_add_c(t_spec *sp, char c);
char			*printf_add_zero(t_spec *sp, char c, int len);

/*
** -- DISPLAY / ERRORS ----------------------------------------------
*/
void			printf_errors_exit(int cas);
void			printf_display(t_stock *stk, t_spec *sp);
void			printf_display_char_minus(t_stock *stk, t_spec *sp);

/*
** -- SET / RESET BIT -----------------------------------------------
*/
void			ft_set_bit(int *flags, int bitval);
void			ft_reset_bit(int *flags, int bitval);

/*
** -- LIBFT with exit for malloc's error ----------------------------
*/
void			ft_bzero(void *s, size_t n);
void			ft_memdel(void **ap);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar(char c);
void			ft_putnbr(int n);
void			ft_putstr(char const *s);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
size_t			ft_strlen(const char *s);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strnew_exit(size_t size);

#endif
