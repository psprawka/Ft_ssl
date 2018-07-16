/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 11:13:42 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/17 13:15:27 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoi(char *s)
{
	long long	nb;
	int			i;

	i = 0;
	nb = 0;
	while ((*s == ' ' || *s == '\n' || *s == '\t') && *s != '\0')
		s++;
	s[i] == '-' || s[i] == '+' ? i++ : i;
	while (s[i] > 47 && s[i] < 58)
	{
		nb *= 10;
		nb += s[i++] - 48;
	}
	nb = s[0] == '-' ? nb * -1 : nb;
	return (nb);
}
