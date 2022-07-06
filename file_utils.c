/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:32 by alemarti          #+#    #+#             */
/*   Updated: 2022/07/06 13:58:15 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	open_infile(char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		ft_putstr_fd("pipex:", 2);
		ft_putstr_fd(infile, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	return (open(infile, O_RDONLY));
}

int	open_outfile(char *outfile)
{
	int	res;

	res = open(outfile, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	// if (access(outfile, F_OK) == -1)
	// {
	// 	ft_putstr_fd("pipex:", 2);
	// 	ft_putstr_fd(outfile, 2);
	// 	ft_putstr_fd(" : No such file or directory\n", 2);
	// 	return (-1);
	// }
	if (access(outfile, W_OK) == -1)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putstr_fd(outfile, 2);
		return (-1);
	}
	return (res);
}
// void	redirection(char *cmd, char **env, int fdin)
// {
// 	int	pid;
// 	int	pipefd[2];
// }
