#include "minishell.h"

char	*ft_strjoin_ft(char const *s1, char c)
{
	char	*ptr;
	int		k;

	k = ft_strlen(s1);
	ptr = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (*s1 != '\0')
		*ptr++ = *s1++;
	if (c)
		*ptr++ = c;
	*ptr = '\0';
	return (ptr - k - 1);
}

t_redirect	*redirect_test(t_pipe *pipe)
{
	int 		i;
	t_pipe 		*top;
	t_redirect	*head;

	i = 0;
	top = pipe;
	head = NULL;
	top->s = NULL;
	while (top->content[i] != '\0')
	{
		while (top->content[i] <= 32)
			i++;
		if (is_redirect_in(top->content[i]) || is_redirect_out(top->content[i]))
			redirect_f_name_flag(top, &head, &i);
		else
		{
			redirect_to_command(top, &i); // sxal funkciayi anun
			i--;
		}
		if (top->content[i])
			i++;
	}
	return (head);
}

int	redirect_f_name_flag(t_pipe *top, t_redirect **head, int *i)
{
	int		x;
	int		start;
	char	*tmp;

	x = 1;
	if (is_redirect_in(top->content[*i]) || is_redirect_out(top->content[*i]))
	{
		if (is_append_in(top->content[*i], top->content[*i + 1]) || is_append_out(top->content[*i], top->content[*i + 1]))
			x++;
		tmp = ft_substr(top->content, *i, x);
		*i += x;
		while (is_space(top->content[*i]))
			(*i)++;
		start = *i;
		while (!ft_strchr(METACHARACTER, top->content[*i]))
			(*i)++;
		ft_t_redirect_add_back(head, new_t_redirect(ft_substr(top->content, start, *i - start), tmp));
		x = 1;
		*i -= 1;
	}
	else
		return(1);
	if (top->content[*i])
		(*i)++;
	return (0);
}

int	redirect_to_command(t_pipe *top, int *i)
{
	int k;
	char *tmp_comand;
	
	k = 0;
	if (top->content[*i] == '\'')
		redirect_to_quote(top,  i, '\'');
	else if (top->content[*i] == '"')
		{printf("else\n");redirect_to_quote(top,  i, '"');}
	k = (*i);
	if (top->content[*i] == '$' && (ft_isalpha(top->content[*i + 1]) || top->content[*i + 1] == '_'))
		top->s = ft_strjoin(top->s, hendl_dolar(top, top->content, i));
	while (top->content[*i] && !ft_strchr(METACHARACTER, top->content[*i]))
		(*i)++;
	tmp_comand = ft_substr(top->content, k, *i - k + 1);
	if (tmp_comand[0] != '$')
		top->s = ft_strjoin(top->s, ft_strtrim(tmp_comand, METACHARACTER));
	top->s = ft_strjoin_ft(top->s, 42);
			printf("top->s: %s\n", top->s);
	if (top->content[*i])
		(*i)++;
	return (1);
}

/* void	redirect_to_quote(t_pipe *top, int *i, char c)
{
	if (top->content && *i < ft_strlen(top->content))
	{
		int	k;

		k = *i;
		if (top->content[*i] == c && top->content[*i + 1] != '$')
		{
			// printf("araji\n");
			(*i)++;
			// printf("%c\n", top->content[*i]);
			// if (c == '"' && top->content[*i] == '$')
			// {
			// 	top->s = ft_strjoin(top->s, hendl_dolar(top, top->content, i));
			// 	printf("chakert\n");
			// }
			// printf("top->s: %s\n", top->s);
			// printf("111 %c\n", top->s[0]);
			// if (top->s[0] == '/')
			// {printf("off\n");
			// 	top->s = ft_strjoin(top->s, ft_strtrim(top->s, METACHARACTER));
			// printf("top->s_5: %s\n", top->s);}
			// if (c == '\'')
			// {
			top->s = ft_strjoin(top->s, split_quote(top->content, &(*i), c));
			// printf("top->s_8: %s\n", top->s);
			top->s = ft_strjoin_ft(top->s, 42);
		}
		(*i) = k + 1;
		printf("hello i: %d\n", *i);
		if (top->content[*i] == '$')
		{
			printf("Hello\n");
			printf("top->s before: %s\n", top->s);
			top->s = ft_strjoin(top->s, hendl_dolar(top, top->content, i));
			printf("top->s after: %s\n", top->s);
			printf("split_quote: top->s: %s\n, i: %d\n", top->s, *i);
		}
		(*i)++;
		// if (c == '"')
		// {
		// 	(*i)++;
		// 	if (top->content[*i] == '$')
		// 	{
		// 		top->s = ft_strjoin(top->s, split_quote(top->content, &(*i), c));
		// 		// top->s = ft_strjoin(top->s, hendl_dolar(top, top->content, i));
		// 		// top->s = ft_strjoin_ft(top->s, 42);
		// 	}
		// }
		// (*i)++;
	}
	// return (top->s);
} */

//******************************************


// void	redirect_to_quote(t_pipe *top, int *i, char c)
// {
// 	if (top->content && *i < ft_strlen(top->content))
// 	{
// 		if (top->content[*i] == c)
// 		{
// 			int k = *i;
// 			(*i)++;
// 			top->s = ft_strjoin(top->s, split_quote(top->content, &(*i), c));
// 			printf("top->s: %s\n", top->s);
// 			if (top->content[k] == '"' && top->content[k + 1] == '$')
// 			{
// 				top->s = ft_strjoin(top->s, hendl_dolar(top, top->s, i));
// 			}
// 			top->s = ft_strjoin_ft(top->s, 42);
// 		}
// 		(*i)++;
// 	}
// }



void	redirect_to_quote(t_pipe *top, int *i, char c)
{
	if (top->content && *i < ft_strlen(top->content))
	{
		if (top->content[*i] == c)
		{
			int k = *i;
			(*i)++;
			top->s = ft_strjoin(top->s, split_quote(top->content, &(*i), c));
			printf("top->s_quote: %s\n", top->s);
   printf("i = %d\n", *i);
			if (top->content[*i] == '"')
			{
				(*i)--;
				while (top->content[*i] != '"')
					(*i)--;
   	printf("i = %d\n", *i);
				printf("k\n");
				while (ft_strchr(METACHARACTER, top->content[k]))
					{printf("ok\n");(*i)++;}
				if (top->content[*i] && top->content[*i] == '$')
					{printf("111\n");top->s = ft_strjoin(top->s, hendl_dolar(top, top->s, i));}
			}
			top->s = ft_strjoin_ft(top->s, 42);
		}
		(*i)++;
	}
}

//******************************************

void	split_s__to_argv(/* t_data *data, */ t_pipe *pipe)
{
	pipe->argv = ft_split(pipe->s, 42);
}

char *hendl_dolar(t_pipe *pipe, char *str, int *i)
{
   	printf("str = %s\n", str);
	printf("str[i]: %c\n", str[*i]);
    int k;
    char *str1;
    char *val;

	(*i)++;
	k = *i;
	while((ft_isalpha(str[*i + 1]) || str[*i + 1]  == '_' || ft_isdigit(str[*i + 1])))
		(*i)++;
	str1 = ft_substr(str, k, *i - k + 1);
	printf("str_dolar: %s\n", str1);
	val = get_dolar_val(pipe, str1);
	printf("val = %s\n", val);
	(*i)--;
	return (val);
}

/* char *hendl_dolar(t_pipe *pipe, char *str, int *i)
{
	printf("i = %d\n", *i);
    int k;
    char *str1;
    char *val;

	(*i)++;
	k = *i;
	printf("str[i]: %c\n", str[*i]);
	while((ft_isalpha(str[*i + 1]) || str[*i + 1]  == '_' || ft_isdigit(str[*i + 1])))
		(*i)++;
	str1 = ft_substr(str, k, *i - k + 1);
	printf("str_dolar: %s\n", str1);
	val = get_dolar_val(pipe, str1);
	printf("val = %s\n", val);
	(*i)--;
	return (val);
} */

char *get_dolar_val(t_pipe *pipe, char *str1)
{
    t_env	*head;
    char	*str;

    head = pipe->head_env;
    while (head)
    {
        if (ft_strcmp(head->key , str1) == 0)
			str = head->val;
		// else
		// 	str = "";
        head = head->next;
    }
	// printf("%s\n", str);e
    return (str);
}


//--------------------------------------------
/* void	function_call(t_redirect **head, t_pipe *top, int *i, char c)
{
	int		x;
	int		start;
	char	*tmp;

	x = 1;

	if (top->content && *i < ft_strlen(top->content))
	{
		if (top->content[*i] == c && top->content[*i + 1] == c)
			x++;
		tmp = ft_substr(top->content, *i, x);
		*i += x;
		while (is_space(top->content[*i]))
			(*i)++;
		start = *i;
		while (!ft_strchr(METACHARACTER, top->content[*i]))
			(*i)++;
		ft_t_redirect_add_back(head, new_t_redirect(ft_substr(top->content, start, *i - start), tmp));
		x = 1;
		*i -= 1;
	}
	// return (top->s);
} */