/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

static void print_process_arg(WINDOW *process,
    process_info_t processes[MAX_PROC], int proc_idx)
{
    wprintw(process, "%7d   %-8s ", processes[proc_idx].pid,
        processes[proc_idx].user);
    if (processes[proc_idx].priority == -100)
        wprintw(process, "  rt");
    else
        wprintw(process, " %3d", processes[proc_idx].priority);
    wprintw(process,
        "   %3d   %7lu   %6lu   %6lu   %c    %#4.1f    %#4.1f     %s   %s",
        processes[proc_idx].nice, processes[proc_idx].virt,
        processes[proc_idx].res, processes[proc_idx].shr,
        processes[proc_idx].state, processes[proc_idx].cpu_percent,
        processes[proc_idx].mem_percent, processes[proc_idx].time_str,
        processes[proc_idx].command);
    wattroff(process, A_REVERSE);
    wprintw(process, "                                               ");
}

void print_second_box(WINDOW *process, selection_handle_t *selected,
    process_info_t processes[MAX_PROC])
{
    int proc_idx;

    selected->all_process_count = collect_pids(processes, MAX_PROC);
    wmove(process, 1, 1);
    for (int i = 0; i < LINES - 10; i++){
        proc_idx = i + selected->scroll_offset;
        if (proc_idx >= selected->all_process_count)
            break;
        wmove(process, i + 1, 1);
        if (selected->selected_proc == i && selected->selected_proc >= 0){
            wattron(process, A_REVERSE);
            print_process_arg(process, processes, proc_idx);
        } else
            print_process_arg(process, processes, proc_idx);
    }
    wrefresh(process);
}
