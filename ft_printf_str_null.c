/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_null.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 18:13:24 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/14 13:30:59 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		else_null(t_stock *stk, t_spec *sp)
{
	if (sp->width <= 6)
		printf_strjoin_exit(stk, "(null)");
	else if (sp->width > 6)
	{
		sp->width -= 6;
		if (sp->flags & ATT_MINUS && sp->width > 0)
			printf_strjoin_ter(stk, "(null)", sp->w = printf_add_c(sp, ' '));
		else if (sp->flags & ATT_ZERO && sp->width > 0)
			printf_strjoin_ter(stk, sp->w = printf_add_c(sp, '0'), "(null)");
		else
			printf_strjoin_ter(stk, sp->w = printf_add_c(sp, ' '), "(null)");
	}
}

static void		precis_inf_6(t_stock *stk, t_spec *sp)
{
	if (sp->precis == 1)
		printf_strjoin_exit(stk, "(");
	else if (sp->precis == 2)
		printf_strjoin_exit(stk, "(n");
	else if (sp->precis == 3)
		printf_strjoin_exit(stk, "(nu");
	else if (sp->precis == 4)
		printf_strjoin_exit(stk, "(nul");
	else if (sp->precis == 5)
		printf_strjoin_exit(stk, "(null");
}

static void		precis_null(t_stock *stk, t_spec *sp)
{
	if (sp->width <= 1)
		printf_strjoin_exit(stk, "");
	else if (sp->width > 1)
	{
		sp->width -= 1;
		if (sp->flags & ATT_MINUS && sp->width > 0)
			printf_strjoin_ter(stk, "", sp->w = printf_add_c(sp, ' '));
		else if (sp->flags & ATT_ZERO && sp->width > 0)
			printf_strjoin_ter(stk, sp->w = printf_add_c(sp, '0'), "");
		else
			printf_strjoin_ter(stk, sp->w = printf_add_c(sp, ' '), "");
	}
}

void			printf_str_null_conv(t_stock *stk, t_spec *sp)
{
	if (sp->flags & PRECIS_POINT && sp->precis < 6 && sp->precis > sp->width)
		precis_inf_6(stk, sp);
	else if (sp->flags & PRECIS_POINT && sp->precis == 0)
		precis_null(stk, sp);
	else
		else_null(stk, sp);
}
