/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_oct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 17:30:47 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/14 14:39:01 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	printf_oint_conv(t_stock *stk, t_spec *sp)
{
	MY_UIMAX	uiconv;

	uiconv = 0;
	if (*stk->fmt == 'O')
		ft_set_bit(&(sp->flags), MODIF_L);
	uiconv = ft_uint_conv(uiconv, stk, sp);
	sp->p = ft_lltoa_base(uiconv, sp, 8);
	if ((sp->flags & ATT_HASH) && *sp->p != '0')
	{
		sp->p--;
		*sp->p = '0';
	}
	if (sp->flags & ATT_PLUS)
		ft_reset_bit(&(sp->flags), ATT_PLUS);
	if (sp->flags & ATT_SPACE)
		ft_reset_bit(&(sp->flags), ATT_SPACE);
	int_uint_conv_bis(stk, sp);
	if (sp->w != NULL)
		ft_memdel((void **)&(sp->w));
	if (sp->z != NULL)
		ft_memdel((void **)&(sp->z));
}
