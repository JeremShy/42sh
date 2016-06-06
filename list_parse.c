/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:12:36 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/06 23:02:20 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		def_sep(char *str)
{
	if (ft_strnstr(str, ">>", 2))
		return (DCHEV_DROITE);
	else if (ft_strnstr(str, "<<", 2))
		return (DCHEV_GAUCHE);
	else if (ft_strnstr(str, "&&", 2))
		return (ETET);
	else if (str[0] == '|')
		return (str[0]);
	else if (str[0] == '>')
		return (str[0]);
	else if (str[0] == '<')
		return (str[0]);
	else if (str[0] == ';')
		return(str[0]);
	return (0);
}

void	join_inside_quote(size_t *i, char *str)
{
	size_t	tmp;
	char	open;

	open = str[*i];
	while (is_quote_close(open, str[*i + 1]) == 0)
	{
		str[*i] = str[*i + 1];
		(*i)++;
	}
	tmp = *i;
	while (str[tmp + 2])
	{
		str[tmp] = str[tmp + 2];
		tmp++;
	}
	str[tmp] = '\0';
	if (*i == 0)
		return ;
	(*i)--;
}

char	**split_cmd(char *str, int count, int *sep)
{
	char		**av;
	size_t		i;
	size_t		n_av;
	size_t		tmp;
	int			quote;
	size_t 		start;

	printf("count : %d\n", count);
	av = (char**)malloc((count + 1) * sizeof(char*));
	if (!av)
		exit(0);
	printf("on recoit : %s\n", str);
	i = 0;
	n_av = 0;
	while (str[i])
	{
		while (ft_isspace2(str[i]))
			i++;
		if (str[i] != '\0')
		{
			tmp = i;
			start = i;
			while (!ft_isspace2(str[i]) && str[i] != '\0')
			{
				if (is_special(str + i) == 1)
				{
					av[n_av] = ft_strsub(str, start, i - start);
					n_av++;
					*sep = def_sep(str + i);
					av[count] = NULL;
					return (av);
				}
				if (is_quote_open(str[i]))
				{
					printf("avant : %zu\n", i);
					join_inside_quote(&i, str);
					printf("apres : %zu /// chaine : =%s=\n", i, str);
					if (i == tmp)
						i--;
//					if (isspace(str[i + 1]) || str[i + 1] == '\0')
					quote = 1;
				}
				i++;
			}
			if (ft_isspace2(str[i]) || str[i] == '\0')
 			{
				av[n_av] = ft_strsub(str, start, i - start);
				n_av++;
			}
		}
	}
	av[count] = NULL;
	*sep = 0;
	return (av);
}

void		print_list(t_cmd *lst)
{
	size_t	i;
	char		**av;
	size_t	j;

	i = 0;
	while (lst != NULL)
	{
		printf("list number : %zu\n", i);
		av = lst->av;
		j = 0;
		while (av[j])
		{
			printf("av[%zu] : #%s#\n", j, av[j]);
			j++;
		}
		printf("sep : %c\n", lst->caractere);
		i++;
		lst = lst->next;
		printf("\n");
	}
}

t_cmd	*create_cmd_elem(char *str, int count)
{
	t_cmd		*elem;
	int			sep;

	sep = 0;
	elem = (t_cmd*)malloc(sizeof(t_cmd));
	printf("str: %s\n", str);
	elem->av = split_cmd(str, count, &sep);
	elem->next = NULL;
	printf("sep : %c\n", (char)sep);
	elem->caractere = sep;
	free(str);
	return (elem);
}

t_cmd *add_cmd_elem(t_cmd *list, t_cmd *elem)
{
	t_cmd *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	return (tmp);
}