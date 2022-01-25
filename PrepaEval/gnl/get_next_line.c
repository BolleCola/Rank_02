#include "get_next_line.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char *strjoin(char *mem, char *buff)
{
	char	*str;
	int		i;
	int		j;	

	i = 0;
	j = 0;
	if (!mem || !buff)
		return (NULL);
	str = malloc((ft_strlen(mem) + ft_strlen(buff)) + 1);
	if (!str)
		return (NULL);
	while(mem[i])
	{
		str[i] = mem[i];
		i++;
	}
	while (buff[j])
	{
		str[i] = buff[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int isbn(char *mem)
{
	int i;
	
	i = 0;
	while (mem[i])
	{
		if (mem[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *getmem(char *mem, int fd)
{
	int	taille;
	int n;
	char *buff;
	char *swap;

	taille = 1;
	n = 0;
	buff = malloc(BUFFER_SIZE + 1);
	if (!mem)
		mem = malloc(1);
	while (n == 0 && taille != 0 && taille != -1)
	{
		taille = read(fd, buff, BUFFER_SIZE);
		if (taille == -1)
		{
			free(mem);
			free(buff);
			return (NULL);
		}
		if (taille != 0 && taille != -1)
		{
			buff[taille] = '\0';
			swap = strjoin(mem, buff);
			free(mem);
			mem = swap;
			swap = NULL;
		}
		n = isbn(mem);
	}
	free(buff);
	return (mem);
}

char *getresul(char *mem)
{
	int i;
	int j;
	char *res;

	res = NULL;
	i = 0;
	j = 0;
	while (mem[i])
	{
		if (mem[i] == '\n')
			break ;
		i++;
	}
	i++;
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	while (i != 0)
	{
		res[j] = mem[j];
		j++;
		i--;
	}
	res[j] = '\0';
	mem = NULL;
	return (res);
}

char *getnewmem(char *mem)
{
	int i;
	int j;
	char *res;

	i = 0;
	j = 0;
	res = NULL;
	while (mem[j])
	{
		if (mem[j] == '\n')
			break ;
		j++;
	}
	j++;
	if ((ft_strlen(mem) - j + 1) > 1)
	{
		res = malloc(ft_strlen(mem) - j + 1);
		if (!res)
			return (NULL);
		while (mem[j])
			res[i++] = mem[j++];
		res[i] = '\0';
	}
	free(mem);
	mem = NULL;
	return (res);
}

char *get_next_line(int fd)
{	
	static char *mem;
	char		*resul;

	resul = NULL;
	if (BUFFER_SIZE == 0 || (read(fd, NULL, BUFFER_SIZE) == 0 && !mem) || fd < 0)
		return (NULL);
	mem = getmem(mem, fd);
	if (mem != NULL)
	{
		resul = getresul(mem);
		mem = getnewmem(mem);
	}
	return (resul);
}

int main ()
{
	int fd;
	int	i;
	char *result;
	i = 0;
	fd = open("test", O_RDONLY);
	if (fd == -1)
		printf("\n---Erreur d'ouverture de fichier---");
	while (i < 4)
	{
		result = get_next_line(fd);
		printf("========== %d lignes ==========\n%s\n", i + 1, result);
		i++;
	}
	if (close(fd) == -1)
		printf("\n---Erreur pour la fermeture du fichier---");
	return (0);
}

