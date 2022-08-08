/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:18 by alemarti          #+#    #+#             */
/*   Updated: 2022/08/08 12:43:41 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_environ	*init_environ(char *infile, char *outfile, char *envp[])
{
	t_environ	*res;

	res = (t_environ *)malloc(sizeof(t_environ));
	res->envp = envp;
	res->paths = get_path(envp);
	res->infile = infile;
	res->outfile = outfile;
	return (res);
}

void	free_environ(t_environ *environ)
{
	free_split(environ->paths);
	free(environ);
}

void	reader_child(int *fd_pipe, char *cmd, t_environ *environ, int fd_in)
{
	char	**cmd_args;

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	cmd_args = ft_split(cmd, ' ');
	if (exec_cmd(cmd_args, environ->paths, environ->envp) == -1)
	{
		free_split(cmd_args);
		free_environ(environ);
		exit (-1);
	}
	close(fd_in);
	close(fd_pipe[1]);
	free_split(cmd_args);
}

void	writer_child(int *fd_pipe, char *cmd, t_environ *environ, int fd_out)
{
	char	**cmd_args;

	dup2(fd_out, STDOUT_FILENO);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
	cmd_args = ft_split(cmd, ' ');
	if (exec_cmd(cmd_args, environ->paths, environ->envp) == -1)
	{
		free_split(cmd_args);
		free_environ(environ);
		exit(-1);
	}
	close(fd_out);
	close(fd_pipe[0]);
	free_split(cmd_args);
}
