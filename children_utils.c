/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:18 by alemarti          #+#    #+#             */
/*   Updated: 2023/07/11 14:15:22 by alemarti         ###   ########.fr       */
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
	res->fd_in_out[0] = -1;
	res->fd_in_out[1] = -1;
	return (res);
}

int	spawn_children(t_environ *environ, char *argv[], \
	int fd_pipe[1024][2])
{
	int		pid;
	int		i;
	int		status;
	pid_t	child_pid;

	i = 0;
	while (i < environ->n_cmd)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (!pid)
			if (child_routine(fd_pipe, argv[i + 2], environ, i))
				return (-1);
		i++;
	}
	i = -1;
	close_fds(fd_pipe, environ->n_cmd - 1);
	while (++i < environ->n_cmd)
	{
		child_pid = waitpid(-1, &status, 0);
		if (child_pid == -1)
			exit(EXIT_FAILURE);
	}
	return (0);
}

int	close_fds(int fd_pipe[1024][2], int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		close(fd_pipe[i][0]);
		close(fd_pipe[i][1]);
		i++;
	}
	return (0);
}

int	dup_fds(int fd_pipe[1024][2], t_environ *environ, int index)
{	
	if (index == 0)
	{
		dup2(environ->fd_in_out[0], STDIN_FILENO);
	}
	else
	{
		close(fd_pipe[index - 1][1]);
		dup2(fd_pipe[index - 1][0], STDIN_FILENO);
	}
	if (index == environ->n_cmd - 1)
	{
		dup2(environ->fd_in_out[1], STDOUT_FILENO);
	}
	else
	{
		close(fd_pipe[index][0]);
		dup2(fd_pipe[index][1], STDOUT_FILENO);
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
	close_fds(fd_pipe, environ->n_cmd - 1);
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
	exit (0);
}
