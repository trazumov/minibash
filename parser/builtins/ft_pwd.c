#include "../parser.h"

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		printf("%s\n", buf);
		free(buf);
		return (0);
	}
	else
		return (1);
}
