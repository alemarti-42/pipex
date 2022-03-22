/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:44 by alemarti          #+#    #+#             */
/*   Updated: 2022/03/22 15:59:48 by alemarti         ###   ########.fr       */
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
	system("leaks pipex");
}
//input format: "infile" "cmd1" "cmd2" "outfile"

int	main(int argc, char *argv[], char *envp[])
{
	int			pid;
	int			fd_pipe[2];
	t_environ	*environ;

	atexit(check_leaks);
	pipe(fd_pipe);
	if (argc != 5)
	{
		ft_putstr_fd("Wrong argument number\n", 2);
		return (0);
	}
	environ = init_environ(argv[1], argv[argc - 1], envp);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("Error creando procesos\n", 2);
	else if (pid == 0)
		reader_child(fd_pipe, argv[2], environ);
	else
		writer_child(fd_pipe, argv[3], environ);
	//waitpid(pid, NULL, 0);
	return (0);
}
