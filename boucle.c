/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boucle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 15:30:12 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/25 15:55:51 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	prompt_quote(t_data *data)
{
	if (data->c == '\'')
		data->prompt = ft_strdup("quote> ");
	else if (data->c == '"')
		data->prompt = ft_strdup("dquote> ");
	else if (data->c == '`')
		data->prompt = ft_strdup("bquote> ");
	else if (data->c == '(')
		data->prompt = ft_strdup("subsh> ");
	else if (data->c == '[')
		data->prompt = ft_strdup("crochet> ");
	else if (data->c == '{')
		data->prompt = ft_strdup("cursh> ");
	else if (data->c == '<')
		data->prompt = ft_strdup("heredoc> ");
	ft_putstr(data->prompt);
	// printf("------- data->cmd = [%s]\n", data->cmd);
}

// data->history_en_cours = data->history_en_cours->prec;
// while(data->history_en_cours &&
// 	!ft_strnequ(data->history_en_cours->line, data->first, ft_strlen(data->first)))
// {
// 	printf("data->history en cours : %s\n", data->history_en_cours->line);
// 	data->history_en_cours = data->history_en_cours->prec;
// }
// if (!data->history_en_cours)
// 	return;

void	move_up_history(t_data *data, t_env *env)
{
	t_history	*temp;

	if (data->c == '\0' && data->history != NULL)
	{
		if (!data->first && data->first_search) // Si c'est la premiere fois qu'on appuie sur haut..
		{
			data->first_search = 0; // On change le fait que c'est la premiere fois
			if (!ft_strequ(data->cmd, "")) // Et si y a qqc dans notre commande, on s'en sert pour notre recherche future.
				data->first = ft_strdup(data->cmd);
		}
		if (!data->first && data->history_en_cours == NULL) //Si on est sorti de l'historique et qu'on a pas de recherche a faire, on part du depart (empeche de sauter le 1er element)
			data->history_en_cours = data->history;
		else if (data->first) // Sinon si on a une recherche a faire..
		{
			temp = data->history_en_cours; // On sauvegarde l'historique, au cas où on doive sortir plus tard
			if (!data->history_en_cours) // Si on est sorti, on part du premier
				data->history_en_cours = data->history;
			else if (data->history_en_cours->prec) // Sinon on part de celui d'avant(pour eviter de stagner sur le meme element)
				data->history_en_cours = data->history_en_cours->prec;
			while(!ft_strnequ(data->history_en_cours->line, data->first, ft_strlen(data->first)) //Tant que celui sur lequel on est ne correspond pas à notre recherche, et qu'il y en a un avant..
				&& data->history_en_cours->prec)
			{
				data->history_en_cours = data->history_en_cours->prec; // On recule dans notre historique
			}
			if (!ft_strnequ(data->history_en_cours->line, data->first, ft_strlen(data->first))) // Si on s'est pas arrete parce que le truc correspond, alors c'est qu'on s'est arrete parce qu'on etait a la fin. auquel cas, on fait comme si on avait rien fait.
			{
				data->history_en_cours = temp;
				return ;
			}
		}
		else
		{
			if (data->history_en_cours->prec)
				data->history_en_cours = data->history_en_cours->prec;
			else
				return ;
		}
		exec_tcap("dl");
		exec_tcap("cr");
		data->prompt = print_prompt(env, data);
		data->len_prompt = ft_strlen(data->prompt);
		ft_putstr((data->history_en_cours)->line);
		free(data->cmd);
		data->cmd = ft_strdup((data->history_en_cours)->line);
		data->real_len_cmd = ft_strlen(data->cmd);
		data->index = ft_strlen(data->cmd);
		data->curs_x = data->len_prompt + data->real_len_cmd + 1;
	}
	else
	{
		//On fait des trucs. (important).
	}
}

void	move_down_history(t_data *data, t_env *env)
{
	if (data->c == '\0')
	{
		if (data->history != NULL)
		{
			if (data->history_en_cours == NULL)
			{
				return ;
			}
			free(data->cmd);
			if (data->first)
			{
				data->history_en_cours = data->history_en_cours->next;
				while (data->history_en_cours &&
					!ft_strnequ(data->history_en_cours->line, data->first, ft_strlen(data->first)))
				{
					data->history_en_cours = data->history_en_cours->next;
				}
				if (!data->history_en_cours)
				{
					data->cmd = ft_strdup(data->first);
				}
				else
					data->cmd = ft_strdup(data->history_en_cours->line);
			}
			else if ((data->history_en_cours)->next)
			{
				data->history_en_cours = (data->history_en_cours)->next;
				data->cmd = ft_strdup(data->history_en_cours->line);
			}
			else
			{
				data->history_en_cours = NULL;
				// data->cmd = old_cmd;
				data->cmd = ft_strdup("");
				// return ;
			}
			exec_tcap("dl");
			exec_tcap("cr");
			data->prompt = print_prompt(env, data);
			data->len_prompt = ft_strlen(data->prompt);
			ft_putstr(data->cmd);
			data->real_len_cmd = ft_strlen(data->cmd);
			data->index = ft_strlen(data->cmd);
			data->curs_x = data->len_prompt + data->real_len_cmd + 1;
			data->curs_y = 0;
		}
	}
}

int	create_history(t_data *data, t_env **env)
{
	int i;

	i = 0;
	// printf("DATA->INDEX = %d\n", data->index);
	// printf("CURSEUR = [%d] /// INDEX  = [%d] /// DATA->WIN_X = [%d]\n", get_actual_cursor(data), data->index, data->win_x);
	ft_putstr("\n");
	if (data->c != '<' && (i = is_quote_end(data)) == 0 && (data->cmd[0] != '\0')) // Si la quote est terminée...
	{
		if (data->cmd_tmp[0] == '\0')
		{
			free(data->cmd_tmp);
		}
		else
		{
			if (data->quote_or_hd == 0) // Il ne faut pas jindre les heredocs à la commande.
				data->cmd = ft_strjoinaf1(data->cmd_tmp, data->cmd);
		}
		data->history = add_history_elem(data->history, create_history_elem(data->cmd)); // On rajoute la ligne dans l'historique.
		// printf("\nexecuting command now...\n");
		data->index = 0;
		invert_term();
		signal(SIGINT, SIG_IGN);
		exec_cmd(env, parse(data->cmd, data->heredocs, env, data), data); // On execute la commande.
		signal(SIGINT, sigint);
		invert_term();
		// printf("\nthe command has been executed\n");
		// display_heredoc(data->heredocs);
		data->c = '\0';
		data->end_hd = 0;
		free_heredoc(data->heredocs);
		data->heredocs_tmp = ft_strdup("");
		data->heredocs = NULL;
		free(data->key_here);
		data->key_here = NULL;
		data->cmd_tmp = ft_strdup("");
		data->quote_or_hd = 0;
		data->first_line_of_hd = 1;
		data->quote_old_index = 0;
	}
	else
	{
		if (i == -1)
		{
			//Parse error
			data->c = '\0'; // Pour tout reinitialiser par la suite.
			//FREE HEREDOCS
			free_heredoc(data->heredocs);
			data->heredocs = NULL;
			if (data->key_here)
				free(data->key_here);
			data->key_here = NULL;
			free(data->cmd);
		}
		else if (data->c == '<')
		{
			// printf("--------  data->cmd : %s\n", data->cmd);
			// printf("index = %d\n", data->index);
			if (is_key(data))
			{
				// printf("on ajoute [%s]\n", data->cmd + 1);
				// data->heredocs_tmp = ft_strjoinaf2(data->heredocs_tmp, data->cmd);
				free(data->cmd);
				// data->heredocs_tmp = ft_strjoinaf1(data->heredocs_tmp, "\n"); // Parce qu'il faut rajouter un \n à la toute fin
				data->heredocs = add_hc_elem(data->heredocs, create_hc_elem(data->heredocs_tmp));
				data->cmd = ft_strdup(data->cmd_tmp);
				free(data->cmd_tmp);
				data->cmd_tmp = ft_strdup("");
				data->index = data->old_index;
				free(data->key_here);
				data->key_here = NULL;
				// printf("[%s]\n", data->cmd + data->index);
				data->c = '\0';
				data->real_len_cmd = 0;
				data->quote_or_hd = 1;
				data->cmd = data->command_save;
				return (create_history(data, env));
				// create_history(data, env);
			}
			else
			{
				if (data->first_line_of_hd == 0)
				{
					data->heredocs_tmp = ft_strjoinaf1(data->heredocs_tmp, data->cmd);
					data->heredocs_tmp = ft_strjoinaf1(data->heredocs_tmp, "\n");
				}
				data->first_line_of_hd = 0;
				data->cmd = ft_strdup("");
			}
		}
		else if (data->c == '\0')
		{
			free(data->cmd_tmp);
			data->cmd_tmp = ft_strdup("");
			free(data->cmd);
		}
		else
		{
			data->cmd_tmp = ft_strjoinaf2(data->cmd_tmp, data->cmd);
			data->cmd_tmp = ft_strjoin(data->cmd_tmp, "\n");
			data->cmd = ft_strdup("");
		}
		data->index++;
	}
	free(data->prompt);
	data->prompt = print_prompt(*env, data);
	data->len_prompt = ft_strlen(data->prompt);
	data->real_len_cmd = 0;
	data->curs_x = data->len_prompt + 1;
	data->curs_y = -1;
	data->heredocs = NULL;
	if (data->first)
	{
		free(data->first);
		data->first = NULL;
	}
	data->first_search = 1;
	data->history_en_cours = NULL;
	data->cmd = ft_strdup("");
	data->index = 0;
	return (0);
}

void	boucle(t_env *env, t_data *data)
{
	char	buf[11];
	int		r;
	int		flag;
	char	*first;

	flag = 0;
	ft_bzero(buf, 11);
	while ((r = read(0, buf, 10)))
	{
		data->in_env_i = 0;
		if ((ft_isalpha(buf[0]) || (buf[0] >= 32 && buf[0] <= 64) || (buf[0] >= 123 && buf[0] <= 126) || (buf[0] >= 91 && buf[0] <= 96)) && buf[1] == '\0')
		{
			data->curs_x++;
			if (data->index == (int)data->real_len_cmd)
			{
				data->cmd = ft_strjoinaf1(data->cmd, buf);
				ft_putchar(buf[0]);
				data->index++;
			}
			else
			{
				insert_mode(data, buf[0]);
			}
			data->real_len_cmd++;
			data->first_search = 1;
			if (data->first)
			{
				free(data->first);
				data->first = NULL;
			}
		}
		else if (buf[0] == 4 && buf[1] == 0)
		// FREE DATA;
			exit(0);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0)
				move_left(data);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && buf[3] == 0)
				move_right(data);
		else if (buf[0] == 127 && buf[1] == 0)
		{
			if (data->index > 0)
			{
				delete_mode(data);
				data->first_search = 1;
				if (data->first)
				{
					free(data->first);
					data->first = NULL;
				}
				if (ft_strequ(data->cmd, ""))
					data->history_en_cours = NULL; // Voir si on veut le mettre
			}
		}
		else if (buf[0] == 10 && buf[1] == 0)
			create_history(data, &env);
		else if (buf[0] == 27	&&	buf[1] == 91	&&	buf[2] == 72 && buf[3] == 0)
			while(data->curs_x > data->len_prompt + 1 && data->curs_x > 0)
				move_left(data);
		else if (buf[0] == 27 && buf[1] == 91	&& buf[2] == 70 && buf[3] == 0)
			while(data->curs_x < data->len_prompt + 1 + (int)data->real_len_cmd)
				move_right(data);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && buf[3] == 0)
		{
			if (flag == 0)
			{
				flag++;
				first = ft_strdup(data->cmd);
			}
			move_up_history(data, env);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && buf[3] == 0)
			move_down_history(data, env);
		else if (buf[0] == -30 && buf[1] == -120 && buf[2] == -102 && buf[3] == 0)
		{
			char *pb = get_pb();
			data->curs_x += ft_strlen(pb);
			data->real_len_cmd += ft_strlen(pb);
			data->index += ft_strlen(pb);
			ft_putstr(pb);
			data->cmd = ft_strjoinaf12(data->cmd, pb);
		}
		else if (buf[0] == 12 && buf[1] == 0  &&buf[2] == 0)
		{
			exec_tcap("cl");
			ft_putstr("\e[38;5;208m");
			ft_putstr(data->prompt);
			ft_putstr("\e[39m");
			ft_putstr(data->cmd);
			int ind_act = ft_strlen(data->cmd);
			while (ind_act > data->index)
			{
				exec_tcap("le");
				ind_act--;
			}
		}
		else if (buf[0] == 27 && buf[1] == 0) // AFFICHE MESSAGE DE DEBUG 1
		{
			printf("data->index_min_win = %d /// data->index = %d\n", data->index_min_win, data->index);
		}
		else if (buf[0] == 29 && buf[1] == 0) // AFFICHE MESSAGE DE DEBUG 2
		{
//			printf("data->index_min_win = %d\n", data->index_min_win);
		}
		else
		{
				// ft_printf("%d - %d - %d - %d - %d - %d - cursor: x : %d, y : %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], data->curs_x, data->curs_y);
		}
		data->env = env;
		get_index_min_win(data);
		singleton_data(data, 1);
		ft_bzero(buf, 11);
	}
}
