/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JeremShy <JeremShy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:53:03 by JeremShy          #+#    #+#             */
/*   Updated: 2016/06/27 18:44:07 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

static char	*print_error_no_path(char *tmp)
{
	ft_putstr_fd("Error : The value of the environment variable PATH", 2);
	ft_putstr_fd(" is not valid or inexistant.\n", 2);
	free(tmp);
	return (NULL);
}

static char	*while_exec(char **split, char *scmd)
{
	int			i;
	DIR			*directory;
	t_dirent	*truc;

	i = 0;
	while (split[i])
	{
		directory = opendir(split[i]);
		while (directory && (truc = readdir(directory)))
			if (ft_strequ(truc->d_name, scmd) &&
					!ft_strequ(truc->d_name, ".") &&
					!ft_strequ(truc->d_name, ".."))
			{
				closedir(directory);
				return (ft_strjoinaf1(ft_strjoin(split[i], "/"), scmd));
			}
		if (directory)
			closedir(directory);
		i++;
	}
	ft_putstr_fd("21sh: command not found: ", 2);
	ft_putstr_fd(scmd, 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

char		*find_exec(char *scmd, t_env *list)
{
	char	**split;
	char	*tmp;
	char	*ret;

	if (ft_strchr(scmd, '/'))
		return (ft_strdup(scmd));
	tmp = find_arg(list, "PATH");
	if (ft_strequ(tmp, ""))
		return (print_error_no_path(tmp));
	split = ft_strsplit(tmp, ':');
	free(tmp);
	ret = while_exec(split, scmd);
	free_char_tab(split);
	return (ret);
}

int			exec_file(t_cmd *cmd, t_env *list)
{
	char	*file;
	char	**env;
	pid_t	process;
	int		retour;

	file = find_exec(cmd->av[0], list);
	if (!file)
		return (0);
	if (access(file, X_OK) == -1)
	{
		ft_putstr_fd("21sh: permission denied: ", 2);
		ft_putstr_fd(cmd->av[0], 2);
		ft_putchar_fd('\n', 2);
		free(file);
		return (0);
	}
	env = make_env_char(list);
	process = fork();
	if (process != 0)
		wait(NULL);
	else
	{
		dup2(cmd->fd_in->fd, 0);
		dup2(cmd->fd_out->fd, 1);
		dup2(cmd->fd_err->fd, 2);
		retour = execve(file, cmd->av, env);
		if (retour == -1)
		{
			ft_putstr_fd("21sh: exec format error: ", 2);
			ft_putstr_fd(cmd->av[0], 2);
			ft_putchar_fd('\n', 2);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	free_char_tab(env);
	return (1);
	}
