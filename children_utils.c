/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:18 by alemarti          #+#    #+#             */
/*   Updated: 2023/07/12 12:05:21 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_environ(t_environ *environ)
{
	if (environ->paths)
		free_split(environ->paths);
	free(environ);
}

static int	close_fds(int fd_pipe[1024][2], int n_pipes)
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

static int	dup_fds(int fd_pipe[1024][2], t_environ *environ, int index)
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

static int	child_routine(int fd_pipe[1024][2], char *cmd, \
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
		exit (127);
	}
	if (exec_cmd(cmd_args, environ->paths, environ->envp) == -1)
	{
		free_split(cmd_args);
		free_environ(environ);
		exit (2);
	}
	exit (0);
}

int	spawn_children(t_environ *environ, char *argv[], \
	int fd_pipe[1024][2])
{
	int		pid;
	int		i;
	pid_t	child_pid;

	i = 0;
	while (i < environ->n_cmd)
	{
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (!pid)
			if (child_routine(fd_pipe, argv[i + 2], environ, i))
				exit(EXIT_FAILURE);
		i++;
	}
	i = -1;
	close_fds(fd_pipe, environ->n_cmd - 1);
	while (++i < environ->n_cmd)
	{
		child_pid = waitpid(-1, NULL, 0);
		if (child_pid == -1)
			exit(EXIT_FAILURE);
	}
	return (0);
}
