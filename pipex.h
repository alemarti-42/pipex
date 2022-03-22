/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:25:46 by alemarti          #+#    #+#             */
/*   Updated: 2022/03/22 15:44:52 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
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
}	t_environ;

//file_utils.c
int			open_infile(char *infile);

//libft_utils.c
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(const char *s, unsigned int start, size_t len);

//ft_split.c
char		**ft_split(const char *s, char c);

//Exec_utils.c
int			exec_cmd(char **cmd_args, char **paths, char *envp[]);
char		*path_join(char *path, char *cmd);
char		*which_bin(char **paths, char *cmd);

//children_utils.c
t_environ	*init_environ(char *infile, char *outfile, char *envp[]);
void		reader_child(int *fd_pipe, char *cmd, t_environ *environ);
void		writer_child(int *fd_pipe, char *cmd, t_environ *environ);
char		**get_path(char *envp[]);
#endif