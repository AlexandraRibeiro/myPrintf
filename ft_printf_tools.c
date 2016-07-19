/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:05:20 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/13 15:13:08 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	printf_strjoin_ter(t_stock *stk, char *s3, char *s4)
{
	char	*tmp;
	size_t	len;

	tmp = NULL;
	if (stk->s1 != NULL && s3 != NULL && s4 != NULL)
	{
		len = stk->nbc + ft_strlen(s3) + ft_strlen(s4);
		tmp = ft_strnew_exit(len);
		tmp = ft_strcpy(tmp, stk->s1);
		tmp = ft_strcat(tmp, s3);
		tmp = ft_strcat(tmp, s4);
		if (stk->s1 != NULL)
			free(stk->s1);
		stk->s1 = tmp;
		stk->nbc = len;
	}
}

void	printf_strjoin_exit(t_stock *stk, char *s3)
{
	char	*tmp;
	size_t	len;

	tmp = NULL;
	if (stk->s1 != NULL && s3 != NULL)
	{
		len = stk->nbc + ft_strlen(s3);
		tmp = ft_strnew_exit(len);
		tmp = ft_strcpy(tmp, stk->s1);
		tmp = ft_strcat(tmp, s3);
		if (stk->s1 != NULL)
			free(stk->s1);
		stk->s1 = tmp;
		stk->nbc = len;
	}
}

void	printf_strjoin_c(char **s1, char c)
{
	char	*tmp;
	int		len;
	int		itemp;

	tmp = NULL;
	len = 1;
	if (*s1 != NULL)
		len = (int)ft_strlen(*s1) + 1;
	tmp = ft_strnew_exit(len);
	if (*s1 != NULL)
	{
		itemp = -1;
		while (++itemp < len - 1)
			tmp[itemp] = (*s1)[itemp];
		free(*s1);
	}
	tmp[len - 1] = c;
	*s1 = tmp;
}

char	*printf_add_c(t_spec *sp, char c)
{
	int len;
	int i;

	len = sp->width;
	i = 0;
	sp->w = ft_strnew_exit((size_t)len);
	while (len != 0)
	{
		sp->w[i] = c;
		i++;
		len--;
	}
	return (sp->w);
}

char	*printf_add_zero(t_spec *sp, char c, int len)
{
	int i;

	i = 0;
	sp->z = ft_strnew_exit((size_t)len);
	while (len != 0)
	{
		sp->z[i] = c;
		i++;
		len--;
	}
	return (sp->z);
}
