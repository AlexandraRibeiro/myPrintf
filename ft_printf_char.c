/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 13:34:29 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/13 14:29:31 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		printf_char_bis(t_stock *stk, t_spec *sp)
{
	sp->width = sp->width - 1;
	if (sp->flags & ATT_MINUS && sp->flags & CHARZERO)
		printf_display_char_minus(stk, sp);
	else if (sp->flags & ATT_MINUS)
		printf_strjoin_ter(stk, stk->s2, (sp->w = printf_add_c(sp, ' ')));
	else if (sp->flags & ATT_ZERO)
	{
		sp->z = printf_add_zero(sp, '0', sp->width);
		printf_strjoin_ter(stk, sp->z, stk->s2);
	}
	else
		printf_strjoin_ter(stk, (sp->w = printf_add_c(sp, ' ')), stk->s2);
}

/*
** if arg = 0 ou NULL : nbc++ because printf displays '\0' and return 1
*/

void			printf_char_conv(t_stock *stk, t_spec *sp)
{
	if (!(sp->flags & INVALIDCONV))
		(stk->s2)[0] = (unsigned char)va_arg(stk->ap, unsigned int);
	if ((stk->s2)[0] == 0 && !(sp->flags & INVALIDCONV))
	{
		stk->nbc++;
		ft_set_bit(&(sp->flags), CHARZERO);
	}
	if (sp->width != 0)
		printf_char_bis(stk, sp);
	else
		printf_strjoin_exit(stk, stk->s2);
	if (sp->w != NULL)
		ft_memdel((void **)&(sp->w));
	if (sp->z != NULL)
		ft_memdel((void **)&(sp->z));
	if (sp->flags & CHARZERO)
		printf_display(stk, sp);
}
