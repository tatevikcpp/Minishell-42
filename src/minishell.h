#ifndef MINISHELL_H
# define MINISHELL_H

/* ---- Used Libraries ---- */
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h> 
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
/* ------------------------ */

/* ----- Constants ----- */
# define HEREDOC 5
# define METACHARACTER "|&;()<> \n\t"
# define METACHARACTER_ERROR "|&;)(<>"
/* --------------------- */

/* ----- Structures ----- */
typedef struct s_redirect
{
	int					flag;  // O_APPEND || O_TRUNC || O_RDONLY || HEREDOC
	char				*f_name;
	int					heredoc_fd;
	int	 				fd_in;
	int					fd_out;
	int	 				fd_ap;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_env
{
	char				*key;
	char				*val;
	struct s_env		*next;
}	t_env;

typedef struct s_pipe
{
	char				*joined_argv;
	char				*content;
	int					fd_in;  // 0
	int					fd_out; // 1
	char				**argv; // null
	t_redirect			*red; // null
	t_env				*head_env;  // data->env;
	// char				**env;  // env;
	// int					infile;
	// int					outfile;
	// int					append_f;
	// int					heredoc_f;
	struct s_pipe		*next;  // null
}	t_pipe;

typedef struct s_data
{
	int					(*fd)[2]; // read-0 write-1  // NULL
	t_env				*head_env;
	char				**env;
	// char				**splited_pipe;  // 
	t_pipe				*pipe;        // NULL
	int					pipe_count;   // 0
	int					len_key_sum;  // 0
	int					len_val_sum;  // 0
}	t_data;
/* ------------------ */

/* --------------- libft functions -------------------------------------- */
char		**ft_split(char const *s, char c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_substr(char const	*s, unsigned int start, size_t len);
char		*ft_strjoin_ft(char const *s1, char c);
/* ---------------------------------------------------------------------- */

/* ----------------------------- Parsing ---------------------------------------------- */
int 		parsing(t_data *data, char *ptr);
int 		open_files_for_redirect(t_pipe *pipe);
char		*function(t_data *data, char *test);
void		func(char *test, int j);

/* ------------------------- new lists ----------------------------- */
/* ------- env list --------- */ /* t_env.c */
t_env 		*new_t_env(char *tmp, char* tmp1);
t_env		*ft_t_env_last(t_env *lst);
void		ft_t_env_add_back(t_env **lst, t_env *new);
/* ---------------------------------------------------------------- */

/* --------- pipe list ------ */ /* t_pipe.c */
t_pipe		*ft_lstnew(void *content, t_env *env);
void		ft_lstadd_back(t_pipe **lst, t_pipe *new);
void		ft_lstadd_front(t_pipe **lst, t_pipe *new);
t_pipe		*ft_lstlast(t_pipe *lst);
t_pipe		*ft_t_pipe_last(t_pipe *lst);
t_pipe		*new_t_pipe(char **tmp);
void		ft_t_pipe_add_back(t_pipe **lst, t_pipe *new);
/* ----------------------------------------- */

/* -------- redirection list -------- */ /* t_redirect.c */
void		ft_t_redirect_add_back(t_redirect **lst, t_redirect *new);
t_redirect	*ft_t_redirect_last(t_redirect *lst);
t_redirect	*new_t_redirect(char *f_name, int flag);
// t_redirect 	*new_t_redirect(char *f_name, char *flag);
/* ----------------------------------------------------- */

/* ---------- initialize lists -------  */ /* init_stract.c */
int 		init_env(t_data	*data, char **envp);
void		struct_zeroed(t_data *data, char **env);
char 		*ft_get_value(char *key, t_data *ptr);
/* -------------------------------------------------------- */

/* --------- parsing utils ---------------- */
bool		is_space(char c);
bool    	is_pipe(char c);
bool    	is_redirect_in(char c);
bool    	is_redirect_out(char c);
bool    	is_append_in(char c, char d);
bool    	is_append_out(char c, char d);
/* ---------------------------------------- */

/* ----------- Ktrtel yev daraknerum teghadrel ---------------------- */
void		split_string(char *input, t_data *data);
t_redirect	*redirect_test(t_pipe *pipe);
int			redirect_f_name_flag(t_pipe *top,t_redirect **head, int *i);
int			redirect_to_command(t_pipe *top, int *i);
void		redirect_to_quote(t_pipe *top, int *i, char c);
void		split_s__to_argv( t_data *data,  t_pipe *pipe);
/* ----------------------------------------------------------------- */

/* ------ print for tests ---------- */
void 		print_list_head_env(t_data *data);
void 		print_lists(t_pipe *red);
void 		print_list(t_redirect *red);
void 		print_env(t_data *data);
void 		printf_pipe(t_pipe *pipe);
void 		print_list_head_env_pipe(t_pipe *pipe);
// void		print_env(t_pipe *data);
/* -------------------------------- */

/* ------------ quotes -------------- */
// int 		check_quot_double(char *ptr);
// char 		*check_quot_one(char *ptr);
int  		for_space(char *ptr, char c, int i);
char		*split_quote(char *top, int *i, char c);
// int  		for_space_quot(char *ptr, char c, int *i);
// int check_qoutes(char *str);
/* --------------------------------- */

/* ------- $ expansion --------------- */
void 		hendl_dolar(t_data *data, char *str);
char 		*hendl_doloar_comand(t_data *data, char *test);
char 		*get_dolar_val(t_data *data, char *str1);
char 		*function(t_data *data, char *test);
/* ----------------------------------- */
/* ------------------------------------------------------------------------------------ */

/* ----------------- Execution --------------------------------------------------------- */
void		execute(t_data *data);

/* ------- Pipes ------- */ /* pipe_exec.c */
void		pipe_exec(t_data *data);
void		pipe_in_out(int i, t_data *data, int count, t_pipe *pipe);
int			lsh_launch(t_data *data, t_pipe *pipe);
void pipe_exec_error_or_create(t_data *data);
void pipe_close_and_wait_parent(t_data *data);

/* -------------------- */

/* -------  Redirections ------- */ /* --- redirections.c --- */
void		infile(t_redirect *red, t_pipe *pipe);
void		outfile(t_redirect *red, t_pipe *pipe);
// void 	heredoc(t_redirect *red);
void		heredoc(t_redirect *red /*, t_pipe *p ,  t_data *data */);
void		append_red(t_redirect *red,  t_pipe *pipe);
void		choose_redirect(t_pipe *pipe, t_redirect *red);
/* ------------------------------ */

/* ----------- syntax errors -------------- */
int			syntax_error(char *ptr, int i);
int			metachar_error(char *ptr);
/* ---------------------------------------- */
/* ------------------------------------------------------------------------------------ */

/* ------------------------ Built-ins ------------------------------------------------- */
void		choose_builtin(/* char *ptr , */ t_pipe *pipe, t_data *data);
int			there_is_builtin(t_data *data);
int			ther_are_equal(char *ptr);

/* ------ export ------------ */ /* builtin_export.c */
void		builtin_export(t_data *data, t_pipe *pipe);
// void export_check(t_data *data, t_pipe *pipe, char ** str1, int *i);
void buildin_export_line( t_pipe *pipe, int *i, char **str1);
/* ----- export utils ------ */
char		*hendl_export_var(char *str1);
// void		buildin_export_all(t_data *data/* , char *ptr */);
void 		buildin_export_all(t_data *data, t_pipe *pipe);
void		buildin_export_all_by_alphabet(t_data *data,  t_pipe *pipe);
void		buildin_export_all_by_alphabet_inner(t_data *data,   t_pipe *pipe);
/* ------------------------- */
/* -------------------------------------------------- */

/* ------ echo ------------- */ /* echo.c */
void		ft_echo(char **ptr);
/* ----- echo utils -------- */
int			check_symbol(char *str);
/* -------------------------- */
/* -------------------------------------- */

/* -------- cd -------------- */ /* cd.c */
int			ft_cd(char **argv, t_data *data);
/* ------------------------------------- */

/* ---------- exit ----------- */ /* exit.c */
int			ft_exit(char **str, t_data *data);
/* ----- exit utils ----- */
int			is_digit(char *str);
int			is_char(char *str);
void		max_int(char *str, t_data *data);
int			neg_to_pos(long double nbr);
/* ---------------------- */
/* ---------------------------------------- */

/* ----- pwd ------ */ /* pwd.c */
int			ft_pwd(void);
/* ---------------------------- */

/* --------- env ----------------------------------- */ 
void		buildin_env_all(t_data *data, t_pipe *pipe); /* builtin_export.c */
void		send_env(t_data *data); /* redirect.c */
/* ------------------------------------------------- */

/* ----- unset ------------- */ /* builtin_export.c */
// void unset_buildin(t_data *data, char *ptr);
/* -------- unset utils -------- */
void		ft_list_remove_if(t_data *data,/*  void *data_ref,  */int (*cmp)(),/*  char *ptr */t_pipe *pipe);
void		remove_else_inner(t_data *data,int (*ft_strcmp)(), char **str1);
void		remove_if_inner(t_data *data, int (*ft_strcmp)(), char *str);
/* ------------------------------ */
/* ------------------------------------------------ */
/* ----------------------------------------------------------------------------------------- */

void	free_data(t_data *data);
void	free_matrix(char **str);
char	*ft_strjon_free_arg1(char *s1, char const *s2);
char	*ft_strjon_free_arg2(char const *s1, char *s2);
char	*ft_strjon_free_both(char *s1, char *s2);


#endif