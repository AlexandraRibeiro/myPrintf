/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 17:41:23 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/11 13:03:59 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			ft_xint_hash_cas2(t_stock *stk, t_spec *sp)
{
	if (*sp->p != '\0' && *sp->p != '0')
	{
		sp->w = ft_strnew_exit(2);
		if (sp->flags & ICONVUPPER)
			sp->w[1] = 'X';
		else
			sp->w[1] = 'x';
		sp->w[0] = '0';
		printf_strjoin_exit(stk, sp->w);
		ft_reset_bit(&(sp->flags), ICONVXINT);
		if (sp->w != NULL)
			ft_memdel((void **)&(sp->w));
	}
}

static void		ft_pint_null(t_spec *sp)
{
	int i;

	i = 0;
	if (sp->flags & POINTERNULL && sp->precis > 1)
	{
		i = sp->precis - 1;
		while (i > 0)
		{
			*sp->p = '0';
			sp->p--;
			i--;
		}
		ft_reset_bit(&(sp->flags), PRECIS_POINT);
		sp->precis = 0;
	}
	else
	{
		ft_reset_bit(&(sp->flags), PRECIS_POINT);
		sp->precis = 0;
	}
}

void			ft_xint_hash_cas1(t_stock *stk, t_spec *sp)
{
	sp->p--;
	if (sp->flags & ICONVPOINTER)
		ft_pint_null(sp);
	if (sp->flags & ICONVUPPER)
		*sp->p = 'X';
	else
		*sp->p = 'x';
	sp->p--;
	*sp->p = '0';
	ft_reset_bit(&(sp->flags), ICONVXINT);
}

static void		ft_pint_conv(t_stock *stk, t_spec *sp)
{
	ft_set_bit(&(sp->flags), MODIF_L);
	ft_set_bit(&(sp->flags), ICONVPOINTER);
	ft_reset_bit(&(sp->flags), ATT_ZERO);
	ft_reset_bit(&(sp->flags), ATT_PLUS);
	ft_reset_bit(&(sp->flags), ATT_HASH);
}

void			printf_xint_conv(t_stock *stk, t_spec *sp)
{
	MY_UIMAX uiconv;

	uiconv = 0;
	if (*stk->fmt == 'p')
		ft_pint_conv(stk, sp);
	if (*stk->fmt == 'X')
		ft_set_bit(&(sp->flags), ICONVUPPER);
	uiconv = ft_uint_conv(uiconv, stk, sp);
	sp->p = ft_lltoa_base(uiconv, sp, 16);
	if (sp->flags & ATT_MINUS && sp->flags & ATT_ZERO)
		ft_reset_bit(&(sp->flags), ATT_ZERO);
	ft_reset_bit(&(sp->flags), ATT_PLUS);
	ft_reset_bit(&(sp->flags), ATT_SPACE);
	if ((sp->flags & ATT_HASH && *sp->p != '\0' && *sp->p != '0')
													|| sp->flags & ICONVPOINTER)
	{
		ft_set_bit(&(sp->flags), ICONVXINT);
		if (!(sp->flags & ATT_ZERO))
			ft_xint_hash_cas1(stk, sp);
	}
	int_uint_conv_bis(stk, sp);
	if (sp->w != NULL)
		ft_memdel((void **)&(sp->w));
	if (sp->z != NULL)
		ft_memdel((void **)&(sp->z));
}
