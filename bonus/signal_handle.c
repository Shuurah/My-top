/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

static int prompt_for_pid(WINDOW *win, int default_pid)
{
    char input[16];
    int pid;

    mvwprintw(win, 6, 1, "PID to signal/kill [default pid = %d]:             ",
        default_pid);
    wrefresh(win);
    echo();
    wgetnstr(win, input, sizeof(input) - 1);
    noecho();
    pid = (strlen(input) > 0) ? atoi(input) : default_pid;
    return pid;
}

static int prompt_for_signal(WINDOW *win, int pid)
{
    char input[16];
    int signal;

    mvwprintw(win, 6, 1, "Send pid %d signal [15/sigterm]:             ", pid);
    wrefresh(win);
    echo();
    wgetnstr(win, input, sizeof(input) - 1);
    noecho();
    signal = (strlen(input) == 0) ? 15 : atoi(input);
    return signal;
}

static void display_result(WINDOW *win, int pid, int signal)
{
    mvwprintw(win, 6, 1, "Signal %d sent to PID %d successfully              ",
        signal, pid);
    wrefresh(win);
    mvwprintw(win, 6, 1, "                                                  ");
    napms(1500);
    wrefresh(win);
}

void prompt_kill_process(WINDOW *win, int pid)
{
    int signal;

    pid = prompt_for_pid(win, pid);
    signal = prompt_for_signal(win, pid);
    if (kill(pid, signal) == 0)
        display_result(win, pid, signal);
}
