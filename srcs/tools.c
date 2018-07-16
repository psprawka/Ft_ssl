/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 01:26:40 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/16 03:54:01 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	An error function just handles all error messages based on the number
**	sent in function call. If number is not found, strerror mesage is sent.
**	I bool flag (ifailure) is set to true func returns EXIT_FAILURE,
**	otherwise EXIT_SUCCESS.
*/
int			error(int errnb, char *msg, bool ifailure)
{
	if (errnb == 1)
		printf("usage: ft_ssl command [command opts] <command args>\n");
	else if (errnb == 2)
		printf("ft_ssl: Error: '%s' is an invalid command.\n\nStandard commands:\n\nMessage Digest commands:\nmd5, sha256\n\nCipher commands:\n\n", msg);
	else if (errnb == 3)
		printf("ft_ssl: Illegal option -- %s\n", msg);
	else if (errnb == 4)
		printf("ft_ssl: option requires an argument -- s\n");
	else if (errnb == 5)
		printf("ft_ssl: %s: No such file or directory\n", msg);
	else if (errnb == 6)
		printf("ft_ssl: %s: Is a directory\n", msg);
	else
		printf("%s%s: %s%s\n", RED, msg, strerror(errno), NORMAL);
	return (ifailure == true ? EXIT_FAILURE : EXIT_SUCCESS);
}


uint32_t swap_uint64(uint64_t val)
{
	return ((val << 56 & 0xff00000000000000) | (val << 40 & 0xff000000000000) |
		(val << 24 & 0xff00000000) | (val << 8 & 0xff00000000) | (val >> 8 & 0xff000000) |
		(val >> 24 & 0xff0000) | (val >> 40 & 0xff00) | (val >> 56 & 0xff));
}

uint32_t swap_uint32(uint32_t val)
{
	return ((val >> 24 & 0xff) | (val >> 8 & 0xff00) | (val << 8 & 0xff0000)
		| (val << 24 & 0xff000000));
}