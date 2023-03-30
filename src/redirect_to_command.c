/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_to_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhechoy <tkhechoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:44:36 by tkhechoy          #+#    #+#             */
/*   Updated: 2023/03/30 17:04:12 by tkhechoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// ls">" asfas
int	redirect_to_command(t_pipe *top, int *i)
{
	int 	k;
	char	*tmp_1;	
	char	*tmp_comand;
	
	k = 0;
	k = (*i);
	while (top->content[*i] && !ft_strchr(METACHARACTER, top->content[*i]))
	{
		*i = for_space(top->content, '\'', *i);
		*i = for_space(top->content, '"', *i);
		if (top->content[*i]  && !ft_strchr(METACHARACTER, top->content[*i]))
			(*i)++;
		// printf("cont : %s\n", top->content + *i);
	}
	tmp_comand = ft_substr(top->content, k, *i - k + 1);
	tmp_1 = ft_strtrim(tmp_comand, METACHARACTER);
	free(tmp_comand);
	top->joined_argv = ft_strjon_free_arg1(top->joined_argv, tmp_1);
	free(tmp_1);
	// top->s = ft_strjoin(top->s, ft_strtrim(tmp_comand, METACHARACTER));
	tmp_1 = top->joined_argv;
	top->joined_argv = ft_strjoin_ft(top->joined_argv, 42);
	free(tmp_1);
	return (1);
}
