#include "sh21.h"

void	page_up(t_data *data)
{
	int	verif_new_line;
	int	tmp;
	int	old_index;

	if (data->index - data->win_x >= 0 && !(get_actual_cursor(data) == 0 \
		&& (int)ft_strlen(data->cmd) == data->index))
	{
		old_index = data->index;
		verif_new_line = data->win_x;
		while (verif_new_line > 0 && \
			data->cmd[data->index - verif_new_line] != '\n')
			verif_new_line--;
		if (verif_new_line == 0)
		{
			verif_new_line = data->win_x;
			while (verif_new_line > 0)
			{
				move_left_without_mod(data);
				verif_new_line--;
			}
			if (data->mode_copy)
			{
				tmp = data->index_max_copy;
				if (old_index != data->index_min_copy)
				{
					if (data->index_max_copy - data->win_x < data->index_min_copy)
					{
						verif_new_line = data->index_min_copy;
						data->index_min_copy = data->index_max_copy - data->win_x;
						data->index_max_copy = verif_new_line;
					}
					else
						data->index_max_copy -= data->win_x;
				}
				else
					data->index_min_copy -= data->win_x;
				verif_new_line = data->index;
				if (data->index > data->index_min_copy &&\
					data->index <= data->index_max_copy)
					exec_tcap("mr");
				while (data->cmd[data->index] && data->index <= tmp)
				{
					if (data->index == data->index_min_copy)
						exec_tcap("mr");
					ft_putchar(data->cmd[data->index]);
					if (data->index == data->index_max_copy)
						exec_tcap("me");
					data->index++;
				}
				exec_tcap("me");
				if (data->index > verif_new_line)
				{
					if (get_actual_cursor(data) == 0)
						move_index(data);
					else
						move_left_without_mod(data);
				}
				while (data->index > verif_new_line)
					move_left_without_mod(data);
			}
		}
		else
			exec_tcap("vb");
	}
}
