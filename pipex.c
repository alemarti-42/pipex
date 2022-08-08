/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:44 by alemarti          #+#    #+#             */
/*   Updated: 2022/08/08 13:03:09 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//envp takes environment variables as a third argument for the main.
char	**get_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

void	check_leaks()
{
	//system("leaks pipex");
}

void put_error(char* text, char* element)
{
	ft_putstr_fd(text, 2);
	ft_putstr_fd(element, 2);
	ft_putstr_fd("\n", 2);
}

int	main(int argc, char *argv[], char *envp[])
{
	int			pid;
	int			fd_pipe[2];
	t_environ	*environ;
	int			fd_in;
	int			fd_out;

	atexit(check_leaks);
	pipe(fd_pipe);
	if (argc != 5)
	{
		ft_putstr_fd("pipex : wrong number of arguments\n", 2);
		return (0);
	}
	environ = init_environ(argv[1], argv[argc - 1], envp);
	fd_in = open(environ->infile, O_RDONLY);
	fd_out = open_outfile(environ->outfile);
	if (fd_in < 0)
	{
		put_error("pipex : no such file or directory: ", environ->infile);
		// ft_putstr_fd("pipex : no such file or directory: ", 2);
		// ft_putstr_fd(environ->infile, 2);
		// ft_putstr_fd("\n", 2);
		return (0);
	}
	if (fd_out < 0)
	{
		put_error("pipex : no such file or directory: ", environ->outfile);
		// ft_putstr_fd("pipex : no such file or directory: ", 2);
		// ft_putstr_fd(environ->outfile, 2);
		// ft_putstr_fd("\n", 2);
		return (0);
	}
	pid = fork();
	if (pid <= -1)
		ft_putstr_fd("Error fork one\n", 2);
	if (!pid)
		writer_child(fd_pipe, argv[3], environ, fd_out);
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("Error fork two\n", 2);
	if (!pid)
		reader_child(fd_pipe, argv[2], environ, fd_in);
	waitpid(pid, NULL, 0);
	waitpid(pid, NULL, 0);
	free_environ(environ);
	return (0);
}
