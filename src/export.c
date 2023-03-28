#include "minishell.h"
void buildin_export_line( t_pipe *pipe, int *i, char **str1)
{
    t_env *head;
    t_env *new; 

    head = pipe->head_env;
    while (head)
        {            
            if (ft_strcmp(str1[0], head->key) == 0)
            {
                head->val = str1[1];
                break;
            } 
            if (head->next == NULL && ther_are_equal(pipe->argv[*i])==1)
            {   
                new = new_t_env(str1[0],"\1");
                ft_t_env_add_back(&head, new);
                break;
            }                  
            if (head->next == NULL)
            {
                new = new_t_env(str1[0], str1[1]);
                ft_t_env_add_back(&head, new);
                break;
            }            
            head = head->next;
        }            
}
void builtin_export(t_data *data, t_pipe *pipe)
{  
    int i;
    char **str1;
    // t_env *head;
    // t_env *new; 

    i = 1;
    while (pipe->argv[i])
    { 
        // ther_are_equal(pipe->argv[i]);        
        str1 = ft_split(pipe->argv[i], '=');
       
        // head = pipe->head_env;
        if (ft_strcmp(hendl_export_var(str1[0]), "not a valid identifier") == 0)
        {
            printf(" %s not a valid identifier\n", pipe->argv[i]);
            return ;
        }  
        buildin_export_line( pipe, &i, str1);
        // while (head)
        // {            
        //     if (ft_strcmp(str1[0], head->key) == 0)
        //     {
        //         head->val = str1[1];
        //         break;
        //     } 
        //     if (head->next == NULL && ther_are_equal(pipe->argv[i])==1)
        //     {   
        //         new = new_t_env(str1[0],"\1");
        //         ft_t_env_add_back(&head, new);
        //         break;
        //     }                  
        //     if (head->next == NULL)
        //     {
        //         new = new_t_env(str1[0], str1[1]);
        //         ft_t_env_add_back(&head, new);
        //         break;
        //     }            
        //     head = head->next;
        // }            
        i++;
    }
}

char *hendl_export_var(char *str1)
{
    int k;

    k = 0;
    if (ft_isalpha(str1[k]) == 0 && str1[k] !=  '_')
    {
        return ("not a valid identifier");
    }
    k++;
    while (str1[k])
    {
        if (ft_isalpha(str1[k]) == 0 && str1[k] !=  '_'  && ft_isdigit(str1[k]) == 0 )
            return ("not a valid identifier");
        k++;
    }
    return (str1);
}

void buildin_export_all(t_data *data, t_pipe *pipe)
{
	// t_env *head;
    
    // head = data->head_env;
    // while (head)
    // {
    //     if (head->val == NULL)
    //         printf("declare -x %s\n", head->key);
    //     else  
    //         printf("declare -x %s=\"%s\"\n", head->key, head->val);
    //     if(head->next == NULL)
    //         return;
    //     head = head->next;
    // }

    t_env *head;
    
    head = pipe->head_env;
    while (head)
    {
        if (head->val == NULL)
            printf("declare -x %s\n", head->key);
        else  
            printf("declare -x %s=\"%s\"\n", head->key, head->val);
        if(head->next == NULL)
            return;
        head = head->next;
    }
}

void buildin_export_all_by_alphabet(t_data *data, t_pipe *pipe)
{
    // t_env *head;
    // int count;
    // int i;
    // count = 0;
    // i = 0;    
    // head = data->head_env;
    // while (head)
    // {        
    //     count++;
    //     head = head->next;
    // }    
    // while (i < count)
    // {      
    //     buildin_export_all_by_alphabet_inner(data); 
    //     i++;
    // }
    t_env *head;
    int count;
    int i;
    count = 0;
    i = 0;    
    head = pipe->head_env;
    while (head)
    {        
        count++;
        head = head->next;
    }    
    while (i < count)
    {      
        buildin_export_all_by_alphabet_inner(data,pipe); 
        i++;
    }
}

void buildin_export_all_by_alphabet_inner(t_data *data, t_pipe *pipe)
{
    // t_env   *head1;
    // char    *tmp;
    // char    *tmp_val;
   
    // head1 = data->head_env;   
    // while (head1->next)
    // {
    //     if (head1->key[0] > head1->next->key[0])
    //     {
    //         tmp_val = head1->val;
    //         tmp = head1->key;
    //         head1->val = head1->next->val;
    //         head1->key = head1->next->key;
    //         head1->next->val = tmp_val;
    //         head1->next->key = tmp;                
    //     }            
    //     head1 = head1->next;
    // }
     t_env   *head1;
    char    *tmp;
    char    *tmp_val;
   
    head1 = pipe->head_env;   
    while (head1->next)
    {
        if (head1->key[0] > head1->next->key[0])
        {
            tmp_val = head1->val;
            tmp = head1->key;
            head1->val = head1->next->val;
            head1->key = head1->next->key;
            head1->next->val = tmp_val;
            head1->next->key = tmp;                
        }            
        head1 = head1->next;
    }
}