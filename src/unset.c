#include "minishell.h"

void ft_get_remove_val(t_data *data,int (*ft_strcmp)(), char *str)
{
    t_env	*head;
    char *line1;
    char *line;
    int len;

    line1 = NULL;
    len = ft_strlen(str);
    line = malloc(sizeof(char) * (len + 1));
    line = ft_substr(str,1,len-1);
    head = data->head_env;
    while (head)
    {               
        if (ft_strcmp(line, head->key) == 0)
        {
            line1= head->val;                   
            break;
        }                
        head = head->next;
    }     
    remove_if_inner(data, ft_strcmp, line1); 
}

void ft_list_remove_if(t_data *data,int (*ft_strcmp)(),t_pipe *pipe)
{    
    char **str1;
    int i;
     
    i = 1;   
    while (pipe->argv[i])
    {
        str1 = ft_split(pipe->argv[i], '=');
        if (str1[0][0] == '$')
        {
            // printf("pipe->argv[i]---%s\n",pipe->argv[i]);
            // printf("str1[0]%s\n", str1[0]);
            // printf("str1[1]%s\n", str1[1]);
            // printf("HI\n");
            ft_get_remove_val(data,ft_strcmp,str1[0]);            
        }
        else
        {
            // printf("pipe->argv[i]---%s\n",pipe->argv[i]);
            // printf("str1[0]%s\n", str1[0]);
            // printf("str1[1]%s\n", str1[1]);
            remove_else_inner(data, ft_strcmp, str1);       
        }
        i++;
    }
}

void remove_else_inner(t_data *data,int (*ft_strcmp)(), char **str1)
{
    t_env   *head;
    t_env   *new;
    t_env   *tmp;

    head = data->head_env;
    if (head == NULL)
        return ;
    if (head && ft_strcmp(head->key, str1[0])==0)
    {
        new = head;
        head= head->next;
        free(new);
    }
    new = head;
    while (new && new->next)
    {
        if (ft_strcmp(new->next->key,str1[0]) == 0)
        {
            tmp = new->next;
            new->next = tmp->next;
                free(tmp);	
        }
        new = new->next;
    }
}

void remove_if_inner(t_data *data,int (*ft_strcmp)(), char *str)
{
    t_env	*head;
    t_env	*new;
    t_env	*tmp;

    head = data->head_env;
    if (head == NULL)
        return ;
    if (head && ft_strcmp(head->key, str)==0)
    {
        new = head;
        head= head->next;
        free(new);
    }
    new = head;
    while (new && new->next)
    {
        if (ft_strcmp(new->next->key, str)==0)
        {
            tmp = new->next;
            new->next = tmp->next;
                free(tmp);	
        }
        new = new->next;
    }
}





