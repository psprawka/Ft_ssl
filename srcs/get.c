/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 04:07:26 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/16 08:43:45 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Function get_algorithm() determines what type of hashing algorithm will be
**	used throughout a program and assigns its pointer to g_data.fct_hash var.
*/
int 	get_algorithm(char *algorithm)
{
	int		i;

	i = 0;
	while (g_hash_fcts[i].fct_hash)
	{
		if (!ft_strcmp(algorithm, g_hash_fcts[i].name))
		{
			g_data.fct = g_hash_fcts[i].fct_hash;
			g_data.hname = algorithm;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (error(2, algorithm, true));
}


/*
**	Functions get_file() and readfile() handle files and stdin and assign
**	argument's content to g_data.str variable. Both return EXIT_SUCCESS upon
**	success, otherwise EXIT_FAILURE is returned.
*/
int		get_file(int fd)
{
	char	*buff;
	char	*final;
	int		res;

	g_data.nb_files++;
	if (!(final = ft_strnew(1)) || !(buff = ft_strnew(BUFF_SIZE)))
		return (error(0, "Ft_strnew", true));
	while ((res = read(fd, buff, BUFF_SIZE - 1)) > 0)
	{
		final = ft_strjoin(final, buff, 0);
		ft_bzero(buff, BUFF_SIZE);
	}
	free(buff);
	if (res == -1)
		return (EXIT_FAILURE);
	g_data.str = final;
	g_data.len = ft_strlen(final);
	return (EXIT_SUCCESS);
}

int		readfile(char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		g_data.nb_files++;
		g_opts |= OPT_BROKEN_S;
		return (error(5, file, true));
	}
	if (get_file(fd) == EXIT_FAILURE)
	{
		if (errno & EISDIR)
			return (error(6, file, true));
		return (error(0, "Read", true));
	}
	close(fd);
	g_data.name = file;
	if (g_opts & OPT_S)
		g_opts |= OPT_BROKEN_S;
	return (EXIT_SUCCESS);
}


int		get_opts_s(int ac, char **av, int *i, int j)
{
	g_opts |= OPT_S;
	if (av[*i][j + 1])
		g_data.str = &(av[*i][j + 1]);
	else if (av[*i + 1] && (*i)++)
		g_data.str = av[*i];
	else
		return (error(4, NULL, true));
	
	g_data.len = ft_strlen(g_data.str);
	g_data.name = g_data.str;
	g_data.fct();
	print_result();
	g_data.nb_files++;
	return (EXIT_SUCCESS);
}


int		get_opts(int ac, char **av, int *i)
{
	int		j;
	
	j = 0;
	while (av[*i][++j])
	{
		if (av[*i][j] == 'p')
		{
			g_opts |= OPT_P;
			get_file(STDIN_FILENO);
			g_data.name = g_data.str;
			g_data.fct();
			print_result();
			reset_data();
			g_opts &= ~OPT_P;
		}
		else if (av[*i][j] == 'r')
			g_opts |= OPT_R;
		else if (av[*i][j] == 'q')
			g_opts |= OPT_Q;
		else if (av[*i][j] == 's')
			return (get_opts_s(ac, av, i, j));
		else
			return (error(3, &(av[*i][j]), true));
	}
	return (EXIT_SUCCESS);
}


int		get_arg(int ac, char **av, int *i)
{
	while (*i < ac)
	{
		reset_data();
		if (g_opts & OPT_BROKEN_S || av[*i][0] != '-')
		{
			if (readfile(av[*i]) == EXIT_SUCCESS)
			{
				g_data.fct();
				print_result();
			}
			(*i)++;
			return (EXIT_SUCCESS);
		}
		if (get_opts(ac, av, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		(*i)++;
	}
	return (EXIT_SUCCESS);
}
