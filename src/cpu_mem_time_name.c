/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

void get_process_name(int pid, char *name)
{
    char filename[256];
    FILE *file;
    int len;

    snprintf(filename, sizeof(filename), "/proc/%d/comm", pid);
    file = fopen(filename, "r");
    if (file == NULL) {
        strcpy(name, "unknown");
        return;
    }
    if (fgets(name, 256, file) == NULL) {
        strcpy(name, "unknown");
        fclose(file);
        return;
    }
    fclose(file);
    len = strlen(name);
    if (len > 0 && name[len - 1] == '\n')
        name[len - 1] = '\0';
}

static unsigned long get_total_cpu_time(int pid)
{
    char path[64];
    FILE *file;
    unsigned long utime;
    unsigned long stime;

    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    file = fopen(path, "r");
    if (!file)
        return 0;
    fscanf(file, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu",
        &utime, &stime);
    fclose(file);
    return utime + stime;
}

void get_cpu_time(int pid, char *time_str)
{
    unsigned long total = get_total_cpu_time(pid);
    long ticks = sysconf(_SC_CLK_TCK);
    unsigned long sec = total / ticks;
    unsigned long min = sec / 60;
    unsigned long cs = ((total % ticks) * 100) / ticks;

    snprintf(time_str, 16, "%lu:%02lu.%02lu", min, sec % 60, cs);
}
