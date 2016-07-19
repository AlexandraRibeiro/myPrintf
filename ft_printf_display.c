/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 17:40:01 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/11 20:30:45 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	printf_display(t_stock *stk, t_spec *sp)
{
	if (sp->flags & CHARZERO)
	{
		if (stk->s1 != NULL)
			ft_putstr(stk->s1);
		write(1, &(stk->n[0]), 1);
		ft_memdel((void **)&(stk->s1));
		stk->s1 = ft_strnew_exit(0);
		ft_reset_bit(&(sp->flags), CHARZERO);
	}
	else if (stk->s1 != NULL)
		ft_putstr(stk->s1);
}

void	printf_display_char_minus(t_stock *stk, t_spec *sp)
{
	if (stk->s1 != NULL)
		ft_putstr(stk->s1);
	write(1, &(stk->n[0]), 1);
	ft_memdel((void **)&(stk->s1));
	stk->s1 = ft_strnew_exit(0);
	printf_strjoin_exit(stk, sp->w = printf_add_c(sp, ' '));
	ft_putstr(stk->s1);
	ft_memdel((void **)&(stk->s1));
	stk->s1 = ft_strnew_exit(0);
	ft_reset_bit(&(sp->flags), CHARZERO);
}
