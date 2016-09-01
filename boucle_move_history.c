/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boucle_move_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:33:06 by vsteffen          #+#    #+#             */
/*   Updated: 2016/09/01 17:33:13 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int	is_boucle_move_history(t_data *data, char buf[11], int *flag, t_env *env)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65
		&& buf[3] == 0 && !data->mode_copy)
	{
		if (flag == 0)
			flag++;
		move_up_history(data, env);
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66
		&& buf[3] == 0 && !data->mode_copy)
		move_down_history(data, env);
	else
		return (0);
	return (1);
}
