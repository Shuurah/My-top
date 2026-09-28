/*
** EPITECH PROJECT, 2025
** game.h
** File description:
** header for game
*/

#ifndef MY_TOP_H_
    #define MY_TOP_H_
    #define MAX_PROC 4096
    #include <ncursesw/ncurses.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <locale.h>
    #include <wchar.h>
    #include <time.h>
    #include <utmp.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdarg.h>
    #include <signal.h>
    #include <sys/stat.h>

typedef struct {
    int days;
    int hours;
    int minutes;
} uptime_t;

typedef struct {
    unsigned long long values[8];
    int initialized;
} cpu_snapshot_t;

typedef struct {
    unsigned long total;
    unsigned long free;
    unsigned long available;
    unsigned long buffers;
    unsigned long cached;
    unsigned long swap_total;
    unsigned long swap_free;
} mem_stats_t;

typedef struct {
    double user;
    double system;
    double nice;cpu_snapshot_t cpu_snapshot;
    double idle;
    double iowait;
    double irq;
    double softirq;
    double steal;
} cpu_stats_t;

typedef struct {
    int total;
    int running;
    int sleeping;
    int stopped;
    int zombie;
} task_stats_t;

typedef enum {
    UNIT_KB,
    UNIT_MB,
    UNIT_GB,
    UNIT_TB,
    UNIT_PB,
    UNIT_EB
} memory_unit_t;

typedef struct {
    int pid;
    char user[32];
    int priority;
    int nice;
    unsigned long virt;
    char virt_str[16];
    unsigned long res;
    unsigned long shr;
    char state;
    float cpu_percent;
    float mem_percent;
    char time_str[16];
    char command[256];
} process_info_t;

typedef struct {
    bool is_username;
    bool is_delay;
    bool is_frame;
    char *username;
    double delay;
    int frame;
} program_parameter_t;

typedef struct {
    int selected_proc;
    int first_process_shown;
    int max_process_shown;
    int scroll_offset;
    int all_process_count;
    memory_unit_t memory_unit;
    cpu_snapshot_t cpu_snapshot;
} selection_handle_t;


void set_title(WINDOW *win, int pos_x, char *title);
void second_box_title(WINDOW *win);
void draw_unicode_box(WINDOW *win, int h, int w, char *box_name);
void draw_output(WINDOW *boite, WINDOW *process, int height_first);
void handle_resize(WINDOW **boite, WINDOW **process, int height_first);
void init_window(program_parameter_t *parameter);
void delete_window(WINDOW *boite, WINDOW *process);
void main_loop(program_parameter_t *parameter, selection_handle_t *selected);
void delete_window(WINDOW *boite, WINDOW *process);
void print_first_box(WINDOW *boite, cpu_snapshot_t *snapshot);
void print_second_box(WINDOW *process, selection_handle_t *selected,
    process_info_t processes[MAX_PROC]);
cpu_stats_t get_cpu_stats(cpu_snapshot_t *snapshot);
int is_pid_dir(const char *name);
char get_process_state(const char *pid);
void update_stats_by_state(task_stats_t *stats, char state);
task_stats_t get_task_stats(void);
int my_getloadavg(double loadavg[], int nelem);
int get_user_count(void);
uptime_t get_uptime(void);
void print_bold_int(WINDOW *win, int value);
void print_bold_value(WINDOW *win, const char *format, ...);
void print_header(WINDOW *win);
void init_process_info(process_info_t *process, int pid);
size_t collect_pids(process_info_t *procs, size_t max);
void print_bold_int_padded(WINDOW *win, int value);
char *get_name_from_uid(uid_t uid);
uid_t get_uid_from_pid(int pid);
int get_priority(int pid);
unsigned long get_info_virtual_memory(int pid);
void format_virt_memory(process_info_t *prc, memory_unit_t unit);
void get_process_memory(int pid, unsigned long *virt,
    unsigned long *res, unsigned long *shr);
void print_first_line(WINDOW *win);
void print_second_line(WINDOW *win);
void print_third_line(WINDOW *boite, cpu_snapshot_t *snapshot);
void print_fourth_line(WINDOW *win);
void print_fifth_line(WINDOW *win);
void get_process_name(int pid, char *name);
void get_cpu_time(int pid, char *time_str);
mem_stats_t get_memory_stats(void);
void prompt_kill_process(WINDOW *win, int pid);
#endif
