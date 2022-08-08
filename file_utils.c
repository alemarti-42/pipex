/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:32 by alemarti          #+#    #+#             */
/*   Updated: 2022/08/08 16:57:23 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	open_files(int *fd_in_out, t_environ *environ)
{
	fd_in_out[0] = open_infile(environ->infile);
	fd_in_out[1] = open_outfile(environ->outfile);
	if (fd_in_out[0] < 0)
	{
		free_environ(environ);
		return (-1);
	}
	if (fd_in_out[1] < 0)
	{
		free_environ(environ);
		return (-1);
	}
	return (0);
}

int	open_infile(char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		put_error("pipex: no such file or directory: ", infile);
		return (-1);
	}
	return (open(infile, O_RDONLY));
}

int	open_outfile(char *outfile)
{
	int	res;

	res = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (access(outfile, W_OK) == -1)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putstr_fd(outfile, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (res);
}
