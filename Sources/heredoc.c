#include "../shell.h"
#include <string.h>

char	*ft_strjoin1(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2 && s2[++i])
	{
		str[len1] = s2[i];
		len1++;
	}
	str[len1] = '\0';
	return (str);
}

char	*hdoc_read(char *delim)
{
	char	*read;
	char	*temp;
	char	*temp2;

	temp = NULL;
	sig_heredoc();
	while (1)
	{
		read = readline(">");
		if (!ft_strncmp_quote(read, delim))
			break ;
		else
		{
			temp2 = ft_strjoin1(temp, read);
			free(temp);
			temp = ft_strjoin1(temp2, "\n");
		}
	}
	return (temp);
}

int	hdoc_fn(char *delim, int fd[2], int status, pid_t pid)
{
	char	*temp;

	temp = NULL;
	g_g.hdoc = 1;
	sig_ignore();
	pid = fork();
	pipe(fd);
	if (pid == 0)
		temp = hdoc_read(delim);
	if (pid == 0)
		sig_default();
	wait(&status);
	if (WEXITSTATUS(status) == 1)
	{
		g_g.status = 130;
		ft_putstr_fd("\n", 1);
	}
	sig_init();
	sig_heredoc();
	if (temp != NULL)
		write(fd[1], temp, ft_strlen(temp));
	if (temp != NULL)
		free(temp);
	close(fd[1]);
	return (fd[0]);
}
