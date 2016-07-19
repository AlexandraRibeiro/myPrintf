/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:43:57 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/13 18:32:10 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		conv_ter_else(t_stock *stk, t_spec *sp, size_t len, char *tmp2)
{
	len = ft_strlen(tmp2);
	if (sp->width >= len)
		sp->width -= len;
	else
		sp->width = 0;
	if (sp->flags & ATT_MINUS)
		printf_strjoin_ter(stk, tmp2, (sp->w = printf_add_c(sp, ' ')));
	else if (sp->flags & ATT_ZERO)
	{
		sp->w = printf_add_zero(sp, '0', sp->width);
		printf_strjoin_ter(stk, sp->w, tmp2);
	}
	else
		printf_strjoin_ter(stk, (sp->w = printf_add_c(sp, ' ')), tmp2);
}

static void		str_conv_ter(t_stock *stk, t_spec *sp, size_t len, int i)
{
	char *tmp2;

	tmp2 = ft_strnew_exit(sp->precis);
	len = ft_strlen(stk->tmp);
	while (i < sp->precis && *(stk->tmp) != '\0')
	{
		tmp2[i] = *stk->tmp;
		i++;
		stk->tmp++;
	}
	if (sp->width == 0 || (sp->precis < (int)len && sp->width < sp->precis))
		printf_strjoin_exit(stk, tmp2);
	else
		conv_ter_else(stk, sp, len, tmp2);
	if (tmp2 != NULL)
		ft_memdel((void **)&tmp2);
}

static void		str_conv_bis(t_stock *stk, t_spec *sp, size_t len)
{
	len = ft_strlen(stk->tmp);
	if (sp->width > (int)len)
	{
		sp->width = sp->width - len;
		if (sp->flags & ATT_MINUS)
			printf_strjoin_ter(stk, stk->tmp, (sp->w = printf_add_c(sp, ' ')));
		else if (sp->flags & ATT_ZERO)
		{
			sp->w = printf_add_zero(sp, '0', sp->width);
			printf_strjoin_ter(stk, sp->w, stk->tmp);
		}
		else
			printf_strjoin_ter(stk, (sp->w = printf_add_c(sp, ' ')), stk->tmp);
	}
	else
		printf_strjoin_exit(stk, stk->tmp);
}

void			printf_str_conv(t_stock *stk, t_spec *sp)
{
	size_t len;

	len = 0;
	if (sp->p == NULL && !(sp->flags & STRNULL))
		stk->tmp = va_arg(stk->ap, char *);
	else
		stk->tmp = sp->p;
	if (stk->tmp == NULL)
	{
		printf_str_null_conv(stk, sp);
		return ;
	}
	if (sp->precis == 0 && sp->width != 0)
		printf_strjoin_exit(stk, (sp->w = printf_add_c(sp, ' ')));
	else if (!(sp->flags & PRECIS_POINT) && sp->width != 0)
		str_conv_bis(stk, sp, len);
	else if (sp->flags & PRECIS_POINT)
		str_conv_ter(stk, sp, len, 0);
	else
		printf_strjoin_exit(stk, stk->tmp);
	if (sp->w != NULL)
		ft_memdel((void **)&(sp->w));
}
