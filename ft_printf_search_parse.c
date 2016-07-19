/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_search_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 15:36:14 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/14 13:57:24 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Bonus in 128, n
*/

static void		parse_conv(t_stock *stk, t_spec *sp)
{
	if (*stk->fmt == 's' && !(sp->flags & MODIF_L))
		printf_str_conv(stk, sp);
	else if ((*stk->fmt == 's' && (sp->flags & MODIF_L)) || *stk->fmt == 'S')
		printf_wstr(stk, sp);
	else if (*stk->fmt == 'c' && !(sp->flags & MODIF_L))
		printf_char_conv(stk, sp);
	else if ((*stk->fmt == 'c' && (sp->flags & MODIF_L)) || (*stk->fmt == 'C'))
		printf_wchar(stk, sp);
	else if (*stk->fmt == 'd' || *stk->fmt == 'i' || *stk->fmt == 'D')
		printf_int_conv(stk, sp);
	else if (*stk->fmt == 'u' || *stk->fmt == 'U')
		printf_uint_conv(stk, sp);
	else if (*stk->fmt == 'o' || *stk->fmt == 'O')
		printf_oint_conv(stk, sp);
	else if (*stk->fmt == 'x' || *stk->fmt == 'X' || *stk->fmt == 'p')
		printf_xint_conv(stk, sp);
	else if (*stk->fmt == 'n')
		printf_len_nbc(stk, sp);
	else
	{
		stk->s2[0] = *stk->fmt;
		ft_set_bit(&(sp->flags), INVALIDCONV);
		printf_char_conv(stk, sp);
	}
	ft_reset_bit(&(sp->flags), WAIT_CONV);
}

static void		parse_number(t_stock *stk, t_spec *sp)
{
	if (*stk->fmt == '0' && sp->width == 0 && !(sp->flags & PRECIS_POINT))
		ft_set_bit(&(sp->flags), ATT_ZERO);
	else if (sp->flags & PRECIS_POINT)
	{
		if (sp->flags & STOP_PRECIS)
			return ;
		sp->precis *= 10;
		sp->precis += *stk->fmt - '0';
	}
	else
	{
		if (sp->flags & AST_WIDTH)
			sp->width = 0;
		sp->width *= 10;
		sp->width += *stk->fmt - '0';
	}
}

/*
** Bonus : q et *
*/

void			printf_parse(t_stock *stk, t_spec *sp)
{
	if (*stk->fmt == '%')
	{
		printf_percent(stk, sp);
		return ;
	}
	else if (*stk->fmt == '.')
	{
		if (sp->flags & PRECIS_POINT && sp->precis != 0)
		{
			ft_set_bit(&(sp->flags), STOP_PRECIS);
			return ;
		}
		sp->precis = 0;
		ft_set_bit(&(sp->flags), PRECIS_POINT);
	}
	else if (*stk->fmt >= '0' && *stk->fmt <= '9')
		parse_number(stk, sp);
	else if (*stk->fmt == '#' || *stk->fmt == '-' || *stk->fmt == '+'
										|| *stk->fmt == ' ' || *stk->fmt == '*')
		printf_attribute(stk, sp);
	else if (*stk->fmt == 'h' || *stk->fmt == 'l' || *stk->fmt == 'j'
										|| *stk->fmt == 'z' || *stk->fmt == 'q')
		printf_modif_length(stk, sp);
	else
		parse_conv(stk, sp);
}

static void		printf_ini_spe(t_stock *stk, t_spec *sp)
{
	sp->w = NULL;
	sp->z = NULL;
	sp->precis = 1;
	sp->width = 0;
	sp->flags = WAIT_CONV;
	sp->p = NULL;
	sp->ws = NULL;
	sp->wc = 0;
	stk->tmp = NULL;
	stk->n[0] = '\0';
}

/*
** seeks all %
** ft_strjoin_exit : free(s1) & s1 = tmp // exit if malloc failed
** stk->nbc : count printable characters
*/

void			printf_search(t_stock *stk, t_spec *sp)
{
	while (*stk->fmt != '\0')
	{
		if (*stk->fmt == '%' && !(sp->flags & WAIT_CONV))
		{
			if (*(stk->fmt + 1) != '\0')
			{
				printf_ini_spe(stk, sp);
				stk->fmt++;
				printf_parse(stk, sp);
			}
		}
		else if (sp->flags & WAIT_CONV)
			printf_parse(stk, sp);
		else
		{
			stk->s2[0] = *stk->fmt;
			printf_strjoin_exit(stk, stk->s2);
		}
		stk->fmt++;
	}
	if (stk->nbc > 0)
		printf_display(stk, sp);
	free(stk->s1);
}
