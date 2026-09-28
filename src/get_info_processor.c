/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

static void calc_delta_and_total(unsigned long long *delta,
    unsigned long long *total, unsigned long long *curr,
    unsigned long long *prev)
{
    *total = 0;
    for (int i = 0; i < 8; i++) {
        delta[i] = curr[i] - prev[i];
        *total += delta[i];
    }
}

static void compute_cpu_percentages(cpu_stats_t *stats,
    unsigned long long *delta, unsigned long long total)
{
    if (total == 0)
        return;
    stats->user = (delta[0] * 100.0) / total;
    stats->nice = (delta[1] * 100.0) / total;
    stats->system = (delta[2] * 100.0) / total;
    stats->idle = (delta[3] * 100.0) / total;
    stats->iowait = (delta[4] * 100.0) / total;
    stats->irq = (delta[5] * 100.0) / total;
    stats->softirq = (delta[6] * 100.0) / total;
    stats->steal = (delta[7] * 100.0) / total;
}

static int read_cpu_values(unsigned long long *curr)
{
    FILE *file;

    file = fopen("/proc/stat", "r");
    if (!file)
        return 0;
    fscanf(file, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
        &curr[0], &curr[1], &curr[2], &curr[3],
        &curr[4], &curr[5], &curr[6], &curr[7]);
    fclose(file);
    return 1;
}

cpu_stats_t get_cpu_stats(cpu_snapshot_t *snapshot)
{
    cpu_stats_t stats;
    unsigned long long curr[8];
    unsigned long long delta[8];
    unsigned long long delta_total;

    memset(&stats, 0, sizeof(cpu_stats_t));
    if (!read_cpu_values(curr))
        return stats;
    if (!snapshot->initialized) {
        memcpy(snapshot->values, curr, sizeof(snapshot->values));
        snapshot->initialized = 1;
        return stats;
    }
    calc_delta_and_total(delta, &delta_total, curr, snapshot->values);
    compute_cpu_percentages(&stats, delta, delta_total);
    memcpy(snapshot->values, curr, sizeof(snapshot->values));
    return stats;
}

int is_pid_dir(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isdigit(name[i]))
            return 0;
    }
    return 1;
}

char get_process_state(const char *pid)
{
    char path[256];
    char buffer[1024];
    char state = 'E';
    FILE *file;
    char *p;

    snprintf(path, sizeof(path), "/proc/%s/stat", pid);
    file = fopen(path, "r");
    if (file == NULL)
        return 'E';
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        p = strrchr(buffer, ')');
        if (p != NULL) {
            sscanf(p + 1, " %c", &state);
        }
    }
    fclose(file);
    return state;
}

void update_stats_by_state(task_stats_t *stats, char state)
{
    if (state == 'R')
        stats->running++;
    if (state == 'S' || state == 'D' || state == 'I'
        || state == 'W' || state == 'P')
        stats->sleeping++;
    if (state == 'T' || state == 't')
        stats->stopped++;
    if (state == 'Z')
        stats->zombie++;
}

task_stats_t get_task_stats(void)
{
    task_stats_t stats = {0, 0, 0, 0, 0};
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL)
        return stats;
    entry = readdir(dir);
    while (entry != NULL) {
        if (is_pid_dir(entry->d_name)) {
            stats.total++;
            update_stats_by_state(&stats, get_process_state(entry->d_name));
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return stats;
}
