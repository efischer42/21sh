#include "ft_readline.h"

struct s_keymap_entry g_emacs_standard_keymap[] =
{
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_home },
	{ ISFUNC, cursor_l },
	{ ISFUNC, kill_line },
	{ ISFUNC, rl_eot },
	{ ISFUNC, rl_end },
	{ ISFUNC, cursor_r },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_backspace },
	{ ISFUNC, autocomplete },
	{ ISFUNC, rl_void },
	{ ISFUNC, clear_eol },
	{ ISFUNC, clear_scr },
	{ ISFUNC, rl_void },
	{ ISFUNC, history_down },
	{ ISFUNC, rl_void },
	{ ISFUNC, history_up },
	{ ISFUNC, rl_void },
	{ ISFUNC, hist_lookup },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_reversel },
	{ ISFUNC, clear_befline },
	{ ISFUNC, rl_void },
	{ ISFUNC, cut_prev_wd },
	{ ISFUNC, rl_ctrl_mode },
	{ ISFUNC, clip_paste },
	{ ISFUNC, rl_void },
	{ ISKMAP, rl_void },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_void },
	{ ISFUNC, undo_last },
	[ ' ' ... '~' ] = { ISFUNC, rl_insert },
	{ ISFUNC, rl_backspace }
};

struct s_keymap_entry g_emacs_ctlx_keymap[] =
{
	[ 0 ... 50 ] = { ISFUNC, rl_void },
	{ ISFUNC, rl_delete },
	[ 52 ... 64 ] = { ISFUNC, rl_void },
	{ ISFUNC, history_up },
	{ ISFUNC, history_down },
	{ ISFUNC, cursor_r },
	{ ISFUNC, cursor_l },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_end },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_home },
	[ 73 ... 84 ] = { ISFUNC, rl_void },
	{ ISFUNC, cursor_u },
	{ ISFUNC, cursor_d },
	{ ISFUNC, wd_right },
	{ ISFUNC, wd_left },
	[ 89 ... 127 ] = { ISFUNC, rl_void },
};

struct s_keymap_entry g_emacs_meta_keymap[] =
{
	[ 0 ... 97 ] = { ISFUNC, rl_void },
	{ ISFUNC, wd_left },
	{ ISFUNC, rl_void },
	{ ISFUNC, cut_next_wd },
	{ ISFUNC, rl_void },
	{ ISFUNC, wd_right },
	[ 103 ... 115 ] = { ISFUNC, rl_void },
	{ ISFUNC, swap_words },
	[ 117 ... 127 ] = { ISFUNC, rl_void },
};
