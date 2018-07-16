/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 22:59:28 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/12 02:35:41 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"


const uint32_t g_keys_md5[] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const uint32_t g_shift[] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4,
	11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6,
	10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

//#define LEFTROTATE(x) ((g_data.F << x) | (g_data.F >> (32 - x)))

uint32_t	leftrotate(uint32_t shift)
{
	return ((g_data.F << shift) | (g_data.F >> (32 - shift)));
}


void		append_chunks_md5(void)
{

	g_data.h0 = ntohl(g_data.h0);
	g_data.h1 = ntohl(g_data.h1);
	g_data.h2 = ntohl(g_data.h2);
	g_data.h3 = ntohl(g_data.h3);
	
	if (!(g_data.fullstr = ft_memalloc(4 * sizeof(uint32_t))))
		return ;
	
	ft_strcpy((char *)g_data.fullstr, ft_convert_hex(g_data.h0, 0));
	ft_strcat((char *)g_data.fullstr, ft_convert_hex(g_data.h1, 0));
	ft_strcat((char *)g_data.fullstr, ft_convert_hex(g_data.h2, 0));
	ft_strcat((char *)g_data.fullstr, ft_convert_hex(g_data.h3, 0));
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          

void	md5_rounds(void)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			g_data.F = (g_data.B & g_data.C) | ((~g_data.B) & g_data.D);
            g_data.G = i;
			
		}
		else if (i < 32)
		{
			g_data.F = (g_data.D & g_data.B) | ((~g_data.D) & g_data.C);
            g_data.G = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			g_data.F = g_data.B ^ g_data.C ^ g_data.D;
            g_data.G = (3 * i + 5) % 16;
		}
		else if (i < 64)
		{
			g_data.F = g_data.C ^ (g_data.B | (~g_data.D));
            g_data.G = (7 * i) % 16;
		}
		// printf("%sF: [%x]%s\n", GREEN, g_data.F, NORMAL);
		g_data.F = g_data.F + g_data.A + g_keys_md5[i] + g_data.M[g_data.G];
		// printf("%s(%x %x %x %d)\n%s", CYAN, g_data.A, g_keys_md5[i], g_data.M[g_data.G], g_data.G, NORMAL);
        g_data.A = g_data.D;
        g_data.D = g_data.C;
        g_data.C = g_data.B;
        g_data.B = g_data.B + leftrotate(g_shift[i++]);
		// printf("%d\n", leftrotate(g_shift[i - 1]));
		// printf("%s[%x][%x][%x][%x]%s\n", YELLOW, g_data.A, g_data.B, g_data.C, g_data.D, NORMAL);
	}
}

int		handle_md5(void)
{
	int		i;//, j = 0;

	if (add_padding() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// printf("%s[%d] [%x][%x][%x][%x] [%s][%s]%s\n", YELLOW, g_data.len, g_data.h0, g_data.h1, g_data.h2, g_data.h3, g_data.str, g_data.fullstr, NORMAL);
	i = 0;
	while (i < g_data.len)
	{
		// printf("why1\n");
		// printf("%d [%c]\n", j, g_data.fullstr[i]);
		// printf("%x%x%x%x\n", g_data.h0, g_data.h1, g_data.h2, g_data.h3);
		g_data.M = (uint32_t *)&(g_data.fullstr[i]);
		g_data.A = g_data.h0;
		g_data.B = g_data.h1;
		g_data.C = g_data.h2;
		g_data.D = g_data.h3;
		// printf("%x%x%x%x\n", g_data.A, g_data.B, g_data.C, g_data.D);
		
		// printf("why2\n");
		md5_rounds();
		// printf("why3\n");
 		g_data.h0 += g_data.A;
    	g_data.h1 += g_data.B;
   		g_data.h2 += g_data.C;
    	g_data.h3 += g_data.D;
		// printf("%s[%x][%x][%x][%x]%s\n", YELLOW, g_data.h0, g_data.h1, g_data.h2, g_data.h3, NORMAL);
		// printf("%s(%x %x %x %d)\n%s", CYAN, g_data.A, g_data.B, g_data.C, g_data.D, NORMAL);
		// printf("%s%x%x%x%x%s\n", YELLOW, g_data.h0, g_data.h1, g_data.h2, g_data.h3, NORMAL);
		// printf("why4\n");
		i += 64;
	}
	append_chunks_md5();
	return (EXIT_SUCCESS);
}


