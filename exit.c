#include <sh21.h>

void exit_ctrl_d(t_env *env, t_data *data)
{
	free(singleton_termios(NULL, 0));
	history_exit(data);
	delete_list(env);
	delete_heredocs(data);
	delete_list_history(data->history);
	delete_list_var(data->var);
	delete_data(data);
	// free(data->prompt);
	exit(EXIT_SUCCESS);
}
