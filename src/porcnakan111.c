#include "minishell.h"

// void	redirect_to_quote(char *str, int *i, char c)
// {
//     char *ptr = NULL;
// 	if (str && *i < ft_strlen(str))
// 	{
// 		if (str[*i] == c)
// 		{
// 			(*i)++;
// 			ptr = ft_strjoin(ptr, split_quote(str, &(*i), c));
// 		}
// 		(*i)++;
// 	}
// }

void hendl_dolar(t_data *data, char *str)
{
    int i;
    int j;    
    char *str1;
    char *val;

    i = 0;
    j = 0;
    while (str[j])
    {
        if (str[j] == '$' && (ft_isalpha(str[j+1]) || str[j+1] == '_'))
        {
            j++;
            i = j;
            while((ft_isalpha(str[j]) || str[j] == '_' || ft_isdigit(str[j])))
                j++;
            str1 = ft_substr(str,i,j - i);
            data-> len_key_sum += ft_strlen(str1);
            val = get_dolar_val(data, str1);
            j--;
        }
        j++;
    }
}

char *get_dolar_val(t_data *data, char *str1)
{
    t_env *head;
    char *str;
    int flag;
    head = data->head_env;

    flag = 0;
    str = NULL;
    while (head)    
    {
        if (ft_strcmp(head->key , str1) == 0)
        {
            str = head->val;
            data->len_val_sum += ft_strlen(str);
            flag = 1;
        }
        head = head->next;
    }
    if (flag == 0)
    {
        str = str1;
        data->len_val_sum += ft_strlen(str1);
    }

    return (str);
}

void func(char *test, int j)
{
    char    *ptr;
    char    *str_line;
    // char    *str1;

    ptr = NULL;
    str_line = ptr;

    ptr = ft_substr(test, j, 1);
    str_line = ft_strjoin(str_line,ptr);
}

// echo 'as$PW"D' "$PWD gvy'''''vgb"

char *hendl_doloar_comand(t_data *data, char *test)
{
    int     i;
    int     j;
    int     is_in_single;;
    int     is_in_double;;;
    char    *ptr = NULL;
    char    *str1;
    char    *str_line;

    i = 0;
    j = 0;
    is_in_single = 0;
    is_in_double = 0;
    str_line = ptr;
    while(test[j])
    {
        if (test[j] == '\'' && !is_in_double)
        {
            if (is_in_single == 1)
                is_in_single = 0;
            else
                is_in_single = 1;
        }
        if (test[j] == '"' && !is_in_single)
        {
            if (is_in_double == 1)
                is_in_double = 0;
            else
                is_in_double = 1; // = 1
        }
        if ((test[j] == '"' && !is_in_single) || (test[j] == '\'' && !is_in_double))
            j++;
        if (!is_in_single && test[j] == '$' && (ft_isalpha(test[j+1]) || test[j+1] == '_'))
        {
            j++;
            i = j;
            while((ft_isalpha(test[j]) || test[j] == '_' || ft_isdigit(test[j])))
                j++;
            str1 = ft_substr(test,i,j - i);
            ptr = get_dolar_val(data, str1);
			if (ptr)
                str_line = ft_strjoin(str_line,ptr);
            j--;
        }
        else if (!(test[j] == '\'' && is_in_single) && !(test[j] == '"' && is_in_double))
        {
            ptr = ft_substr(test, j, 1);
            str_line = ft_strjoin(str_line, ptr);
        }
        if (test[j] && !(test[j] == '\'' && is_in_single) && !(test[j] == '"' && is_in_double))// else?
            j++;
	}
    return (str_line);
}

char *function(t_data *data, char *test)
{
    hendl_dolar(data, test);
    // hendl_doloar_comand(data, test);
    // printf("comand : %s\n", hendl_doloar_comand(data, test));
    return (hendl_doloar_comand(data, test));
}


//leaks     'dsgsdgsd$PWD g'
//  int main(int ac,  char **av,  char **env)//kaskaceli e Tatevi hamar u shaaat 
// {
// 	(void)(av+ac);
// 	// int j;
//     int i;
// 	t_data	data;
    
// 	// char *ptr = ft_strdup(" ");
//     // char *str1;
//     // int len;
//     // int p;
// 	// j = 0;
//     i = 0;
// 	 struct_zeroed(&data, env);
// 	// init(&data, env);
// 	// printf("%s\n", ft_get_value("PATH", &data));
// 	// char	*test = "la -la \"$PWD\"$HOME $SFAFSF biuhbui $PWD  '$HOME'  sdgsdg";
//     char *test;
//     while (1)
//     {
// 		test = readline("minishell-$ ");
//         add_history(test);
// 	// char	*test = "la -la  'kshja' \"$OKK0M\" \"$PWD\"$HOME $SFAFSF biuhbui $PWD barev okokok '$HOME'  sdgsdg";
//     // hendl_dolar(&data, test);
//     // ptr = hendl_doloar_comand(&data, test);
//     // printf("ptr: %s\n", ptr - 87);
//     // printf("comand : %s\n", hendl_doloar_comand(&data, test));
//     function(&data, test);

//     }

//     // ptr = test;
//     // while (*test != '\0')
//     //     test++;
//     // printf("1111 = %s\n", ptr);
//     // printf("test: %s\n", test - 87);
// 	return (0);
// }