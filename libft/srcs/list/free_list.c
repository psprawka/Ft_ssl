/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 03:35:33 by psprawka          #+#    #+#             */
/*   Updated: 2018/07/16 09:14:44 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_list(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		free(*list);
		*list = tmp;
	}
}
