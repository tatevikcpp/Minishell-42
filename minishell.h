#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/stat.h> 
# include "./libft/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# define HEREDOC 5

# define METACHARACTER "|&;<>() \n\t"

/* typedef struct s_pipe
{
	// char			**argv;
	char			*content;
	struct s_pipe	*next;
}	t_pipe; */

typedef struct s_redirect
{
	// int	flag;  // O_APPEND || O_TRUNC || O_RDONLY || HEREDOC
	char *f_name;
	char *flag;
	// char *type;  // petq chi
	struct s_redirect *next;
} t_redirect;

typedef struct s_env
{
	char 			*key;
	char 			*val;
	struct s_env	*next;
}t_env;

typedef struct s_pipe
{
	char			*content;
	int				fd_in;  // 0
	int				fd_out; // 1
	char			**argv; // null
	t_redirect		*red; // null
	t_env			*head_env;  // data->env;
	char			**env;  // env;
	int				*(fd)[2]; // read-0 write-1
	struct s_pipe	*next;  // null
}	t_pipe;


typedef struct s_data
{
	t_env	*head_env;
	char	**env;
	char	**splited_pipe;
	t_pipe *pipe;
	int		pipe_count;
	int 	len_key_sum;
	int 	len_val_sum;
} t_data;

//***********************Tatev


char **ft_split(char const *s, char c);
int	ft_strcmp(char *s1, char *s2);
char	*ft_substr(char const	*s, unsigned int start, size_t len);
char *ft_get_value(char *key, t_data *ptr);
// int  herdoc(int c, char **v);
t_redirect	*redirect(t_pipe *pipe);
//***************** Tatev

bool	is_space(char c);
bool    is_pipe(char c);
bool    is_redirect_in(char c);
bool    is_redirect_out(char c);
bool    is_append_in(char c, char d);
bool    is_append_out(char c, char d);
char	*valid_ls(char *str);
// t_pipe *get_pipe_readline(t_data *data);
void	split_string(char *input, t_data *data);
// void print_list(t_redirect *red);
void print_list_head_env(t_data data);
void print_lists(t_pipe *red);
int get_readline(t_data *data);
int init(t_data	*data, char **envp);
void	ft_lstadd_back(t_pipe **lst, t_pipe *new);
void	ft_lstadd_front(t_pipe **lst, t_pipe *new);
t_pipe	*ft_lstnew(void *content, t_env *env);
t_pipe	*ft_lstlast(t_pipe *lst);
char *check_quot_double(char *ptr);
char *check_quot_one(char *ptr);
void	struct_zeroed(t_data *data, char **env);
int  for_space(char *ptr, char c, int i);
void send_env(t_data *data);
void print_env(t_data *data);
void print_list(t_redirect *red);
// void hendl_dolar(t_data *data);
char *access_path(t_data *data);
int lsh_launch(t_data *data);
void pipe_exec(t_data *data);

//
char *fun(char *top, int *i);
t_redirect		*ft_t_redirect_last(t_redirect *lst);
void		ft_t_redirect_add_back(t_redirect **lst, t_redirect *new);
t_redirect 	*new_t_redirect(char *f_name, char *flag);

void	redirect_f_name_flag(t_pipe *top,t_redirect **head, int *i);
void	redirect_to_command(t_pipe *top, int *i) ;

t_pipe *new_t_pipe(char **tmp);
t_pipe	*ft_t_pipe_last(t_pipe *lst);
void	ft_t_pipe_add_back(t_pipe **lst, t_pipe *new);

void hendl_dolar(t_data *data, char *str);
char *hendl_dolar_inline(t_data *data, char *str);

void builtin_export(t_env *head_env, char *ptr);
void split_readline(char *ptr,t_pipe *pipe, t_data *data);

t_env 	*new_t_env(char *tmp, char* tmp1);
t_env	*ft_t_env_last(t_env *lst);
void	ft_t_env_add_back(t_env **lst, t_env *new);

#endif
