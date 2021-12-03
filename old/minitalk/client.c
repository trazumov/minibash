#include "minitalk.h"

static void	send_bit(int pid, char c)
{
	char	bin[9];
	char	tmp;
	int		i;
	int		j;

	i = 7;
	j = 0;
	while (i >= 0)
	{
		tmp = (c & (1 << i));
		if (tmp)
			bin[j] = '1';
		else
			bin[j] = '0';
		if (bin[j] == '0')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		j++;
		usleep(100);
	}
	bin[j] = '\0';
}

static void	send_bit_by_bit(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_bit(pid, message[i]);
		i++;
	}
}

static void	sig_handler(int sig)
{
	(void)sig;
	if (sig == SIGUSR1)
		ft_putstr_fd("Message was received by Server\n", 1);
}

int	main(int argc, char **argv)
{
	int		server_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Incorrect arguments\n", 2);
		return (1);
	}
	signal(SIGUSR1, sig_handler);
	server_pid = ft_atoi(argv[1]);
	send_bit_by_bit(server_pid, argv[2]);
	send_bit(server_pid, '\0');
	return (0);
}
