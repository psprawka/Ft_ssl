/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:41:57 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/16 08:39:26 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	G_data holds information about current argument to hash, g_opts holds opts
**	attached to current argument.
*/ 
t_data	g_data;
char	g_opts;


/*
**	For each algorithm, one row in a dispatch table below contains: algo's
**	name, a pointer to function creating a hash and a pointer to function
**	reseting data in g_data variable.
*/
t_fcts	g_hash_fcts[] =
{
	{"md5", handle_md5, reset_md5},
	{"sha256", handle_sha256, reset_sha256},
	{NULL, NULL, NULL}
};


/*
**	A main funtion first parses arguments from command line, then for all
**	arguments to hash initializes their data (init_data) and executes chosen
**	hash algorithm.
*/
int		main(int ac, char **av)
{
	int		i;

	if (ac < 2)
		return (error(1, NULL, true));
	if (get_algorithm(av[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	i = 2;
	while (i < ac)
		get_arg(ac, av, &i);
	if (ac == 2 || !g_data.nb_files)
	{
		reset_data();
		get_file(STDIN_FILENO);
		g_data.fct();
		print_result();
	}
	return (EXIT_SUCCESS);
}