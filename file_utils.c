/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:32 by alemarti          #+#    #+#             */
/*   Updated: 2022/03/22 15:48:28 by alemarti         ###   ########.fr       */
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

void	redirection(char *cmd, char **env, int fdin)
{
	int	pid;
	int	pipefd[2];
}
