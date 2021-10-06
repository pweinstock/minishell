CC = gcc

NAME = minishell

LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

SDIR = ./srcs/
OBJDIR = ./objs/

CFLAGS = -Wall -Werror -Wextra
OBJECTS = $(OBJDIR)/*.o

DARKBLUE	= \033[0;34m
LIGHTBLUE	= \033[0;36m
GREEN		= \033[0;32m
RED			= \033[0;31m
ORANGE		= \033[0;33m
NO_COLOR	= \033[m

SRC =	./srcs/main.c									\
		./srcs/utils/ft_utils.c							\
		./srcs/utils/ft_utils2.c						\
		./srcs/utils/ft_utils3.c						\
		./srcs/utils/ft_split.c							\
		./srcs/pipex/px.c								\
		./srcs/pipex/px_cmd.c							\
		./srcs/pipex/px_fork.c							\
		./srcs/pipex/px_error.c							\
		./srcs/pipex/px_parse.c							\
		./srcs/builtin/bltin_cd.c						\
		./srcs/builtin/bltin_compare.c					\
		./srcs/builtin/bltin_exit.c						\
		./srcs/builtin/bltin_eastereggs.c				\


all: header $(NAME)

header:
	@printf "%b" "$(DARKBLUE)"
	@echo " ____________________________________________________________________________________________________________________________________________________ "
	@echo "|               _       _     _          _ _     _               _    _     _          _                                    _           _            |"
	@echo "|              (_)     (_)   | |        | | |   | |             | |  | |   (_)        (_)         ___                      (_)         | |           |"
	@echo "|     _ __ ___  _ _ __  _ ___| |__   ___| | |   | |__  _   _    | | _| |__  _ _ __ ___ _  __ _   ( _ )    _ ____      _____ _ _ __  ___| |_ ___      |"
	@echo "|    |  _   _ \| |  _ \| / __|  _ \ / _ \ | |   |  _ \| | | |   | |/ /  _ \| |  __/ __| |/ _  |  / _ \/\ |  _ \ \ /\ / / _ \ |  _ \/ __| __/ _ \     |"
	@echo "|    | | | | | | | | | | \__ \ | | |  __/ | |   | |_) | |_| |   |   <| | | | | |  \__ \ | (_| | | (_>  < | |_) \ V  V /  __/ | | | \__ \ || (_) |    |"
	@echo "|    |_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_|   |_.__/ \__, |   |_|\_\_| |_|_|_|  |___/_|\__, |  \___/\/ | .__/ \_/\_/ \___|_|_| |_|___/\__\___/     |"
	@echo "|                                                       __/ |                             __/ |          | |                                         |"
	@echo "|                                                      |___/                             |___/           |_|                                         |"
	@echo "|____________________________________________________________________________________________________________________________________________________|"
	@printf "%b" "$(LIGHTBLUE)"
	@echo "|                                                                                                                                                    |"

header_end:
	@echo "|____________________________________________________________________________________________________________________________________________________|"

$(NAME): $(OBJECTS)
	@$(CC) $(LFLAGS) $(OBJECTS) -o $(NAME)
	@echo "|                                                             Compiling completed.                                                                   |"
	@make header_end

$(OBJECTS): $(SRC)
	@$(CC) -c $(CFLAGS) $(CPFLAGS) $(SRC)
	@rm -rf ./objs; mkdir ./objs
	@mv *.o $(OBJDIR)
	@echo "|                                                       Object files created and moved.                                                              |"

clean: header
	@rm -f $(OBJECTS) $(D_OBJECTS)
	@rm -rf ./objs ./debug
	@echo "|                                                             Object files cleaned.                                                                  |"
	@make header_end

fclean: header
	@rm -f $(NAME) $(D_NAME)
	@echo "|                                                             Executeable cleaned.                                                                   |"
	@rm -f $(OBJECTS) $(D_OBJECTS)
	@rm -rf ./objs ./debug
	@echo "|                                                             Object files cleaned.                                                                  |"
	@make header_end

re: header
	@rm -f $(NAME) $(D_NAME)
	@echo "|                                                             Executeable cleaned.                                                                   |"
	@rm -f $(OBJECTS) $(D_OBJECTS)
	@rm -rf ./objs ./debug
	@echo "|                                                             Object files cleaned.                                                                  |"
	@make $(NAME)
