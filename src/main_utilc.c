#include "minishell.h"

int  for_space(char *ptr, char c, int i)
{
    if (ptr[i] == c)
    {
        i++;
        while(ptr[i] && ptr[i] != c)
            i++;
        if (ptr[i])
            i++;
    }
    return (i);
}

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