/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 18:00:08 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/14 13:39:22 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** va_arg ne sait pas gerer les fmts < int
** donc cast pour char et short
** (int) if iconv = 0 , be careful don't print 0 with '.' for the precision
*/

static MY_IMAX	ft_int_conv(MY_IMAX iconv, t_stock *stk, t_spec *sp)
{
	if (sp->flags & MODIF_Q128)
		iconv = va_arg(stk->ap, MY_IMAX);
	else if (sp->flags & MODIF_J)
		iconv = va_arg(stk->ap, intmax_t);
	else if (sp->flags & MODIF_LL)
		iconv = va_arg(stk->ap, long long int);
	else if (sp->flags & MODIF_L)
		iconv = va_arg(stk->ap, long int);
	else if (sp->flags & MODIF_HH)
		iconv = (char)va_arg(stk->ap, int);
	else if (sp->flags & MODIF_Z)
		iconv = va_arg(stk->ap, ssize_t);
	else if (sp->flags & MODIF_H)
		iconv = (short int)va_arg(stk->ap, int);
	else
	{
		iconv = va_arg(stk->ap, int);
		if (iconv == 0)
		{
			sp->buf[sizeof(sp->buf) - 1] = 1;
			ft_reset_bit(&(sp->flags), ATT_HASH);
		}
	}
	return (iconv);
}

static void		int_ast_conv(t_stock *stk, t_spec *sp)
{
	if (sp->flags & ATT_MINUS && sp->flags & AST_WIDTH)
	{
		sp->precis = 1;
		ft_reset_bit(&(sp->flags), PRECIS_POINT);
	}
}

/*
** itoa stock char from va_arg in sp->p
** conv D real printf work only with %lD, myprintf work with %D or %lD
*/

void			printf_int_conv(t_stock *stk, t_spec *sp)
{
	MY_IMAX		iconv;
	MY_UIMAX	uiconv;

	iconv = 0;
	if (*stk->fmt == 'D')
		ft_set_bit(&(sp->flags), MODIF_L);
	iconv = ft_int_conv(iconv, stk, sp);
	if (iconv < 0)
	{
		ft_set_bit(&(sp->flags), ICONVNEG);
		uiconv = -iconv;
	}
	else
		uiconv = iconv;
	sp->p = ft_lltoa_base(uiconv, sp, 10);
	if (sp->flags & AST_PRECIS || sp->flags & AST_WIDTH)
		int_ast_conv(stk, sp);
	int_uint_conv_bis(stk, sp);
	if (sp->w != NULL)
		ft_memdel((void **)&(sp->w));
	if (sp->z != NULL)
		ft_memdel((void **)&(sp->z));
}
