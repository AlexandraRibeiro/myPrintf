/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:15:21 by aribeiro          #+#    #+#             */
/*   Updated: 2016/02/15 14:14:41 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void				*ft_memset(void *b, int c, size_t len)
{
	char			*bcpy;
	unsigned char	ccpy;

	bcpy = b;
	ccpy = c;
	while (len != 0)
	{
		*bcpy = ccpy;
		bcpy++;
		len--;
	}
	return (b);
}
