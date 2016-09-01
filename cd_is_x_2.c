/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_is_x_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:33:06 by vsteffen          #+#    #+#             */
/*   Updated: 2016/09/01 17:33:13 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int			is_logical_goto_oldpwd(char **str)
{
	size_t	len;

	len = ft_str2len(str);
	if (len == 1)
		return (0);
	if (ft_strcmp("-", str[1]) == 0)
		return (1);
	if (len == 2)
		return (0);
	if (ft_strcmp("-L", str[1]) == 0 && ft_strcmp("-", str[2]) == 0)
		return (1);
	return (0);
}

int			is_physical_goto_oldpwd(char **str)
{
	size_t	len;

	len = ft_str2len(str);
	if (len == 1)
		return (0);
	if (ft_strcmp("-", str[1]) == 0)
		return (0);
	if (len == 2)
		return (0);
	if (ft_strcmp("-P", str[1]) == 0 && ft_strcmp("-", str[2]) == 0)
		return (1);
	return (0);
}

int			is_goto_home(char **command)
{
	size_t	len;

	len = ft_str2len(command);
	if (len == 1 || ft_strcmp(command[1], "~") == 0)
	{
		return (1);
	}
	else if (len == 2 && ft_strcmp(command[1], "-P") == 0)
	{
		return (1);
	}
	else if (len == 2 && ft_strcmp(command[1], "-L") == 0)
	{
		return (1);
	}
	return (0);
}
