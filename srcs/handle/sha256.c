/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 22:59:36 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/16 07:50:33 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

# define SHR(x, n)		x >> n
# define ROTR(x, y)		(x >> y | (x << (32 - y)))
# define SSIG0(x)		ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3)
# define SSIG1(x)		ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10)
# define BSIG0(x)		ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25)
# define BSIG1(x)		ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22)

# define CH(x, y, z)	(x & y) ^ ((~x) & z)
# define MAJ(x, y, z)	(x & y) ^ (x & z) ^ (y & z)

const uint32_t g_keys_sha256[] =
{
   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
   0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
   0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
   0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
   0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
   0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
   0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
   0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
   0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};



void		append_chunks_sha256(void)
{
	// g_data.h0 = swap_uint32(g_data.h0);
	// g_data.h1 = swap_uint32(g_data.h1);
	// g_data.h2 = swap_uint32(g_data.h2);
	// g_data.h3 = swap_uint32(g_data.h3);
	// g_data.h4 = swap_uint32(g_data.h4);
	// g_data.h5 = swap_uint32(g_data.h5);
	// g_data.h6 = swap_uint32(g_data.h6);
	// g_data.h7 = swap_uint32(g_data.h7);
	// printf("[%x][%x][%x][%x][%x][%x][%x][%x]\n", g_data.h0, g_data.h1, g_data.h2, g_data.h3, g_data.h4, g_data.h5, g_data.h6, g_data.h7);
	if (!(g_data.wtf = ft_memalloc(8 * sizeof(uint32_t))))
		return ;
	
	ft_strcpy((char *)g_data.wtf, ft_convert_hex(g_data.h0, 0));
	ft_strcat((char *)g_data.wtf, ft_convert_hex(g_data.h1, 0));
	ft_strcat((char *)g_data.wtf, ft_convert_hex(g_data.h2, 0));
	ft_strcat((char *)g_data.wtf, ft_convert_hex(g_data.h3, 0));
	ft_strcat((char *)g_data.wtf, ft_convert_hex(g_data.h4, 0));
	ft_strcat((char *)g_data.wtf, ft_convert_hex(g_data.h5, 0));
	ft_strcat((char *)g_data.wtf, ft_convert_hex(g_data.h6, 0));
	ft_strcat((char *)g_data.wtf, ft_convert_hex(g_data.h7, 0));

	g_data.fullstr = (unsigned char *)g_data.wtf;

	
}

void	initialize_sha256(void)
{
	int			i;
	int			x;
	uint32_t	s0;
	uint32_t	s1;
	
	i = 0;
	x = 0;
	while (i < 16)
	{
		g_data.W[x] = (g_data.wtf[i]);
		// g_data.W[x] = g_data.W[x];
		// g_data.W[x] = swap_uint32(g_data.W[x]);
		x++;
		i += 1;
	}
		
	while (x < 64)
	{
		s0 = SSIG0(g_data.W[x - 15]);
		s1 = SSIG1(g_data.W[x - 2]);
		g_data.W[x] = g_data.W[x - 16] + s0 + g_data.W[x - 7] + s1;
		// g_data.W[x] = swap_uint32(g_data.W[x]);
		x++;
	}
}

void	algorithm_sha256(void)
{
	int i;
	uint32_t S1;
	uint32_t ch;
	uint32_t temp1;
	uint32_t S0;
	uint32_t maj;
	uint32_t temp2;
	
	i = 0;
	while (i < 64)
	{
		S1 = BSIG0(g_data.E);
		ch = CH(g_data.E, g_data.F, g_data.G);
		temp1 = g_data.H + S1 + ch + g_keys_sha256[i] + g_data.W[i];
		S0 = BSIG1(g_data.A);
		maj = MAJ(g_data.A, g_data.B, g_data.C);
		temp2 = (S0 + maj);
		g_data.H = g_data.G;
		g_data.G = g_data.F;
		g_data.F = g_data.E;
		g_data.E = g_data.D + temp1;
		g_data.D = g_data.C;
		g_data.C = g_data.B;
		g_data.B = g_data.A;
		g_data.A = temp1 + temp2;
		i++;
	}	
}

int		handle_sha256(void)
{
	int			i;

	if (add_padding_sha256() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	
	reset_data();
	// printf("[%x][%x][%x][%x][%x][%x][%x][%x]\n", g_data.h0, g_data.h1, g_data.h2, g_data.h3, g_data.h4, g_data.h5, g_data.h6, g_data.h7);
	// 	printf("[%x][%x][%x][%x][%x][%x][%x][%x]\n", g_data.A, g_data.B, g_data.C, g_data.D, g_data.E, g_data.F, g_data.G, g_data.H);
	i = 0;
	while (i < g_data.len)
	{
		// printf("How many?\n");
		initialize_sha256();
		// printf("VAR2: %d %u\n", i / 64, g_data.len);
		g_data.A = g_data.h0;
		g_data.B = g_data.h1;
		g_data.C = g_data.h2;
		g_data.D = g_data.h3;
		g_data.E = g_data.h4;
		g_data.F = g_data.h5;
		g_data.G = g_data.h6;
		g_data.H = g_data.h7;
		// printf("[%x][%x][%x][%x][%x][%x][%x][%x]\n", g_data.h0, g_data.h1, g_data.h2, g_data.h3, g_data.h4, g_data.h5, g_data.h6, g_data.h7);
		// printf("%s we are here: [%x][%x][%x][%x][%x][%x][%x][%x]%s\n", GREEN, g_data.A, g_data.B, g_data.C, g_data.D, g_data.E, g_data.F, g_data.G, g_data.H);
		
		algorithm_sha256();
		// printf("[%x][%x][%x][%x][%x][%x][%x][%x]\n", g_data.A, g_data.B, g_data.C, g_data.D, g_data.E, g_data.F, g_data.G, g_data.H);
		g_data.h0 += g_data.A;
		g_data.h1 += g_data.B;
		g_data.h2 += g_data.C;
		g_data.h3 += g_data.D;
		g_data.h4 += g_data.E;
		g_data.h5 += g_data.F;
		g_data.h6 += g_data.G;
		g_data.h7 += g_data.H;
		i += 64;
		// printf("AFTER: [%x][%x][%x][%x][%x][%x][%x][%x]\n", g_data.h0, g_data.h1, g_data.h2, g_data.h3, g_data.h4, g_data.h5, g_data.h6, g_data.h7);
	}
	append_chunks_sha256();
	return (EXIT_SUCCESS);
	
	
}
