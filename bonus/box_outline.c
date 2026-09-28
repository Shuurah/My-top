/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** box_outline
*/

#include "my_top.h"

void set_title(WINDOW *win, int pos_x, char *title)
{
    mvwaddstr(win, 0, pos_x - 1, "┤");
    wattron(win, A_BOLD);
    wattron(win, A_REVERSE);
    mvwprintw(win, 0, pos_x, "%s", title);
    wattroff(win, A_REVERSE);
    wattroff(win, A_BOLD);
    mvwaddstr(win, 0, strlen(title) + pos_x, "├");
}

void second_box_title(WINDOW *win)
{
    set_title(win, 5, "PID");
    set_title(win, 11, "USER");
    set_title(win, 22, "PR");
    set_title(win, 28, "NI");
    set_title(win, 36, "VIRT");
    set_title(win, 46, "RES");
    set_title(win, 55, "SHR");
    set_title(win, 61, "S");
    set_title(win, 66, "%CPU");
    set_title(win, 74, "%MEM");
    set_title(win, 85, "TIME+");
    set_title(win, 93, "COMMAND");
}

void draw_unicode_box(WINDOW *win, int h, int w, char *box_name)
{
    mvwaddstr(win, 0, 0, "╭");
    mvwaddstr(win, 0, w - 1, "╮");
    mvwaddstr(win, h - 1, 0, "╰");
    mvwaddstr(win, h - 1, w - 1, "╯");
    for (int i = 1; i < w - 1; i++) {
        mvwaddstr(win, 0, i, "─");
        mvwaddstr(win, h - 1, i, "─");
    }
    for (int i = 1; i < h - 1; i++) {
        mvwaddstr(win, i, 0, "│");
        mvwaddstr(win, i, w - 1, "│");
    }
    if (box_name != NULL) {
        set_title(win, 7, box_name);
    } else {
        second_box_title(win);
    }
}

void draw_output(WINDOW *boite, WINDOW *process, int height_first)
{
    wclear(boite);
    wclear(process);
    draw_unicode_box(boite, height_first, COLS, "my_top");
    draw_unicode_box(process, LINES - height_first, COLS, NULL);
}

void handle_resize(WINDOW **boite, WINDOW **process, int height_first)
{
    clear();
    refresh();
    if (*boite != NULL)
        delwin(*boite);
    if (*process != NULL)
        delwin(*process);
    *boite = newwin(height_first, COLS, 0, 0);
    *process = newwin(LINES - height_first, COLS, height_first, 0);
    draw_output(*boite, *process, height_first);
}
