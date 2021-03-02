#include "minishell.h"

char	*my_strdup(char *str, int size)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpyt(char *str, char c, int in_quote, char tmp)
{
	char	*dest;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i] && ((str[i] != c && in_quote == -1) || in_quote == 1))
	{
		if (in_quote == 1 && str[i] == tmp && i != 0)
			in_quote = -in_quote;
		else if (in_quote == -1 && (str[i] == D_QUOTE || str[i] == S_QUOTE))
		{
			in_quote = -in_quote;
			tmp = str[i];
		}
		if (str[i] == SLASH && str[i + 1])
			i++;
		i++;
	}
	size += i;
	dest = my_strdup(str, size);
	// dest = (char *)malloc(sizeof(char) * (size + 1));
	// if (!dest)
	// 	return (NULL);
	// i = 0;
	// while (i < size)
	// {
	// 	dest[i] = str[i];
	//     i++;
	// }
	// dest[i] = '\0';
	// printf("dest = |%s|\n", dest);
	return (dest);
}

void	check_quote(char **str, char c, int *in_quote, char *tmp)
{
	while (**str && ((**str != c && *in_quote == -1) || *in_quote == 1))
	{
		if (**str == SLASH && *(*str + 1))
			(*str)++;
		(*str)++;
		if (*in_quote == 1 && **str == *tmp)
			*in_quote = -(*in_quote);
		else if (*in_quote == -1 && (**str == D_QUOTE || **str == S_QUOTE))
		{
			*in_quote = -(*in_quote);
			*tmp = **str;
		}
	}
}

int		cw(char *str, char c)
{
	int		i;
	int		in_quote;
	char	tmp;

	in_quote = -1;
	i = 0;
	while (*str)
	{
		while (*str && (*str == c && in_quote == -1))
			str++;
		if (in_quote == -1 && (*str == D_QUOTE || *str == S_QUOTE))
		{
			in_quote = -in_quote;
			tmp = *str;
		}
		if (*str && (*str != c || in_quote == 1))
		{
			i++;
			check_quote(&str, c, &in_quote, &tmp);
			// while (*str && ((*str != c && in_quote == -1) || in_quote == 1))
			// {
			// 	if (*str == SLASH && *(str + 1))
			// 		str++;
			// 	str++;
			// 	if (in_quote == 1 && *str == tmp)
			// 		in_quote = -in_quote;
			// 	else if (in_quote == -1 && (*str == D_QUOTE || *str == S_QUOTE))
			// 	{
			//     	in_quote = -in_quote;
			//     	tmp = *str;
			// 	}
			// }
		}
	}
	return (i);
}

char	**new_split(char *str, char c)
{
	char	**dest;
	int		i;
	int		in_quote;
	char	tmp;

	in_quote = -1;
	i = 0;
	if (!(dest = (char **)malloc(sizeof(char *) * (cw(str, c) + 1))))
		return (NULL);
	while (*str)
	{
		while (*str && (*str == c && in_quote == -1))
			str++;
		if (in_quote == -1 && (*str == D_QUOTE || *str == S_QUOTE))
		{
			in_quote = -in_quote;
			tmp = *str;
		}
		if (*str && (*str != c || in_quote == 1))
		{
			dest[i] = ft_strcpyt(str, c, in_quote, tmp);
			i++;
			check_quote(&str, c, &in_quote, &tmp);
			// while (*str && ((*str != c && in_quote == -1) || in_quote == 1))
			// {
			// 	if (*str == SLASH && *(str + 1))
			// 			str++;
			// 	str++;
			// 	if (in_quote == 1 && *str == tmp)
			// 		in_quote = -in_quote;
			// 	else if (in_quote == -1 && (*str == D_QUOTE || *str == S_QUOTE))
			// 	{
			// 		in_quote = -in_quote;
			// 		tmp = *str;
			// 	}
			// }
		}
	}
	dest[i] = NULL;
	return (dest);
}
