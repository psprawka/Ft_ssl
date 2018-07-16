/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 10:52:32 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/16 08:02:44 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	reset_md5(void)
{
	g_data.h0 = ntohl(0x01234567);
	g_data.h1 = ntohl(0x89abcdef);
	g_data.h2 = ntohl(0xfedcba98);
	g_data.h3 = ntohl(0x76543210);	
}

void	reset_sha256(void)
{
	g_data.h0 = 0x6a09e667;
	g_data.h1 = 0xbb67ae85;
	g_data.h2 = 0x3c6ef372;
	g_data.h3 = 0xa54ff53a;
	g_data.h4 = 0x510e527f;
	g_data.h5 = 0x9b05688c;
	g_data.h6 = 0x1f83d9ab;
	g_data.h7 = 0x5be0cd19;
}


void	reset_data(void)
{
	int		i;
	
	i = 0;
	while (g_hash_fcts[i].fct_reset)
	{
		if (g_data.fct == g_hash_fcts[i].fct_hash)
		{
			g_hash_fcts[i].fct_reset();
			break ;
		}
		i++;	
	}
}