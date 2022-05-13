#include "shell.h"

void	welcome_text(void)
{
	int	len;

	len = ft_strlen("░▒▓██████████►╬◄██████████▓▒░\n");
	write(1, "░▒▓██████████►╬◄██████████▓▒░\n", len);
	write(1, "░▒▓██►╔╦╦╦═╦╗╔═╦═╦══╦═╗◄██▓▒░\n", len);
	write(1, "░▒▓██►║║║║╩╣╚╣═╣║║║║║╩╣◄██▓▒░\n", len);
	write(1, "░▒▓██►╚══╩═╩═╩═╩═╩╩╩╩═╝◄██▓▒░\n", len);
	write(1, "░▒▓██████████►╬◄██████████▓▒░\n", len);
}

void	mini_checkings(char *str)
{
	if (!str)
	{
		free(str);
		ft_error("exit", 0);
	}
	if (ft_strlen(str))
		add_history(str);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	if (argc != 1)
		puterror("Wrong number of arguments\n");
	fill_env(env, argc, argv);
	welcome_text();
	sig_init();
	while (1)
	{
		str = readline("shell: ");
		if (!is_space(str))
		{
			mini_checkings(str);
			if (!check_quotes(str) || !check_sem_and_pipe(str)
				|| !check_red(str))
			{
				print_error("Syntax error\n");
				g_g.status = 258;
				update_status();
				continue ;
			}
			start(str);
		}
	}
	return (0);
}
