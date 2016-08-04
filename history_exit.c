/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 15:27:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/08/04 14:42:45 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	history_exit(t_data *data)
{
	char			*path;
	int				fd;
	t_history	*history;

	if (get_history_path(data, &path) == 1)
		return ;
	fd = open(path, O_WRONLY | O_APPEND);
	free(path);
	if (fd == -1)
		return ;
	if ((history = data->history) == NULL)
		return ;
	while (history->prec && history->prec->get_from_file == 0)
		history = history->prec;
	while (history)
	{
		path = ft_itoa_base(history->time, 10);
		path = ft_strjoinaf1(path, ";");
		path = ft_strjoinaf1(path, history->line);
		path = ft_strjoinaf1(path, "\n");
		write(fd, path, ft_strlen(path));
		free(path);
		history = history->next;
	}
	close(fd);
}
