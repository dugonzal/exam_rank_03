#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 3 
#endif

int	ft_strchr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int i = 0;
	if (str)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (0);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *str;
	int i;
	int j;

	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (s1)
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free (s1);
	return (str);
}	

char *read_line(char *str, int fd)
{
	char *buffer;
	int i;

	i = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0'; /// init en 0 buffer;
	while (!ft_strchr(buffer) && i > 0)
	{
		if (((i = read(fd, buffer, BUFFER_SIZE)) == -1))
			return (NULL);
		if (!buffer && !i)
		{
			free (buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free (buffer);
	buffer  = NULL;
	return (str);
}


char *get_line(char *str)
{
	char *tmp;
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	tmp = (char *)malloc(sizeof(char) * i + 2);
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] != 0 && str[i] != '\n')
	{
		tmp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		tmp[i] = '\n';
		tmp[i + 1] = '\0';
		return (tmp);
	}
	tmp[i] = '\0';
	return (tmp);
}

char *next_line(char *str)
{
	char *tmp;
	int i;
	int j;

	i = 0;
	while (str[i] != 0 && str[i] != '\n')
		i++;
	tmp = (char *)malloc(sizeof(char) * ft_strlen((str) - i + 2));
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	return (tmp);
}

char *get_next_line(int fd)
{
	char *line;
	char static *str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_line(str, fd);
	line = get_line(str);
	str = next_line (str);
	if (line[0] == '\0')
		return (NULL);
	return (line);
}

#include <fcntl.h>
int	main(void)
{
	char *line;
//	int fd = open ("./hola", O_RDONLY);
	while (	line = get_next_line (0)){
		
		printf ("[%s]", line);
		free (line);
	}

}
