#include "minitalk.h"

static t_byte_char	g_char;

static void	action(int signo, siginfo_t *info, void *context)
{
	char	c;

	(void)signo;
	(void)context;
	(void)info;
	if (signo == SIGUSR1)
		c = '0';
	if (signo == SIGUSR2)
		c = '1';
	g_char.binary[g_char.get_bit_count] = c;
	g_char.get_bit_count++;
	if (g_char.get_bit_count == 8)
	{
		c = (char)decode_char(g_char.binary);
		if (c == '\0')
			kill(info->si_pid, SIGUSR1);
	}
}

void	init(char **msg)
{
	int	i;

	g_char.get_bit_count = 0;
	i = 0;
	while (i < 8)
	{
		g_char.binary[i] = '0';
		i++;
	}
	g_char.binary[i] = '\0';
	ft_putstr_fd("Server PID is: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	*msg = NULL;
}

int	main(void)
{
	char				*msg;
	char				curr_char;
	struct sigaction	s_action;

	s_action.sa_sigaction = action;
	s_action.sa_flags = SA_SIGINFO;
	init(&msg);
	while (1)
	{
		sigaction(SIGUSR1, &s_action, NULL);
		sigaction(SIGUSR2, &s_action, NULL);
		if (g_char.get_bit_count == 8)
		{
			g_char.get_bit_count = 0;
			curr_char = (char)decode_char(g_char.binary);
			msg = ft_strjoin_char(msg, curr_char);
			if (curr_char == '\0')
			{
				ft_putstr_fd(msg, 1);
				free(msg);
				msg = NULL;
			}
		}
		pause();
	}
}
