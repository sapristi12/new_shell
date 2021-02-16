#include "minishell.h"

void		apply_tmp(char *tmp, char c, int *in_quote)
{
	*tmp = c;
	*in_quote = *(in_quote) * -1;
}

static int 	is_first_condition(char tmp, char now, char bef, char bef2)
{
	if ((now == tmp && tmp == S_QUOTE))
		return (1);
	if (((bef != SLASH) || (bef2 == SLASH)) && (tmp == D_QUOTE && now == tmp))
		return (1);
	return (0);
}

static int 	is_second_condition(char now, char bef, int i)
{
	if (now == S_QUOTE)
		return (1);
	if (i > 0 && (now == D_QUOTE && bef != SLASH) || (i == 0 && now == D_QUOTE))
		return (1);
	return (0);
}

int 		is_even_quote(char *str)
{
	int in_quote;
	int i;
	char tmp;

	i = 0;
	in_quote = -1;
	while (str[i])
	{
		if (str[i] == SLASH && (str[i + 1] == SLASH || str[i + 1] == S_QUOTE || str[i + 1] == D_QUOTE))
			i++;
		if (in_quote == 1)
		{
			if (is_first_condition(tmp, str[i], str[i - 1], str[i - 2]))
				in_quote = -in_quote;
		}
		else if (in_quote == -1)
			if (str[i] == S_QUOTE || str[i] == D_QUOTE)
				if (is_second_condition(str[i], str[i - 1], i))
					apply_tmp(&tmp, str[i], &in_quote);
		i++;
	}
	if (in_quote == -1)
		return (1);
	return (0);
}