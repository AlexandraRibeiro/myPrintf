/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 14:43:29 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/14 15:56:26 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

MY_UIMAX	ft_uint_conv(MY_UIMAX uiconv, t_stock *stk, t_spec *sp)
{
	if (sp->flags & MODIF_Q128)
		uiconv = va_arg(stk->ap, MY_UIMAX);
	else if (sp->flags & MODIF_J)
		uiconv = va_arg(stk->ap, uintmax_t);
	else if (sp->flags & MODIF_LL)
		uiconv = va_arg(stk->ap, MY_ULLONG);
	else if (sp->flags & MODIF_HH)
		uiconv = (unsigned char)va_arg(stk->ap, MY_UINT);
	else if (sp->flags & MODIF_L)
	{
		uiconv = va_arg(stk->ap, MY_ULONG);
		if (uiconv == 0)
			ft_set_bit(&(sp->flags), POINTERNULL);
	}
	else if (sp->flags & MODIF_H)
		uiconv = (unsigned short int)va_arg(stk->ap, MY_UINT);
	else if (sp->flags & MODIF_Z)
		uiconv = va_arg(stk->ap, size_t);
	else
	{
		uiconv = va_arg(stk->ap, MY_UINT);
		if (uiconv == 0)
			sp->buf[sizeof(sp->buf) - 1] = 1;
	}
	return (uiconv);
}

void		printf_uint_conv(t_stock *stk, t_spec *sp)
{
	MY_UIMAX uiconv;

	uiconv = 0;
	if (*stk->fmt == 'U')
		ft_set_bit(&(sp->flags), MODIF_L);
	uiconv = ft_uint_conv(uiconv, stk, sp);
	sp->p = ft_lltoa_base(uiconv, sp, 10);
	if (sp->flags & ATT_SPACE)
		ft_reset_bit(&(sp->flags), ATT_SPACE);
	if (sp->flags & ATT_PLUS)
		ft_reset_bit(&(sp->flags), ATT_PLUS);
	int_uint_conv_bis(stk, sp);
	if (sp->w != NULL)
		ft_memdel((void **)&(sp->w));
	if (sp->z != NULL)
		ft_memdel((void **)&(sp->z));
}
