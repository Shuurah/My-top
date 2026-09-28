/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

void init_window(program_parameter_t *parameter)
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(parameter->delay * 1000);
    refresh();
}

void delete_window(WINDOW *boite, WINDOW *process)
{
    if (boite != NULL)
        delwin(boite);
    if (process != NULL)
        delwin(process);
}

void print_first_box(WINDOW *boite, cpu_snapshot_t *snapshot)
{
    print_first_line(boite);
    print_second_line(boite);
    print_third_line(boite, snapshot);
    print_fourth_line(boite);
    print_fifth_line(boite);
    wrefresh(boite);
}

static void handle_down_key(selection_handle_t *selected, int absolute_pos)
{
    if (absolute_pos >= selected->all_process_count - 1)
        return;
    if (selected->selected_proc < selected->max_process_shown - 1){
        selected->selected_proc++;
        return;
    }
    selected->scroll_offset++;
}

static void handle_up_key(selection_handle_t *selected)
{
    if (selected->selected_proc > 0){
        selected->selected_proc--;
        return;
    }
    if (selected->scroll_offset > 0){
        selected->scroll_offset--;
        return;
    }
}

static void check_ch_key(int ch, selection_handle_t *selected, WINDOW *boite,
    process_info_t *processes)
{
    int absolute_pos = selected->selected_proc + selected->scroll_offset + 1;

    if (ch == 'E') {
        selected->memory_unit = (selected->memory_unit + 1) % 6;
        return;
    }
    if (ch == 'k' || ch == 'K')
        prompt_kill_process(boite, processes[absolute_pos - 1].pid);
    if (ch == KEY_DOWN)
        handle_down_key(selected, absolute_pos);
    if (ch == KEY_UP)
        handle_up_key(selected);
}

void main_loop(program_parameter_t *parameter, selection_handle_t *selected)
{
    WINDOW *boite = NULL;
    WINDOW *process = NULL;
    int ch;
    int height_first = 6;
    process_info_t processes[MAX_PROC];

    selected->max_process_shown = LINES - height_first - 2;
    boite = newwin(6, COLS, 0, 0);
    process = newwin(LINES - height_first, COLS, height_first, 0);
    for (int i = 0; parameter->frame == -1 || i < parameter->frame; i++){
        if (ch == 'q' || ch == 'Q')
            break;
        check_ch_key(ch, selected, boite, processes);
        print_first_box(boite, &selected->cpu_snapshot);
        print_second_box(process, selected, processes);
        ch = getch();
    }
    delete_window(boite, process);
    return;
}
