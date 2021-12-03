#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>

typedef struct s_byte_char
{
	int		get_bit_count;
	char	binary[9];
}	t_byte_char;

char	*ft_strjoin_char(char *str, char c);
int		decode_char(char bin[9]);

#endif