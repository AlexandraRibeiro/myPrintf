/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_wide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:43:17 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/13 15:57:40 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		wstr_conv2(char **tmp, int *c, int *precis)
{
	if (*c <= 0x7FF)
	{
		printf_strjoin_c(tmp, (*c >> 6) + 0xC0);
		printf_strjoin_c(tmp, (*c & 0x3F) + 0x80);
		*precis -= 2;
	}
	else if (*c <= 0xFFFF)
	{
		printf_strjoin_c(tmp, (*c >> 12) + 0xE0);
		printf_strjoin_c(tmp, ((*c >> 6) & 0x3F) + 0x80);
		printf_strjoin_c(tmp, (*c & 0x3F) + 0x80);
		*precis -= 3;
	}
	else if (*c <= 0x10FFFF)
	{
		printf_strjoin_c(tmp, (*c >> 18) + 0xF0);
		printf_strjoin_c(tmp, ((*c >> 12) & 0x3F) + 0x80);
		printf_strjoin_c(tmp, ((*c >> 6) & 0x3F) + 0x80);
		printf_strjoin_c(tmp, (*c & 0x3F) + 0x80);
		*precis -= 4;
	}
}

/*
** cast int because wchart_t < int on Windows, not necessary on Linux
** verif precision : to avoid incompleted UTF8's unit
*/

char			*wstr_conv(wchar_t *wcs, int cas, int precis)
{
	int		value_ini;
	char	*tmp;
	int		c;

	value_ini = cas;
	tmp = NULL;
	while (cas != 0 && *wcs != 0)
	{
		c = (int)*wcs;
		if (c <= 0x7F && (precis < 0 || precis > 0))
		{
			printf_strjoin_c(&tmp, c);
			precis--;
		}
		else if ((c <= 0x7FF && (precis < 0 || precis > 1))
							|| (c <= 0xFFFF && (precis < 0 || precis > 2))
							|| (c <= 0x10FFFF && (precis < 0 || precis > 3)))
			wstr_conv2(&tmp, &c, &precis);
		else
			return (tmp);
		cas--;
		if (value_ini != 1)
			wcs++;
	}
	return (tmp);
}

void			printf_wstr(t_stock *stk, t_spec *sp)
{
	sp->ws = NULL;
	sp->ws = va_arg(stk->ap, wchar_t *);
	if (sp->ws == NULL)
	{
		ft_set_bit(&(sp->flags), STRNULL);
		printf_str_conv(stk, sp);
		return ;
	}
	else if (sp->ws != NULL)
	{
		if (!(sp->flags & PRECIS_POINT))
			sp->p = wstr_conv(sp->ws, -1, -1);
		else
			sp->p = wstr_conv(sp->ws, -1, sp->precis);
	}
	if (sp->p != NULL)
	{
		printf_str_conv(stk, sp);
		free(sp->p);
	}
	else if (sp->p == NULL)
	{
		sp->p = "";
		printf_str_conv(stk, sp);
	}
}

static void		wchar_free(t_stock *stk, t_spec *sp)
{
	if (sp->p != NULL)
		free(sp->p);
	if (sp->w != NULL)
		free(sp->w);
	if (sp->z != NULL)
		free(sp->z);
	if (sp->flags & CHARZERO)
		printf_display(stk, sp);
}

/*
** cast because on Windows wchar_t < int (not necessary on Linux)
*/

void			printf_wchar(t_stock *stk, t_spec *sp)
{
	sp->wc = (wchar_t)va_arg(stk->ap, unsigned int);
	if (sp->wc == 0)
	{
		stk->nbc++;
		ft_set_bit(&(sp->flags), CHARZERO);
	}
	sp->p = NULL;
	sp->p = wstr_conv(&(sp->wc), 1, -1);
	if (sp->width != 0)
	{
		sp->width = sp->width - (int)ft_strlen(sp->p);
		if (sp->flags & ATT_MINUS)
			printf_strjoin_ter(stk, sp->p, (sp->w = printf_add_c(sp, ' ')));
		else if (sp->flags & ATT_ZERO)
		{
			sp->z = printf_add_zero(sp, '0', sp->width);
			printf_strjoin_ter(stk, sp->z, sp->p);
		}
		else
			printf_strjoin_ter(stk, (sp->w = printf_add_c(sp, ' ')), sp->p);
	}
	else
		printf_strjoin_exit(stk, sp->p);
	wchar_free(stk, sp);
}
