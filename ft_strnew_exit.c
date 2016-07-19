/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:01:48 by aribeiro          #+#    #+#             */
/*   Updated: 2016/03/13 15:40:43 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strnew_exit(size_t size)
{
	char *ptr;

	ptr = (char *)malloc((sizeof(*ptr) * (size + 1)));
	if (ptr == NULL)
	{
		write(1, "strnew_exit : Error malloc\n", 27);
		exit(1);
	}
	ft_bzero(ptr, size + 1);
	return (ptr);
}
