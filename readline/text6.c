# include "ft_readline.h"

_Bool	g_ctrl_mode = 0;

static void	switch_cbpos(void)
{
	int	tmp;

	tmp = g_dis.cbpos;
	g_dis.cbpos = g_dis.cbpos_prev;
	g_dis.cbpos_prev = tmp;
	update_line();
}

void	rl_ctrl_mode(union u_buffer u)
{
	if (g_ctrl_mode)
	{
		if (u.buf[0] == 24 && u.buf[1] == 0)
			switch_cbpos();
	}
	g_ctrl_mode ^= 1;
}

void	rl_eot(void)
{
	if (g_line.len == 0)
	{
		free(g_line.line);
		write(STDOUT_FILENO, "\n", 1);
		deprep_terminal();
		rl_clear_signals();
		exit(0);
	}
	else
		rl_delete();
}
