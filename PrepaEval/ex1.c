#include <unistd.h>

int main (int argc, char **argv)
{
	int i;
	int j;

	(void)argc;
	i = 0;
	while (argv[1][i])
	{
		j = i + 1;
		while (argv[1][j])
		{
			if (argv[1][i] == argv[1][j])
				argv[1][j] = 127;
			j++;
		}
		j = 0;
		while (argv[2][j])
		{
			if (argv[1][i] == argv[2][j])
				argv[2][j] = 127;
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (argv[2][i])
	{
		j = i + 1;
		while (argv[2][j])
		{
			if (argv[2][i] == argv[2][j])
				argv[2][j] = 127;
			j++;
		}
		i++;
	}
	i = 0;
	while (argv[1][i])
	{
		if (argv[1][i] != 127)
			write(1, &argv[1][i], 1);
		i++;
	}
	i = 0;
	while (argv[2][i])
	{
		if (argv[2][i] != 127)
			write(1, &argv[2][i], 1);
		i++;
	}
}
