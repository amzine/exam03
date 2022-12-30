#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
		str[k++] = s1[i++];
	while (s2[j])
		str[k++] = s2[j++];
	str[k] = '\0';
	free(s1);
	return (str);
}

char	*ft_pre_save(char *stock)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*stock)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i += 1;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
		str[j++] = stock[i++];
	if (stock[i] == '\n')
		str[j++] = stock[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_sec_save(char *stock)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	str = malloc(ft_strlen(stock) - i);
	if (!str)
		return (NULL);
	i += 1;
	j = 0;
	while (stock[i])
		str[j++] = stock[i++];
	str[j] = '\0';
	free(stock);
	return (str);
}

char *buffer_to_stock(int fd, char *stock)
{
    char *buff;

    int i;

    buff = malloc((BUFFER_SIZE + 1));
    if (!buff)
        return(NULL);
    i = 1;
    while (!ft_strchr(stock, '\n') && i != 0)
    {
        i = read(fd, buff, BUFFER_SIZE);
        if (i == -1)
        {
            free(buff);
            if (stock)
                free(stock);
            return NULL;
        }
        buff[i] = '\0';
        stock = ft_strjoin(stock, buff);
    }
    free(buff);
    return stock;
}

char *get_next_line(int fd)
{
    char    *line;
    static char *stock;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return(NULL);
    stock = buffer_to_stock(fd, stock);
    if (!stock)
        return(NULL);
    line = ft_pre_save(stock);
    stock = ft_sec_save(stock);
    return(line);
}

int main()
{
    char *str = get_next_line(0);
    printf("%s",str);
    return (0);
}
