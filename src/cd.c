/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adashyan <adashyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:49:07 by tkhechoy          #+#    #+#             */
/*   Updated: 2023/04/01 20:32:30 by adashyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **argv, t_data *data)
{
	if (!argv[1])
	{
		if (chdir(ft_get_value("HOME", data)) != 0)
		{
			ft_printf(2, "minishell:  %s: %s: No such file or directory\n",
				argv[0], argv[1]);
			return (1);
		}
	}
	else if (chdir(argv[1]) != 0)
	{
		ft_printf(2, "minishell:  %s: %s: No such file or directory\n",
			argv[0], argv[1]);
		return (1);
	}
	return (0);
}
