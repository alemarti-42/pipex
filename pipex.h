/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:46 by alemarti          #+#    #+#             */
/*   Updated: 2023/07/12 14:17:56 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_command
{
	char	*path;
	char	*commands;
}	t_command;

typedef struct s_environ
{
	char	**envp;
	char	**paths;
	char	*infile;
	char	*outfile;
	int		fd_in_out[2];
	int		n_cmd;
}	t_environ;

//file_utils.c
int			open_files(t_environ *environ);
int			open_infile(char *infile);
int			open_outfile(char *outfile);

//Exec_utils.c
int			exec_cmd(char **cmd_args, char **paths, char *envp[]);

//ft_split.c
char		**ft_split(const char *s, char c);
void		free_split(char **str);

//children_utils.c
int			spawn_children(t_environ *environ, char *argv[], \
	int fd_pipe[1024][2]);
void		free_environ(t_environ *environ);

//pipex.c
void		put_error(char *text, char *element);

//libft_utils.c
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(const char *s, unsigned int start, size_t len);

#endif