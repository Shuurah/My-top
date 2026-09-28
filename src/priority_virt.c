/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

static int parse_priority_field(char *line)
{
    char *token;
    int field;
    int priority;

    token = line;
    field = 1;
    while (field < 18 && token) {
        token = strchr(token + 1, ' ');
        field++;
    }
    if (token && sscanf(token, "%d", &priority) == 1)
        return priority;
    return 0;
}

int get_priority(int pid)
{
    char path[64];
    char line[256];
    FILE *fp;
    int priority;

    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    fp = fopen(path, "r");
    if (!fp)
        return 0;
    if (!fgets(line, sizeof(line), fp)) {
        fclose(fp);
        return 0;
    }
    priority = parse_priority_field(line);
    fclose(fp);
    return priority;
}

unsigned long get_info_virtual_memory(int pid)
{
    char path[64];
    char line[256];
    FILE *fp;
    unsigned long virt;

    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    fp = fopen(path, "r");
    if (!fp)
        return 0;
    virt = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "VmSize:", 7) == 0) {
            sscanf(line, "VmSize: %lu", &virt);
            break;
        }
    }
    fclose(fp);
    return virt;
}

void format_virt_memory(process_info_t *prc, memory_unit_t unit)
{
    double value;
    const char *suffix[] = {"", "m", "g", "t", "p", "e"};

    value = (double)prc->virt;
    for (int i = 0; i < unit; i++)
        value /= 1024.0;
    if (unit == UNIT_KB && value < 10000) {
        snprintf(prc->virt_str, sizeof(prc->virt_str), "%lu", prc->virt);
    } else {
        snprintf(prc->virt_str, sizeof(prc->virt_str), "%.1f%s",
            value, suffix[unit]);
    }
}
