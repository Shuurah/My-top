/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** main file
*/

#include "my_top.h"

static char *extract_username_from_line(char *line, uid_t uid)
{
    char *token;
    char *username;
    uid_t current_uid;

    username = strtok(line, ":");
    if (username == NULL)
        return NULL;
    strtok(NULL, ":");
    token = strtok(NULL, ":");
    if (token == NULL)
        return NULL;
    current_uid = atoi(token);
    if (current_uid == uid)
        return strdup(username);
    return NULL;
}

char *get_name_from_uid(uid_t uid)
{
    FILE *fp;
    char line[1024];
    char *result;

    fp = fopen("/etc/passwd", "r");
    if (fp == NULL)
        return NULL;
    while (fgets(line, sizeof(line), fp) != NULL) {
        result = extract_username_from_line(line, uid);
        if (result != NULL) {
            fclose(fp);
            return result;
        }
    }
    fclose(fp);
    return NULL;
}

static uid_t parse_uid_from_status(FILE *fp)
{
    char line[256];
    char *token;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Uid:", 4) != 0)
            continue;
        token = strtok(line, "\t ");
        token = strtok(NULL, "\t ");
        return token ? (uid_t)atoi(token) : (uid_t)-1;
    }
    return (uid_t)-1;
}

uid_t get_uid_from_pid(int pid)
{
    char path[64];
    char line[256];
    FILE *fp;
    uid_t uid;

    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    fp = fopen(path, "r");
    if (!fp)
        return (uid_t)-1;
    uid = parse_uid_from_status(fp);
    fclose(fp);
    return uid;
}
