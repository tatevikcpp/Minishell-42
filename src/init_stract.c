#include "minishell.h"

int init(t_data	*data, char **envp)
{
	int		i;
	t_env	*tmp_first_node;
	char	**split_env;

	i = 0;
	(*data).head_env = (t_env *)malloc(sizeof(t_env));
	if (!(*data).head_env)
		return (0);
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
		if (!(*data).head_env)
			return (0);
		data->head_env = data->head_env->next;
		i++;
	}
	data->head_env = tmp_first_node;
	return (0);
}

void	struct_zeroed(t_data *data, char **env)
{
    init(data, env);
	data->pipe = NULL;
    data->env = env;
}

void send_env(t_data *data)
{
	t_env *head;
	char *str;
	char *str1 = ft_strdup(" ");

	head = data->head_env;
	while (head)
	{
		str = ft_strjoin(head->key, "=");
		str = ft_strjoin(str, head->val);
		str = ft_strjoin(str, " ");
		str1 = ft_strjoin(str1,str);
		head = head->next;
	}
	printf("str1 = %s\n", str1);
	data->env = ft_split(str1, ' ');
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
