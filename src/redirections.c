#include "minishell.h"

void heredoc(t_redirect *red, t_pipe *p/* ,  t_data *data */)
{
    t_redirect *tmp;
    char       *s;
    int        fd[2];

    tmp = red;
    while (tmp)
    {
        pipe(fd);
        if (tmp->flag == HEREDOC) // tmp->flag == HEREDOC
        {
            while (1)
            {
                s = readline("heredoc>");
                if (ft_strcmp(s, tmp->f_name) == 0)
                {
                    free(s);
                    s = NULL;                    
                    break;
                }
                write(fd[1], s, ft_strlen(s));
                write(fd[1], "\n", 1);
            }
            close(fd[1]);
            p->heredoc_f = 1;
            tmp->heredoc_fd = fd[0];
        }
        tmp = tmp->next;
    }
}

// void append_red(t_redirect *red,  t_pipe *pipe)
// {
//     t_redirect *tmp;

//     tmp = red;
//     while (tmp)
//     {
//         if (ft_strcmp(tmp->flag, /* ">>" */O_APPEND) == 0) // tmp->flag == O_APPEND
//         {
//             if (tmp->f_name == NULL)
//                 return ;
//             red->fd_ap = open(tmp->f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
//             if (red->fd_ap == -1)
//                 perror("Can't open file");
//             pipe->append_f = 1;
//         }
//         tmp = tmp->next;
//     }
// }

// void    infile(t_redirect *red,  t_pipe *pipe)
// {
//     t_redirect *tmp;

//     tmp = red;
//     while (tmp)
//     {
//         if (ft_strcmp(tmp->flag, /* "<" */O_RDONLY) == 0) // tmp->flag == O_RDONLY
//         {
//             if (tmp->f_name == NULL)
//                 return ;
//             red->fd_in = open(tmp->f_name, O_RDONLY, 0644);
//             if (red->fd_in == -1)
//                 perror("Can't open infile");
//             pipe->infile = 1;
//         }
//         tmp = tmp->next;
//     }
// }

// void    outfile(t_redirect *red, t_pipe *pipe)
// {
//     t_redirect *tmp;

//     tmp = red;
//     while (tmp)
//     {
//         if (ft_strcmp(tmp->flag,/*  ">" */O_TRUNC) == 0) // tmp->flag = O_TRUNC
//         {
//             if (tmp->f_name == NULL)
//                 return ;
//             red->fd_out = open(tmp->f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (red->fd_out == -1)
//                 perror("Can't open outfile");
//             pipe->outfile = 1;
//         }
//         tmp = tmp->next;
//     }
// }

// void choose_redirect(t_pipe *pipe, t_redirect *red)
// {
//     if (pipe->heredoc_f == 1)
//     {
//         dup2(red->fd_herdoc, 0);
//         pipe->heredoc_f = 0;
//     }
// 	else if (pipe->infile == 1)
// 	{
// 		dup2(red->fd_in, 0);
// 		pipe->infile = 0;
// 		close(red->fd_in);
// 	}
// 	else if (pipe->outfile == 1)
// 	{
// 		dup2(red->fd_out, 1);
// 		pipe->outfile = 0;
// 		close(red->fd_out);
// 	}
// 	else if (pipe->append_f == 1)
// 	{
// 		dup2(red->fd_ap, 1);
// 		pipe->append_f = 0;
// 		close(red->fd_ap);
// 	}
// }
