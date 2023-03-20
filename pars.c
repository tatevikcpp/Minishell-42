// echo "xg''fch'gcj'hv" | cat | "ls" -la | echo "hctfyuu | ijiuhouhuh |||||" | cat  
// ls -la "$PWD"$HOME $SFAFSF biuhbui $PWD'$HOME'  sdgsdg -> ls -la /Users/sokhacha/Users/sokhacha biuhbui /Users/sokhacha/Users/sokhacha

#include "minishell.h"
#include <fcntl.h> 

int init(t_data	*data, char **envp)
{
	int i;
	t_env *tmp_first_node;
	char **split_env;
	i = 0;
	(*data).head_env =  (t_env *)malloc(sizeof(t_env));
	tmp_first_node = data->head_env;
	while (envp[i])
	{
		split_env = ft_split(envp[i], '=');
		data->head_env->key = split_env[0];
		data->head_env->val = split_env[1];
		data->head_env->next = NULL;
		if (!envp[i + 1])
			break ;
		data->head_env->next = (t_env *)malloc(sizeof(t_env));
		data->head_env = data->head_env->next;
		i++;
	}
	data->head_env = tmp_first_node;
	return (0);
}

char *ft_get_value(char *key, t_data *ptr)
{
	t_env *head_env;

	head_env = ptr->head_env;
	while (head_env)
	{
		if (ft_strcmp(key, head_env->key) == 0)
			return (head_env->val);
		head_env = head_env->next;
	}
	return ("<<chka tenc ban>>");
}