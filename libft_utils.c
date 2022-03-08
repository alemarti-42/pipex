#include"pipex.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
		write(fd, &s[i], 1);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;
    int res;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] == s2[i])
	{
		if (!s1[i])
			break ;
		if (--n == 0)
			return (0);
		i++;
	}
    res = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (res);
}


char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s[i] && i < start)
	{
		i++;
	}
	while (j < len && s[i])
	{
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = 0;
	return (res);
}