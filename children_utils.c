/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:18 by alemarti          #+#    #+#             */
/*   Updated: 2023/07/13 15:11:57 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	close_fds(int fd_pipe[1024][2], t_environ *environ, int n_pipes)
{
	int	i;

	i = 0;
	close(environ->fd_in_out[0]);
	close(environ->fd_in_out[1]);
	while (i < n_pipes)
	{
		close(fd_pipe[i][0]);
		close(fd_pipe[i][1]);
		i++;
	}
	return (0);
}

static int	dup_fds(int fd_pipe[1024][2], t_environ *environ, int index)
{	
	if (index == 0)
	{
		environ->fd_in_out[0] = open_infile(environ->infile);
		if (environ->fd_in_out[0] <= 0)
			exit (1);
		dup2(environ->fd_in_out[0], STDIN_FILENO);
	}
	else
	{
		dup2(fd_pipe[index - 1][0], STDIN_FILENO);
	}
	if (index == environ->n_cmd - 1)
	{
		environ->fd_in_out[1] = open_outfile(environ->outfile);
		if (environ->fd_in_out[1] <= 0)
			exit (1);
		dup2(environ->fd_in_out[1], STDOUT_FILENO);
	}
	else
	{
		dup2(fd_pipe[index][1], STDOUT_FILENO);
	}
	close (environ->fd_in_out[0]);
	close (environ->fd_in_out[1]);
	return (0);
}

int	child_routine( int fd_pipe[1024][2], char *cmd, \
		t_environ *environ, int index)
{
	int		i;
	char	**cmd_args;
	int		status;

	i = 0;
	status = 0;
	dup_fds(fd_pipe, environ, index);
	if (status)
		exit (status);
	close_fds(fd_pipe, environ, environ->n_cmd - 1);
	cmd_args = ft_split(cmd, ' ');
	if (*cmd_args == 0)
	{
		put_error("command not found:", " ");
		exit (127);
	}
	if (exec_cmd(cmd_args, environ->paths, environ->envp) == -1)
	{
		free_split(cmd_args);
		free_environ(environ);
		exit (2);
	}
	return (0);
}

static int	wait_children(int i, int last_pid)
{
	int	pid;
	int	status;
	int	exit_status;

	exit_status = 0;
	while (--i >= 0)
	{
		pid = wait(&status);
		if (pid == -1)
			return (EXIT_FAILURE);
		if (pid == last_pid)
			exit_status = status;
	}
	return (WEXITSTATUS(exit_status));
}

int	spawn_children(t_environ *environ, char *argv[], \
	int fd_pipe[1024][2])
{
	int		pid;
	int		i;
	int		status;
	int		last_pid;
	int		exit_status;

	i = 0;
	status = 0;
	exit_status = 0;
	while (i < environ->n_cmd)
	{
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (!pid)
			if (child_routine(fd_pipe, argv[i + 2], environ, i))
				exit(EXIT_FAILURE);
		last_pid = pid;
		i++;
	}
	close_fds(fd_pipe, environ, environ->n_cmd - 1);
	return (wait_children(i, last_pid));
}
