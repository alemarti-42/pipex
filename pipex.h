#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>


//file_utils.c
int     open_infile(char *infile);


//libft_utils.c
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);

//ft_split.c
char	**ft_split(const char *s, char c);

//Exec_utils.c
int     exec_cmd(char *cmd, char **paths);
char    *path_join(char *path, char *cmd);
char    *which_bin(char **paths, char *cmd);


#endif