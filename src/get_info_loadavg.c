/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

int my_getloadavg(double loadavg[], int nelem)
{
    FILE *file;
    int count = 0;

    if (nelem <= 0 || nelem > 3 || loadavg == NULL)
        return -1;
    file = fopen("/proc/loadavg", "r");
    if (file == NULL)
        return -1;
    for (int i = 0; i < nelem; i++) {
        if (fscanf(file, "%lf", &loadavg[i]) != 1) {
            fclose(file);
            return -1;
        }
        count++;
    }
    fclose(file);
    return 0;
}

int get_user_count(void)
{
    FILE *file;
    struct utmp ut;
    int count = 0;
    size_t result;

    file = fopen("/var/run/utmp", "rb");
    if (file == NULL)
        return 0;
    result = fread(&ut, sizeof(struct utmp), 1, file);
    while (result == 1) {
        if (ut.ut_type == USER_PROCESS)
            count++;
        result = fread(&ut, sizeof(struct utmp), 1, file);
    }
    fclose(file);
    return count;
}

uptime_t get_uptime(void)
{
    FILE *file = fopen("/proc/uptime", "r");
    double uptime_seconds;
    uptime_t up = {0, 0, 0};

    if (file == NULL)
        return up;
    fscanf(file, "%lf", &uptime_seconds);
    fclose(file);
    up.days = uptime_seconds / 86400;
    up.hours = ((int)uptime_seconds % 86400) / 3600;
    up.minutes = ((int)uptime_seconds % 3600) / 60;
    return up;
}
