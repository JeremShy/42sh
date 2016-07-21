/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 19:30:33 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/24 15:25:44 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	free_heredoc(t_hc *list)
{
	t_hc *tmp;

	while(list)
	{
		tmp = list->next;
		free(list->content - 1);	//	Car on a fait un +1 au moment de la creation
															//	afin de sauter le \n du debut.
		free(list);
		list = tmp;
	}
}

void	display_heredoc(t_hc *elem)
{
	int	i;

	i = 0;
	printf("--- LIST HEREDOC ---\n");
	while (elem)
	{
		printf("N° %d --> [%s]\n", i, elem->content);
		i++;
		elem = elem->next;
	}
	printf("--- END HEREDOC  ---\n");
}

t_hc *create_hc_elem (char *content)
{
	t_hc	*elem;

	elem = malloc(sizeof(t_hc));
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

t_hc 	*add_hc_elem(t_hc *list, t_hc *elem)
{
	t_hc *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
  		list = list->next;
	list->next = elem;
	return (tmp);
}