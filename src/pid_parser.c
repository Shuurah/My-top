/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

static int is_number(const char *character)
{
    while (*character){
        if (!isdigit(*character))
            return 0;
        character++;
    }
    return 1;
}

char get_process_state_pid(int pid)
{
    char path[256];
    char buffer[1024];
    FILE *file;

    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    file = fopen(path, "r");
    if (!file)
        return '?';
    if (fgets(buffer, sizeof(buffer), file)) {
        fclose(file);
        return buffer[strrchr(buffer, ')') - buffer + 2];
    }
    fclose(file);
    return '?';
}

int get_nice_value(pid_t pid)
{
    char path[64];
    FILE *fp;
    int nice;
    int dummy;
    char comm[256];
    char state;

    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    fp = fopen(path, "r");
    if (!fp)
        return -1;
    if (fscanf(fp, "%d (%255[^)]) %c", &dummy, comm, &state) != 3){
        fclose(fp);
        return -1;
    }
    for (int i = 0; i < 15; i++)
        fscanf(fp, "%d", &dummy);
    fscanf(fp, "%d", &nice);
    fclose(fp);
    return nice;
}

static void set_process_user(char *name, process_info_t *process)
{
    if (!name) {
        snprintf(process->user, sizeof(process->user), "unknown");
    } else {
        if (strlen(name) > 7)
            snprintf(process->user, sizeof(process->user), "%.7s+", name);
        else
            snprintf(process->user, sizeof(process->user), "%s", name);
    }
}

void init_process_info(process_info_t *process, int pid)
{
    uid_t uid = get_uid_from_pid(pid);
    char *name = get_name_from_uid(uid);
    char pid_str[16];

    snprintf(pid_str, sizeof(pid_str), "%d", pid);
    if (!process)
        return;
    memset(process, 0, sizeof(process_info_t));
    process->pid = pid;
    set_process_user(name, process);
    process->priority = get_priority(process->pid);
    process->nice = get_nice_value(process->pid);
    get_process_memory(pid, &process->virt, &process->res, &process->shr);
    process->state = get_process_state(pid_str);
    get_cpu_time(pid, process->time_str);
    get_process_name(pid, process->command);
    process->cpu_percent = 0;
    process->mem_percent = 0;
}

size_t collect_pids(process_info_t *procs, size_t max)
{
    DIR *dir;
    struct dirent *entry;
    size_t count = 0;

    if (!procs || max == 0)
        return 0;
    dir = opendir("/proc");
    if (!dir)
        return 0;
    entry = readdir(dir);
    while (entry && count < max){
        if (is_number(entry->d_name)){
            init_process_info(&procs[count], atoi(entry->d_name));
            count++;
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return count;
}
