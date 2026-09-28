##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## compile the lib and basic rules
##

CC	= epiclang

CFLAGS = -I include/

EPICLANGFLAGS = -Wall -Wextra -I include/

MEMORYLEAKSFLAGS = -fsanitize=address

MATHFLAGS = -lm 

NCURSESFLAGS = -lncursesw

LDFLAGS = -L. -lcsfml-system -lcsfml-window -lcsfml-graphics

ARG = -o $(NAME)

SRC	= src/main.c \
	src/window_handle.c \
	src/first_window.c \
	src/get_info_loadavg.c \
	src/get_info_processor.c \
	src/second_window.c \
	src/pid_parser.c \
	src/get_name_from_uid.c \
	src/priority_virt.c \
	src/mem_swap_processmem.c \
	src/cpu_mem_time_name.c \
	src/signal_handle.c \

OBJ 	= $(SRC:.c=.o)

NAME	= my_top

SRCBONUS = src/main.c \
	bonus/window_handle.c \
	bonus/first_window.c \
	bonus/box_outline.c \
	src/get_info_loadavg.c \
	src/get_info_processor.c \
	bonus/second_window.c \
	src/pid_parser.c \
	src/get_name_from_uid.c \
	src/priority_virt.c \
	src/mem_swap_processmem.c \
	src/cpu_mem_time_name.c \
	bonus/signal_handle.c \

OBJBONUS = $(SRCBONUS:.c=.o)

all:	compile

compile: $(OBJ)
	@$(CC) $(NCURSESFLAGS) $(CFLAGS) $(OBJ) $(ARG)

debug: $(OBJ)
	@$(CC) $(NCURSESFLAGS) $(EPICLANGFLAGS) $(CFLAGS) $(MEMORYLEAKSFLAGS) $(OBJ) $(ARG) -g

bonus: $(OBJBONUS)
	@$(CC) $(NCURSESFLAGS) $(CFLAGS) $(OBJBONUS) $(ARG)

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJBONUS)

fclean: clean
	@rm -f $(NAME)

.PHONY: fclean all
re: fclean all
