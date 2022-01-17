#include <unistd.h>

int main (int argc, char **argv)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	c = 0;
	argc = 0;
	while (argv[1][i])
	{
		j = i + 1;
		while (argv[1][j])
		{
			if (argv[1][i] == argv[1][j])
				argv[1][j] = 127;
			j++;
		}
		i++;
	}
	i = 0;
	while (argv[1][i])
	{
		j = 0;
		while (argv[2][j])
		{
			if (argv[1][i] == argv[2][j])
				c = 1;	
			j++;
		}
		if (c == 1)
			write(1, &argv[1][i], 1);
		c = 0;
		i++;
	}
}	
