/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 00:00:04 by jcamhi            #+#    #+#             */
/*   Updated: 2016/09/02 00:07:13 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*mallocp(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		exit(EXIT_FAILURE);
	return (ret);
}
