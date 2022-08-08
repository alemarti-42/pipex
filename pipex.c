/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:44 by alemarti          #+#    #+#             */
/*   Updated: 2022/08/08 17:14:35 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	put_error(char *text, char *element)
{
	ft_putstr_fd(text, 2);
	ft_putstr_fd(element, 2);
	ft_putstr_fd("\n", 2);
}

void	free_environ(t_environ *environ)
{
	free_split(environ->paths);
	free(environ);
}

int	main(int argc, char *argv[], char *envp[])
{
	int			fd_pipe[2];
	int			fd_in_out[2];
	t_environ	*environ;

	if (argc != 5)
	{
		ft_putstr_fd("pipex : wrong number of arguments\n", 2);
		return (-1);
	}
	environ = init_environ(argv[1], argv[argc - 1], envp);
	if (open_files(fd_in_out, environ) < 0)
		return (-1);
	pipe(fd_pipe);
	spawn_children(environ, argv, fd_pipe, fd_in_out);
	free_environ(environ);
	return (0);
}

	//SPAWN_CHILDREN
	// pid = fork();
	// if (pid < 0)
	// 	ft_putstr_fd("Error fork one\n", 2);
	// if (!pid)
	// 	writer_child(fd_pipe, argv[3], environ, fd_in_out[1]);
	// pid = fork();
	// if (pid < 0)
	// 	ft_putstr_fd("Error fork two\n", 2);
	// if (!pid)
	// 	reader_child(fd_pipe, argv[2], environ, fd_in_out[0]);
	// waitpid(pid, NULL, 0);
	// waitpid(pid, NULL, 0);

	//open_files
	// fd_in_out[0] = open_infile(environ->infile);
	// fd_in_out[1] = open_outfile(environ->outfile);
	// if (fd_in_out[0] < 0)
	// {
	// 	put_error("pipex : no such file or directory: ", environ->infile);
	// 	return (0);
	// }
	// if (fd_in_out[1] < 0)
	// {
	// 	put_error("pipex : no such file or directory: ", environ->outfile);
	// 	return (0);
	// }
