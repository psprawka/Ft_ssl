/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 00:07:45 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/16 08:03:03 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		add_padding(void)
{
	int				padding_size;
	unsigned char	*padding;
	unsigned char	*res;

	if ((padding_size = 56 - (g_data.len % 64)) < 0)
		padding_size = 64 - ABS(56 - (g_data.len % 64));
	if (!(padding = ft_memalloc(padding_size)))
		return (error(0, "Ft_memalloc [add_padding]", true));
	if (!(res = ft_memalloc((g_data.len + 64))))
		return (error(0, "Ft_memalloc [add_padding]", true));
	((uint8_t *)padding)[0] |= 0x80;
	ft_memcpy(res, g_data.str, g_data.len);
	ft_memcpy(res + g_data.len, padding, padding_size);
	long long temp = g_data.len * 8;
	ft_memcpy(res + g_data.len + padding_size, (uint64_t *)(&(temp)), 8);
	g_data.fullstr = res;
	g_data.len += padding_size + 8;
	return (EXIT_SUCCESS);
}


int		add_padding_sha256(void)
{
	int				padding_size;
	unsigned char	*padding;
	int				i;

	if ((padding_size = 56 - (g_data.len % 64)) < 0)
		padding_size = 64 - ABS(56 - (g_data.len % 64));
	
	if (!(padding = ft_memalloc(padding_size)))
		return (error(0, "Ft_memalloc [add_padding]", true));
	if (!(g_data.wtf = ft_memalloc((g_data.len + 64))))
		return (error(0, "Ft_memalloc [add_padding]", true));
	ft_strcpy((char *)g_data.wtf, g_data.str);
	((char*)g_data.wtf)[ft_strlen(g_data.str)] = 0x80;
	i = 0;
	while (i < (g_data.len + padding_size + 8) / 4)
	{
		g_data.wtf[i] = swap_uint32(g_data.wtf[i]);
		i++;
	}
	uint32_t temp = g_data.len * 8;
	g_data.len += padding_size + 8;
	g_data.wtf[(g_data.len - 8) / 4 + 1] = temp;
	return (EXIT_SUCCESS);
}