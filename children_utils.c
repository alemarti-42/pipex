/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:18 by alemarti          #+#    #+#             */
/*   Updated: 2023/06/20 12:39:01 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_environ	*init_environ(char *infile, char *outfile, char *envp[])
{
	t_environ	*res;

	res = (t_environ *)malloc(sizeof(t_environ));
	if (!res)
		return (NULL);
	res->envp = envp;
	res->paths = get_path(envp);
	res->infile = infile;
	res->outfile = outfile;
	res->fd_in_out = (int *)malloc(2);
	if (!res->fd_in_out)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

int	spawn_children(t_environ *environ, char *argv[], \
	int fd_pipe[1024][2])
{
	int	pid;
	int	i;

	i = -1;
	while (++i < environ->n_cmd)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("Critical fork error. Exiting...\n", 2);
			return (-1);
		}
		if (!pid)
		{
			if (child_routine(fd_pipe, argv[i + 2], environ, i))
			{
				ft_putstr_fd("Child routine error\n", 2);
				return (-1);
			}
		}
	}
	waitpid(-1, NULL, 0);
	return (0);
}

int	dup_fds(int fd_pipe[1024][2], t_environ *environ, int index)
{	
	if (index == 0)
		dup2(environ->fd_in_out[0], STDIN_FILENO);
	else
	{
		dup2(fd_pipe[index - 1][0], STDIN_FILENO);
		close(fd_pipe[index - 1][1]);
	}
	if (index == environ->n_cmd - 1)
		dup2(environ->fd_in_out[1], STDOUT_FILENO);
	else
	{
		dup2(fd_pipe[index][1], STDOUT_FILENO);
		close(fd_pipe[index][0]);
	}
	return (0);
}

int	close_fds(int fd_pipe[1024][2], t_environ *environ, int index)
{
	if (index == 0)
		close(environ->fd_in_out[0]);
	if (index == environ->n_cmd - 1)
		close(environ->fd_in_out[1]);
	if (index != environ->n_cmd - 1)
	{
		close(fd_pipe[1][index - 1]);
	}
	if (index != 0)
	{
		close(fd_pipe[0][index - 2]);
	}
	return (0);
}

int	child_routine(int fd_pipe[1024][2], char *cmd, \
		t_environ *environ, int index)
{
	int		i;
	char	**cmd_args;

	i = 0;
	dup_fds(fd_pipe, environ, index);
	cmd_args = ft_split(cmd, ' ');
	if (*cmd_args == 0)
	{
		put_error("command not found:", " ");
		return (0);
	}
	if (exec_cmd(cmd_args, environ->paths, environ->envp) == -1)
	{
		free_split(cmd_args);
		free_environ(environ);
		exit (-1);
	}
	free_split(cmd_args);
	close_fds(fd_pipe, environ, index);
	return (0);
}
