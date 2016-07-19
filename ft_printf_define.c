/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_define.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:05:26 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/14 13:58:05 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** first search case : %(width)%
*/

void		printf_percent(t_stock *stk, t_spec *sp)
{
	(stk->s2)[0] = '%';
	if (sp->width != 0)
	{
		sp->width = sp->width - 1;
		if (sp->flags & ATT_MINUS)
			printf_strjoin_ter(stk, stk->s2, (sp->w = printf_add_c(sp, ' ')));
		else if (sp->flags & ATT_ZERO)
		{
			sp->z = printf_add_zero(sp, '0', sp->width);
			printf_strjoin_ter(stk, sp->z, stk->s2);
		}
		else
			printf_strjoin_ter(stk, (sp->w = printf_add_c(sp, ' ')), stk->s2);
	}
	else
		printf_strjoin_exit(stk, stk->s2);
	if (sp->z != NULL)
		ft_memdel((void **)&(sp->z));
	if (sp->w != NULL)
		ft_memdel((void **)&(sp->w));
	ft_reset_bit(&(sp->flags), WAIT_CONV);
}

void		printf_attribute(t_stock *stk, t_spec *sp)
{
	if (*stk->fmt == '#')
		ft_set_bit(&(sp->flags), ATT_HASH);
	else if (*stk->fmt == '+')
		ft_set_bit(&(sp->flags), ATT_PLUS);
	else if (*stk->fmt == '-')
		ft_set_bit(&(sp->flags), ATT_MINUS);
	else if (*stk->fmt == ' ')
		ft_set_bit(&(sp->flags), ATT_SPACE);
	else if (*stk->fmt == '*')
		printf_asterisk(stk, sp);
}

void		printf_asterisk(t_stock *stk, t_spec *sp)
{
	int r;

	r = va_arg(stk->ap, int);
	if (!(sp->flags & PRECIS_POINT))
	{
		sp->width = r;
		if (r < 0)
		{
			ft_set_bit(&(sp->flags), ATT_MINUS);
			sp->width = -r;
		}
		ft_set_bit(&(sp->flags), AST_WIDTH);
	}
	else
	{
		sp->precis = r;
		if (r < 0)
		{
			sp->precis = 1;
			ft_reset_bit(&(sp->flags), PRECIS_POINT);
		}
		ft_set_bit(&(sp->flags), AST_PRECIS);
	}
}

void		printf_modif_length(t_stock *stk, t_spec *sp)
{
	if (*stk->fmt == 'h')
	{
		if (sp->flags & MODIF_H)
			ft_set_bit(&(sp->flags), MODIF_HH);
		else
			ft_set_bit(&(sp->flags), MODIF_H);
	}
	else if (*stk->fmt == 'l')
	{
		if (sp->flags & MODIF_L)
			ft_set_bit(&(sp->flags), MODIF_LL);
		else
			ft_set_bit(&(sp->flags), MODIF_L);
	}
	else if (*stk->fmt == 'j')
		ft_set_bit(&(sp->flags), MODIF_J);
	else if (*stk->fmt == 'z')
		ft_set_bit(&(sp->flags), MODIF_Z);
	else if (*stk->fmt == 'q')
		ft_set_bit(&(sp->flags), MODIF_Q128);
}
