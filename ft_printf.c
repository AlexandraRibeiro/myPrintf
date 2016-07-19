/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 14:05:00 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/13 14:26:29 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** s2 : doesn't use malloc > doesn't need to be freed
** ft_strnew_exit : use exit if malloc failed
** by default precis = 1
*/

static void		printf_ini_structs(t_stock *stk, t_spec *sp)
{
	stk->s1 = ft_strnew_exit(0);
	stk->s2[1] = '\0';
	stk->tmp = NULL;
	stk->nbc = 0;
	stk->n[0] = '\0';
	sp->w = NULL;
	sp->precis = 1;
	sp->width = 0;
	sp->flags = 0;
	sp->p = NULL;
}

/*
** void va_start(va_list ap, param);
** va_list ap : points to the first argument
** param : name of the last param = format
** type va_arg(va_list ap, type);
** void va_end(va_list ap);
*/

int				ft_printf(const char *format, ...)
{
	t_stock stk;
	t_spec	sp;

	if (format == NULL)
		return (-1);
	else if (ft_strlen(format) == 0)
		return (0);
	printf_ini_structs(&stk, &sp);
	stk.fmt = format;
	va_start(stk.ap, format);
	printf_search(&stk, &sp);
	va_end(stk.ap);
	return (stk.nbc);
}
