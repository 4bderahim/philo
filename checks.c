int	ph_atoi(char *s)
{
	int	res;
    int i;

    i = 0;
	res = 0;
	while (s[i] != 0)
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
            return (-1);
		res = (res * 10) + (s[i] - 48);
		i++;
	}
	return (res);
}

int check_args(char **argv, int argc)
{
    int i;
    i = 1;

    while (i < argc)
    {
        if (ph_atoi(argv[i]) == -1)
            return (0);
        i++;
    }
    return (1);
}