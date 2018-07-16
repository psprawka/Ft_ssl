/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:36:54 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/10 21:39:54 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_convert_hex(unsigned long int nb, int type)
{
	char	*print;
	int		i;

	i = 0;
	print = ft_memalloc(21);
	if (nb == 0)
		print[i] = '0';
	if (type == 0)
		while (nb != 0)
		{
			print[i++] = "0123456789abcdef"[nb % 16];
			nb /= 16;
		}
	else
		while (nb != 0)
		{
			print[i++] = "0123456789ABCDEF"[nb % 16];
			nb /= 16;
		}
	return (ft_strrev(print));
}
