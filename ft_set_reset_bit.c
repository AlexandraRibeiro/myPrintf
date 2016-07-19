/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_reset_bit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:06:18 by aribeiro          #+#    #+#             */
/*   Updated: 2016/02/22 14:06:25 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** avoid multi affectation
*/

void	ft_set_bit(int *flags, int bitval)
{
	if (!(*flags & bitval))
		*flags += bitval;
}

void	ft_reset_bit(int *flags, int bitval)
{
	if (*flags & bitval)
		*flags -= bitval;
}
