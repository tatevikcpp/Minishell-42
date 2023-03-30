#include "minishell.h"

void printf_pipe(t_pipe *pipe);

int open_files_for_redirect (t_pipe *pipe)
{
    t_redirect *head_red;

    head_red = pipe->red;
    while (head_red)
    {
        if (head_red->flag == O_RDONLY)
        {
            if (pipe->fd_in != 0)
                close(pipe->fd_in);
            pipe->fd_in = open(head_red->f_name, head_red->flag);
            if (pipe->fd_in == -1)
            {
                perror("minishell: open: ");
                return (1);
            }
        }
        else if (head_red->flag == O_TRUNC || head_red->flag == O_APPEND)
        {
            if (pipe->fd_out != 1)
                close(pipe->fd_out);
            pipe->fd_out = open(head_red->f_name, O_CREAT | head_red->flag | O_WRONLY, 0644);
            if (pipe->fd_out == -1)
            {
                perror("minishell: open: ");
                return (1);
            }
        }
        else if (head_red->flag == HEREDOC)
            pipe->fd_in = head_red->heredoc_fd;
        head_red = head_red->next;
    }
    return (0);
}

int check_errors(char *ptr)
{
    int i;

    i = 0;
    while (ptr[i])
    {
        if (metachar_error(ptr) == 1 ) //  > a   - ?
            return (1); //continue
        if (syntax_error(ptr, i) == 1)
           return (1); //continue
        if (metachar_error(ptr) == 1)
           return (1);	//continue  // kara chlini
        // check_qoutes(ptr); // sxala ashxatum
        // check_quot_double(ptr);
        // check_quot_one(ptr);
        if (ptr[i])
            i++;
    }
    return (0);
}

// $ls|"$ls   "
//  asfas >>   out
int parsing(t_data *data, char *ptr)  //return 
{
    // if (check_errors(ptr)) 
    //     return (-1);
    // if (syntax_error(ptr, &i) == 1 || metachar_error(ptr) == 1 ) // >a     ev ls|ls | "|ls|"
    // 	continue ;
    // if (syntax_error(ptr, &i) == 1)
    // 	continue ;
    // if (metachar_error(ptr) == 1)
    // 	continue ;							// kara chlini
    // check_qoutes(ptr); // sxala ashxatum

    // check_quot_double(ptr);
    // check_quot_one(ptr);
    // print_list_head_env(data);
    split_string(ptr, data); // ls|ls | "|ls|"  sxala ashxatum
    // print_lists(data->pipe);
    t_pipe *tmp1 = data->pipe;
    while (tmp1) //pttvum e michpaipain taracutjunerov u juraqanchjuri hamar gtnum redirektnery u faili anuner@
    {
        tmp1->red = redirect_test(tmp1); // sxal ls>a>b

        if (open_files_for_redirect(tmp1) != 0)
            return (1);
        split_s__to_argv(data, tmp1); // *(42) => 1
        tmp1 = tmp1->next;
    }
    printf_pipe(data->pipe);
    printf("pipe count: %d\n", data->pipe_count);
    return (0);
}