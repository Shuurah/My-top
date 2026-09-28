/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

static void parse_mem_line(char *line, mem_stats_t *stats)
{
    sscanf(line, "MemTotal: %lu", &stats->total);
    sscanf(line, "MemFree: %lu", &stats->free);
    sscanf(line, "MemAvailable: %lu", &stats->available);
    sscanf(line, "Buffers: %lu", &stats->buffers);
    sscanf(line, "Cached: %lu", &stats->cached);
    sscanf(line, "SwapTotal: %lu", &stats->swap_total);
    sscanf(line, "SwapFree: %lu", &stats->swap_free);
}

mem_stats_t get_memory_stats(void)
{
    FILE *file;
    char line[256];
    mem_stats_t stats;

    memset(&stats, 0, sizeof(mem_stats_t));
    file = fopen("/proc/meminfo", "r");
    if (!file)
        return stats;
    while (fgets(line, sizeof(line), file))
        parse_mem_line(line, &stats);
    fclose(file);
    return stats;
}

void get_process_memory(int pid, unsigned long *virt,
    unsigned long *res, unsigned long *shr)
{
    char path[256];
    FILE *file;
    unsigned long size;
    unsigned long resident;
    unsigned long shared;
    long page_size = sysconf(_SC_PAGESIZE) / 1024;

    *virt = 0;
    *res = 0;
    *shr = 0;
    snprintf(path, sizeof(path), "/proc/%d/statm", pid);
    file = fopen(path, "r");
    if (file == NULL)
        return;
    if (fscanf(file, "%lu %lu %lu", &size, &resident, &shared) == 3) {
        *virt = size * page_size;
        *res = resident * page_size;
        *shr = shared * page_size;
    }
    fclose(file);
}
