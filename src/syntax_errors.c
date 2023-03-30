// Harcer !!!
// 2 hat || error !!!!
// "echo 14| ba" == 'echo 14| ba' => echo 14| ba: command not found
// echo   &&>  abc &x     >>    amalia   < 121 ??????
#include "minishell.h"

// void	check_error(char *ptr, int *i)
// {
// 	while (ptr && ((ptr[*i] >= 9 && ptr[*i] <= 13) || ptr[*i] == 32))
//         (*i)++;
// 	if (syntax_error(ptr) == 1);
// }

extern int exit_status;

int	syntax_error(char *ptr, int i)
{
    while (ptr && ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == 32))
        (i)++;
	if (!ptr[i])
	{
		ft_printf(2, "minishell: syntax error near unexpected token  `newline'\n");
		exit_status = 258;
		return (1);
	}
	if (ptr && (ptr[i] == '>' && ptr[i + 1] == '>') && ptr[i + 1] == '\0')
	{
		ft_printf(2, "minishell: syntax error near unexpected token `>>'\n");
		exit_status = 258;
		return (1);
	}
	if (ptr && (ptr[i] == '<' && ptr[i + 1] == '<') && ptr[i + 1] == '\0')
	{
		ft_printf(2, "minishell: syntax error near unexpected token `<<'\n");
		exit_status = 258;
		return (1);
	}
    if (ptr && (ptr[i] == '&' || ptr[i] == '|' || ptr[i] == ')' || ptr[i] == '(' || ptr[i] == ';'
        || ptr[i] == '>' || ptr[i] == '<') && ptr[i + 1] == '\0')
	{
        ft_printf(2, "minishell: syntax error near unexpected token `%c'\n", ptr[i]);
		exit_status = 258;
		return (1);
	}
	return (0);
}

int	metachar_error(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i] && ptr[i] != '\0')
	{
		while (ptr && (ptr[i] >= 9 && ptr[i] <= 13) && ptr[i] == 32)
			i++;
		while (!ft_strchr(METACHARACTER_ERROR, ptr[i]))
			i++;
		if ((ptr[i] && ptr[i] == '<' && ptr[i + 1] && ptr[i + 1] == '<') || (ptr[i] && ptr[i] == '>'
			&& ptr[i + 1] && ptr[i + 1] == '>'))
		{
			i += 2;
			if (syntax_error(ptr, i) == 1)
				return (1);
		}
		else if (ptr[i] && (ptr[i] == '>' || ptr[i] == '<'))
		{
			i++;
			if (syntax_error(ptr, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

//  command not found !!!
// syntax error near unexpected token `newline' ???
//  int	shlash_quote(char *ptr, int *i)
//  {
// 	while(ptr && ptr[*i])
// 	{		
// 	}
//  }