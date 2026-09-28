/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

void print_first_line(WINDOW *win)
{
    double load[3];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    uptime_t up = get_uptime();
    int users = get_user_count();

    mvwprintw(win, 0, 0, "top - %02d:%02d:%02d up ",
        t->tm_hour, t->tm_min, t->tm_sec);
    if (up.days > 0)
        wprintw(win, "%d day%s, ", up.days, up.days > 1 ? "s" : "");
    if (up.hours > 0)
        wprintw(win, "%2d:%02d, ", up.hours, up.minutes);
    else
        wprintw(win, "%d min, ", up.minutes);
    wprintw(win, "%2d users,  ", users);
    if (my_getloadavg(load, 3) == 0)
        wprintw(win, "load average: %.2f, %.2f, %.2f    ",
            load[0], load[1], load[2]);
}

void print_second_line(WINDOW *win)
{
    task_stats_t stats = get_task_stats();

    mvwprintw(win, 1, 0, "Tasks: ");
    print_bold_int_padded(win, stats.total);
    wprintw(win, " total, ");
    print_bold_int_padded(win, stats.running);
    wprintw(win, " running, ");
    print_bold_int_padded(win, stats.sleeping);
    wprintw(win, " sleeping, ");
    print_bold_int_padded(win, stats.stopped);
    wprintw(win, " stopped, ");
    print_bold_int_padded(win, stats.zombie);
    wprintw(win, " zombie    ");
}

void print_third_line(WINDOW *boite, cpu_snapshot_t *snapshot)
{
    cpu_stats_t cpu;

    cpu = get_cpu_stats(snapshot);
    mvwprintw(boite, 2, 0, "%%Cpu(s): ");
    print_bold_value(boite, "%4.1f", cpu.user);
    wprintw(boite, " us, ");
    print_bold_value(boite, "%4.1f", cpu.system);
    wprintw(boite, " sy, ");
    print_bold_value(boite, "%4.1f", cpu.nice);
    wprintw(boite, " ni, ");
    print_bold_value(boite, "%4.1f", cpu.idle);
    wprintw(boite, " id, ");
    print_bold_value(boite, "%4.1f", cpu.iowait);
    wprintw(boite, " wa, ");
    print_bold_value(boite, "%4.1f", cpu.irq);
    wprintw(boite, " hi, ");
    print_bold_value(boite, "%4.1f", cpu.softirq);
    wprintw(boite, " si, ");
    print_bold_value(boite, "%4.1f", cpu.steal);
    wprintw(boite, " st");
}

void print_fourth_line(WINDOW *win)
{
    mem_stats_t mem;
    double total_mb;
    double free_mb;
    double used_mb;
    double buff_cache_mb;

    mem = get_memory_stats();
    total_mb = mem.total / 1024.0;
    free_mb = mem.free / 1024.0;
    used_mb = (mem.total - mem.free - mem.buffers - mem.cached) / 1024.0;
    buff_cache_mb = (mem.buffers + mem.cached) / 1024.0;
    mvwprintw(win, 3, 0, "MiB Mem : ");
    print_bold_value(win, "%8.1f", total_mb);
    wprintw(win, " total, ");
    print_bold_value(win, "%8.1f", free_mb);
    wprintw(win, " free, ");
    print_bold_value(win, "%8.1f", used_mb);
    wprintw(win, " used, ");
    print_bold_value(win, "%8.1f", buff_cache_mb);
    wprintw(win, " buff/cache");
}

void print_fifth_line(WINDOW *win)
{
    mem_stats_t mem;
    double swap_total_mb;
    double swap_free_mb;
    double swap_used_mb;
    double avail_mb;

    mem = get_memory_stats();
    swap_total_mb = mem.swap_total / 1024.0;
    swap_free_mb = mem.swap_free / 1024.0;
    swap_used_mb = (mem.swap_total - mem.swap_free) / 1024.0;
    avail_mb = mem.available / 1024.0;
    mvwprintw(win, 4, 0, "MiB Swap: ");
    print_bold_value(win, "%8.1f", swap_total_mb);
    wprintw(win, " total, ");
    print_bold_value(win, "%8.1f", swap_free_mb);
    wprintw(win, " free, ");
    print_bold_value(win, "%8.1f", swap_used_mb);
    wprintw(win, " used. ");
    print_bold_value(win, "%8.1f", avail_mb);
    wprintw(win, " avail Mem");
}
