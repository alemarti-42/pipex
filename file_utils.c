/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:32 by alemarti          #+#    #+#             */
/*   Updated: 2023/07/12 11:55:23 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static int	open_infile(char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		put_error("no such file or directory: ", infile);
		exit(1);
	}
	if (access(infile, R_OK) == -1)
	{
		put_error("permission denied: ", infile);
		exit (1);
	}
	return (open(infile, O_RDONLY));
}

static int	open_outfile(char *outfile)
{
	int	res;

	res = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (access(outfile, W_OK) == -1)
	{
		put_error("permission denied: ", outfile);
		exit (1);
	}
	return (res);
}

int	open_files(t_environ *environ)
{
	environ->fd_in_out[0] = open_infile(environ->infile);
	if (environ->fd_in_out[0] < 0)
	{
		free_environ(environ);
		exit (1);
	}
	environ->fd_in_out[1] = open_outfile(environ->outfile);
	if (environ->fd_in_out[1] < 0)
	{
		close(environ->fd_in_out[0]);
		free_environ(environ);
		exit (1);
	}
	return (0);
}
