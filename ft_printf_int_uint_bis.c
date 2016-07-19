/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int_uint_bis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 16:51:43 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/14 13:56:41 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		ft_part4(t_stock *stk, t_spec *sp, int l)
{
	if (!(sp->flags & ATT_ZERO)
							|| (sp->precis == 1 && sp->flags & PRECIS_POINT))
		ft_part1_4_bis(stk, sp, l, 4);
	else if (sp->flags & ATT_ZERO)
	{
		if (sp->flags & ATT_PLUS || sp->flags & ICONVNEG
													|| sp->flags & ATT_SPACE)
		{
			printf_strjoin_exit(stk, stk->s2);
			sp->width -= 1;
		}
		if (sp->flags & ICONVXINT)
		{
			ft_xint_hash_cas2(stk, sp);
			l += 2;
		}
		sp->z = printf_add_zero(sp, '0', (sp->width - l));
		printf_strjoin_ter(stk, sp->z, sp->p);
	}
	else
		printf_strjoin_exit(stk, sp->p);
}

static void		ft_part2_3(t_stock *stk, t_spec *sp, int l, int cas)
{
	if (cas == 2)
	{
		if (stk->s2[0] != ' ')
			printf_strjoin_exit(stk, stk->s2);
		else if (sp->flags & ATT_SPACE)
			printf_strjoin_exit(stk, stk->s2);
		else if (sp->flags & ICONVXINT)
		{
			ft_xint_hash_cas2(stk, sp);
			l += 2;
		}
		sp->z = printf_add_zero(sp, '0', (sp->precis - l));
		printf_strjoin_ter(stk, sp->z, sp->p);
	}
	if (cas == 3)
	{
		if ((stk->s2)[0] != ' ')
		{
			printf_strjoin_exit(stk, stk->s2);
			sp->width -= 1;
		}
		sp->width -= l;
		printf_strjoin_ter(stk, sp->p, (sp->w = printf_add_c(sp, ' ')));
	}
}

void			ft_part1_4_bis(t_stock *stk, t_spec *sp, int l, int cas)
{
	if (cas == 1)
	{
		sp->width = sp->width - sp->precis - 1;
		sp->w = printf_add_c(sp, ' ');
		if (sp->flags & ATT_PLUS || sp->flags & ICONVNEG)
			printf_strjoin_ter(stk, sp->w, stk->s2);
		else
			printf_strjoin_ter(stk, stk->s2, sp->w);
		if (sp->precis == 1 && *sp->p == 0)
			return ;
		sp->z = printf_add_zero(sp, '0', (sp->precis - l));
		printf_strjoin_ter(stk, sp->z, sp->p);
	}
	if (cas == 4)
	{
		sp->width = sp->width - l - 1;
		sp->w = printf_add_c(sp, ' ');
		printf_strjoin_ter(stk, sp->w, stk->s2);
		printf_strjoin_exit(stk, sp->p);
	}
}

static void		ft_part1(t_stock *stk, t_spec *sp, int l)
{
	if (sp->flags & ICONVXINT)
	{
		ft_xint_hash_cas2(stk, sp);
		l += 2;
	}
	if (sp->flags & ATT_MINUS)
	{
		if (stk->s2[0] != ' ')
		{
			printf_strjoin_exit(stk, stk->s2);
			sp->width -= 1;
		}
		sp->z = printf_add_zero(sp, '0', (sp->precis - l));
		printf_strjoin_ter(stk, sp->z, sp->p);
		sp->width = sp->width - sp->precis;
		printf_strjoin_exit(stk, (sp->w = printf_add_c(sp, ' ')));
	}
	else
		ft_part1_4_bis(stk, sp, l, 1);
}

void			int_uint_conv_bis(t_stock *stk, t_spec *sp)
{
	int l;

	l = ft_strlen(sp->p);
	(stk->s2)[0] = ' ';
	if (sp->flags & ATT_MINUS && sp->flags & ATT_ZERO)
		ft_reset_bit(&(sp->flags), ATT_ZERO);
	if (sp->flags & ICONVNEG)
		(stk->s2)[0] = '-';
	else if (sp->flags & ATT_PLUS)
		(stk->s2)[0] = '+';
	if (sp->flags & PRECIS_POINT && sp->width > sp->precis && sp->precis >= l)
		ft_part1(stk, sp, l);
	else if (sp->flags & PRECIS_POINT && sp->precis > l)
		ft_part2_3(stk, sp, l, 2);
	else if (sp->width > l && sp->flags & ATT_MINUS)
		ft_part2_3(stk, sp, l, 3);
	else if (sp->width > l)
		ft_part4(stk, sp, l);
	else
	{
		if (stk->s2[0] != ' ' || sp->flags & ATT_SPACE)
			printf_strjoin_ter(stk, stk->s2, sp->p);
		else
			printf_strjoin_exit(stk, sp->p);
	}
}
