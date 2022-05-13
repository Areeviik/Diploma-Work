#include "../shell.h"

void	sigquit(int sig)
{
	(void)sig;
	ft_cancel();
	rl_on_new_line();
	rl_redisplay();
}

void	ft_cancel(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p))
		return ;
	termios_p.c_lflag &= ~ECHO;
	termios_p.c_lflag &= ~ECHOCTL;
	termios_p.c_lflag |= ECHO;
	if (tcsetattr(0, 0, &termios_p))
		return ;
}

void	reprompt(int sig)
{
	(void)sig;
	ft_cancel();
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	interrupt(int sig)
{
	(void)sig;
	ft_cancel();
	rl_on_new_line();
	rl_redisplay();
	exit(1);
}
