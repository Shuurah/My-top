/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

void print_bold_int(WINDOW *win, int value)
{
    wattron(win, A_BOLD);
    wprintw(win, "%d", value);
    wattroff(win, A_BOLD);
}

void print_bold_int_padded(WINDOW *win, int value)
{
    wattron(win, A_BOLD);
    wprintw(win, "%3d", value);
    wattroff(win, A_BOLD);
}

void print_bold_value(WINDOW *win, const char *format, ...)
{
    va_list args;

    wattron(win, A_BOLD);
    va_start(args, format);
    vw_printw(win, format, args);
    va_end(args);
    wattroff(win, A_BOLD);
}

static void init_program_parameters(program_parameter_t *parameter,
    selection_handle_t *selected)
{
    parameter->is_username = false;
    parameter->is_delay = false;
    parameter->is_frame = false;
    parameter->username = NULL;
    parameter->delay = 3.0;
    parameter->frame = 100000000;
    selected->first_process_shown = 0;
    selected->selected_proc = -1;
    selected->max_process_shown = 20;
    selected->scroll_offset = 0;
    selected->memory_unit = UNIT_KB;
}

static void exit_error(const char *message, int code)
{
    fprintf(stderr, "my_top: %s\n", message);
    exit(code);
}

static void parse_arg(char *argv[], program_parameter_t *parameter, int i)
{
    if (argv[i][1] == 'U'){
        if (parameter->is_username)
            exit_error("conflicting process selections (U/p/u)", 84);
        parameter->username = argv[i + 1];
        parameter->is_username = true;
    }
    if (argv[i][1] == 'd'){
        parameter->delay = strtod(argv[i + 1], NULL);
        parameter->is_delay = true;
    }
    if (argv[i][1] == 'n'){
        parameter->frame = atoi(argv[i + 1]);
        parameter->is_frame = true;
    }
}

void parameter_parser(int argc, char *argv[], program_parameter_t *parameter)
{
    for (int i = 1; i < argc; i++){
        if (argv[i][0] == '-'){
            parse_arg(argv, parameter, i);
            i++;
            continue;
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    program_parameter_t parameter;
    selection_handle_t selected;

    init_program_parameters(&parameter, &selected);
    if (argc > 1)
        parameter_parser(argc, argv, &parameter);
    init_window(&parameter);
    main_loop(&parameter, &selected);
    endwin();
    return 0;
}
