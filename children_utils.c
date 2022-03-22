/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:18 by alemarti          #+#    #+#             */
/*   Updated: 2022/03/22 18:54:10 by alemarti         ###   ########.fr       */
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

void	reader_child(int *fd_pipe, char *cmd, t_environ *environ)
{
	char	**cmd_args;
	int		fd_in;

	fd_in = open (environ->infile, O_RDONLY);
	if (fd_in == -1)
	{
		ft_putstr_fd(environ->infile, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		//free_environ(environ);
		return ;
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	cmd_args = ft_split(cmd, ' ');
	if (exec_cmd(cmd_args, environ->paths, environ->envp) == -1)
	{
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	close(fd_in);
	close(fd_pipe[1]);
	free_split(cmd_args);
}

void	writer_child(int *fd_pipe, char *cmd, t_environ *environ)
{
	char	**cmd_args;
	int		fd_out;

	fd_out = open(environ->outfile, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	if (fd_out == -1)
	{
		ft_putstr_fd(environ->outfile, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		//free_environ(environ);
		return ;
	}
	dup2(fd_out, STDOUT_FILENO);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
	cmd_args = ft_split(cmd, ' ');
	if (exec_cmd(cmd_args, environ->paths, environ->envp) == -1)
	{
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	close(fd_out);
	close(fd_pipe[0]);
	free_split(cmd_args);
}
