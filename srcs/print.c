/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 06:21:06 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/16 08:29:40 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		is_regfile(char *path)
{
	struct stat info;

	stat(path, &info);
	return (S_ISREG(info.st_mode));
}

int		print_result(void)
{
	if (g_opts & OPT_P)
		ft_printf("%s", g_data.name);
	else if ((g_opts & OPT_S) && !(g_opts & OPT_R) && !(g_opts & OPT_Q))
		is_regfile(g_data.name) ? ft_printf("%s (%s) = ", g_data.hname, g_data.name)
			: ft_printf("%s (\"%s\") = ", g_data.hname, g_data.name);
	else if (is_regfile(g_data.name) && !(g_opts & OPT_R) && !(g_opts & OPT_Q))
		ft_printf("%s (%s) = ", g_data.hname, g_data.name);
	
		
	ft_printf("%s", g_data.fullstr);
	
	if ((g_opts & OPT_S) && (g_opts & OPT_R) && !(g_opts & OPT_Q) && !(g_opts & OPT_P))
		is_regfile(g_data.name) ? ft_printf(" %s", g_data.name)
			: ft_printf(" \"%s\"", g_data.name);
	else if (is_regfile(g_data.name) && (g_opts & OPT_R) && !(g_opts & OPT_Q))
		ft_printf(" %s", g_data.name);
	
	ft_printf("\n");
	return (EXIT_SUCCESS);
}
