#include <sh21.h>

void 		signal_end_prog(int sig)
{
	invert_term();
	exit(sig);
}

void		signal_handler(void)
{
	int	i;

	i = 1;
	while (i < 28)
	{
		if (i != SIGSTOP && i != SIGTTOU && i != SIGTSTP && i != SIGTTIN
			&& i != SIGWINCH && i != SIGINFO && i != SIGINT && i != SIGURG
			&& i != SIGIO)
			signal(i, signal_end_prog);
		i++;
	}
}
