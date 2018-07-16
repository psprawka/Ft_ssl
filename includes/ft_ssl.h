/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:50:29 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/16 08:36:01 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include <math.h>
# include <string.h>

# define OPT_P			1
# define OPT_Q			2
# define OPT_R			4
# define OPT_S			8
# define OPT_BROKEN_S	16

typedef struct	s_fcts
{
	char	*name;						/* name of a hashing algorithm */
	int		(*fct_hash)(void);			/* ptr to hash function */
	void	(*fct_reset)(void);			/* ptr to reset function */
}				t_fcts;

typedef struct	s_data
{
	char			opts;				/* options passed in command line */
	char			*name;				/* file name */
	char			*hname;				/* hash name */
	char			*str;				/* string to hash */
	unsigned char 	*fullstr;			/* string with padding to hash */
	uint32_t		len;				/* length of a string to hash */
	int				(*fct)(void);		/* ptr to hash function */
	uint32_t		*wtf;
	int				nb_files;
	
	uint32_t	h0;				/* hash's 0 chunk - used by md5 and sha256 */
	uint32_t	h1;				/* hash's 1 chunk - used by md5 and sha256 */
	uint32_t	h2;				/* hash's 2 chunk - used by md5 and sha256 */
	uint32_t	h3;				/* hash's 3 chunk - used by md5 and sha256 */
	uint32_t	h4;				/* hash's 4 chunk - used by sha256 */
	uint32_t	h5;				/* hash's 5 chunk - used by sha256 */
	uint32_t	h6;				/* hash's 6 chunk - used by sha256 */
	uint32_t	h7;				/* hash's 7 chunk - used by sha256 */


	uint32_t	A;
	uint32_t	B;
	uint32_t	C;
	uint32_t	D;
	uint32_t	E;
	uint32_t	F;
	uint32_t	G;
	uint32_t	H;
	
	uint32_t	*M;
	uint32_t	W[64];
}				t_data;

extern t_data	g_data;
extern char		g_opts;
extern t_fcts	g_hash_fcts[];

/*
**	handle/
*/
int		handle_md5(void);
int		handle_sha256(void);
int		add_padding(void);
int		add_padding_sha256(void);


/*
**	get.c
*/
int 	get_algorithm(char *algorithm);
int		get_file(int fd);
int		readfile(char *file);
int		get_opts(int ac, char **av, int *i);
int		get_arg(int ac, char **av, int *i);

/*
**	print.c
*/
int		print_result(void);


/*
**	reset_data.c
*/
void	reset_md5(void);
void	reset_sha256(void);
void	reset_data(void);


/*
**	tools.c
*/
int			error(int errnb, char *msg, bool ifailure);
uint32_t	swap_uint64(uint64_t val);
uint32_t	swap_uint32(uint32_t val);

#endif
