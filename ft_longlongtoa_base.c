/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_longlongtoa_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 15:32:26 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/08 18:02:58 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_lltoa_base(MY_UIMAX uiconv, t_spec *sp, unsigned int base)
{
	int				i;
	const char		*table;
	unsigned int	nb;

	i = 0;
	if (sp->flags & ICONVUPPER)
		table = "0123456789ABCDEF";
	else
		table = "0123456789abcdef";
	if (sp->buf[sizeof(sp->buf) - 1] == 1 && sp->precis == 0)
	{
		sp->buf[0] = '\0';
		return (&((sp->buf)[0]));
	}
	i = sizeof(sp->buf);
	(sp->buf)[--i] = '\0';
	while (uiconv >= base)
	{
		nb = uiconv % base;
		uiconv /= base;
		(sp->buf)[--i] = table[nb];
	}
	(sp->buf)[--i] = table[uiconv];
	return (&((sp->buf)[i]));
}
