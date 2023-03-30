/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhechoy <tkhechoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:29:33 by tkhechoy          #+#    #+#             */
/*   Updated: 2023/03/29 21:59:31 by tkhechoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_in_out(int i, t_data *data, int count, t_pipe *pipe)
{
	// Grel nayev piperi myus paymanneri hamar
	if (i == 0)
	{
		printf("heredoc%d\n", pipe->heredoc_f);
		if (pipe->heredoc_f == 1)
    	{
	    	dup2(red->heredoc_fd, 0);
			pipe->heredoc_f = 0;
    	}
		// else if (pipe->infile == 1)
		// {
		// 	dup2(red->fd_in, 0);
		// 	pipe->infile = 0;
		// 	close(red->fd_in);
		// }
		// else 
		// if (pipe->outfile == 1)
		// {
		// 	dup2(red->fd_out, 1);
		// 	pipe->outfile = 0;
		// 	close(red->fd_out);
		// }
		// else if (pipe->append_f == 1)
		// {
		// 	printf("blahblah\n");
		// 	dup2(red->fd_ap, 1);
		// 	pipe->append_f = 0;
		// 	close(red->fd_ap);
		// }
		// else
		// {
		if (pipe->fd_in != 0)
			dup2(pipe->fd_in, STDIN_FILENO); // sovorel 
		if (pipe->fd_out != 1)
			dup2(pipe->fd_out, STDOUT_FILENO); // sovorel
		else if (data->pipe_count > 1)
			dup2(data->fd[i][1], STDOUT_FILENO); // sovorel
		}
	}
	else if (i ==  count - 1)
	{	
		// if (pipe->heredoc_f == 1)
    	// {
        // 	// printf("hello\n");
	    // 	dup2(red->fd_herdoc, 0);
		// 	pipe->heredoc_f = 0;
    	// }
		// /* else */ if(pipe->infile == 1)
		// {
		// 	// dup2(red->fd, STDOUT_FILENO);
		// 	printf("hello\n");
		// 	dup2(red->fd_in, 0);
		// }
		// else
		if (pipe->fd_out != 1)
			dup2(pipe->fd_out, STDOUT_FILENO); // sovorel
		if (pipe->fd_in != 0)
			dup2(pipe->fd_in, STDOUT_FILENO); // sovorel 
		else
			dup2(data->fd[i - 1][0], STDIN_FILENO);
	}				
	else
	{
		// if (pipe->heredoc_f == 1)
    	// {
	    // 	dup2(red->fd_herdoc, 0);
		// 	pipe->heredoc_f = 0;
    	// }
		// /* else */ if(pipe->infile == 1)
		// {
		// 	// dup2(red->fd, STDOUT_FILENO);
		// 	printf("hello\n");
		// 	dup2(red->fd_in, 0);
		// }
		// else
		// {
		if (pipe->fd_in != 0)
			dup2(pipe->fd_in, STDOUT_FILENO); // sovorel 
		else
			dup2(data->fd[i - 1][0], STDIN_FILENO);
		if (pipe->fd_out != 1)
			dup2(pipe->fd_out, STDOUT_FILENO); // sovorel
		else
			dup2(data->fd[i][1], STDOUT_FILENO);
		// }
	}
	i = -1;
	while (++i < count)
	{
		close(data->fd[i][1]);
		close(data->fd[i][0]);
	}
	lsh_launch(data, pipe);
	exit(0);
}

void pipe_exec(t_data *data)
{
	int		i;
	int		count;

	i = 0;
	count = data->pipe_count;
	while (i < count)
	{
		if(pipe(data->fd[i]) == -1)
		{
			// TODO close pipes go to readline
			printf("error\n");
			return ;   // mtacel                
		}
		i++;
	}
}

void pipe_close_and_wait_parent(t_data *data)
{
	int		i;
	int		count;

	i = -1;
	count = data->pipe_count;
	while (++i < count)
	{
		close(data->fd[i][1]);
		close(data->fd[i][0]);
	}
	i = -1;
	while (++i < count)
	{
	// 	i =
	 waitpid(-1, NULL, 0);
		// wait(0); // poxel waitpid
	}
}
void pipe_exec(t_data *data, t_redirect *red)
{
	int		i;
	int		count;
	t_pipe *tmp;

	i = 0;
	count = data->pipe_count;
	data->fd = malloc(sizeof(int [2]) * count);
	pipe_exec_error_or_create(data);	
	tmp = data->pipe;
	while (tmp)
	{
		pid_t id = fork();
		if (id == -1)
		{
			perror("Error: fork\n");
			// TODO close pipes
		}
		if (id == 0)
			pipe_in_out(i, data, count, tmp);		
		tmp = tmp->next;
		i++;
	}
	i = -1;
	while (++i < count)
	{
		close(data->fd[i][1]);
		close(data->fd[i][0]);
	}
	i = -1;
	while (++i < count)
	{
	// 	i = waitpid(-1, NULL, 0);
		wait(0); // poxel waitpid
	}
}
