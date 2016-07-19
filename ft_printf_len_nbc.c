/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_len_nbc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 17:07:09 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/13 17:20:26 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	printf_len_nbc(t_stock *stk, t_spec *sp)
{
	void *ptr;

	ptr = va_arg(stk->ap, void *);
	if (sp->flags & MODIF_Q128)
		*(MY_IMAX *)ptr = stk->nbc;
	else if (sp->flags & MODIF_J)
		*(intmax_t *)ptr = stk->nbc;
	else if (sp->flags & MODIF_LL)
		*(long long int *)ptr = stk->nbc;
	else if (sp->flags & MODIF_L)
		*(long int *)ptr = stk->nbc;
	else if (sp->flags & MODIF_HH)
		*(char *)ptr = stk->nbc;
	else if (sp->flags & MODIF_Z)
		*(ssize_t *)ptr = stk->nbc;
	else if (sp->flags & MODIF_H)
		*(short int *)ptr = stk->nbc;
	else
		*(int *)ptr = stk->nbc;
}
