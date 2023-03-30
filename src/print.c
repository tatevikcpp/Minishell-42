#include "minishell.h"
#include <fcntl.h> 

void print_env(t_data *data)
{
	int i = 0;
	while (data->env[i])
	{
		printf("data.env = %s\n", data->env[i]);
		i++;
	}	
}

void print_lists(t_pipe *red)
{
	t_pipe *head;

	head = red;
	while (head)
	{
		//printf("content: %s\n", head->content);
		head = head->next;
	}
}

void printf_pipe(t_pipe *pipe)
{
	t_pipe *pipe_in;
	int i = 0;

	pipe_in = pipe;
	while (pipe_in)
	{
		printf("⛩  pipe [%d]\n", i++);
		int i = 0;
		// print_list(pipe_in->red);
		// printf("argv ***********************************\n");
		while (pipe_in->argv && pipe_in->argv[i])
		{
			printf("argv[%d] = %s\n, ", i, pipe_in->argv[i]);
			i++;
		}
		// printf("\nfd_in %d, ", pipe_in->fd_in);
		// printf("fd_out %d", pipe_in->fd_out);
		// printf("\nargv ***********************************\n");
		pipe_in = pipe_in->next;
	}
}

void print_list(t_redirect *red)
{
	t_redirect *head;

	printf("redirections ***********************************\n");
	head = red;
	while (head)
	{
		printf("f_name: [%s]", head->f_name);
		printf("  Mode = ");
		if (head->flag == HEREDOC)
			printf("HEREDOC\n");
		if (head->flag == O_APPEND)
			printf("O_APPEND\n");
		if (head->flag == O_RDONLY)
			printf("O_RDONLY\n");
		if (head->flag == O_TRUNC)
			printf("O_TRUNC\n");
		
		head = head->next;
	}
	printf("redirections ***********************************\n");
}

void print_list_head_env(t_data *data)
{
	t_env *head;

	head = data->head_env;
	while (head)
	{
		printf("head->key: %s\nhead->val: %s\n", head->key, head->val);
		if (head->next == NULL)
			return ;
		head = head->next;
	}
}

void print_list_head_env_pipe(t_pipe *pipe)
{
	printf("ok\n");
	t_env *head;

	head = pipe->head_env;
	while (head)
	{
		printf("head->key: %s\nhead->val: %s\n", head->key, head->val);
		if (head->next == NULL)
			return ;
		head = head->next;
	}
}
