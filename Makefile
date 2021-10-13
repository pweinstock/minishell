CC = gcc

NAME = minishell

LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

SDIR = ./srcs/
OBJDIR = ./objs/
LIBFT = ./libs/libft/libft.a

CFLAGS = -Wall -Werror -Wextra
OBJECTS = $(OBJDIR)/*.o

DARKBLUE	= \033[0;34m
LIGHTBLUE	= \033[0;36m
GREEN		= \033[0;32m
RED			= \033[0;31m
ORANGE		= \033[0;33m
NO_COLOR	= \033[m

SRC =	./srcs/main.c									\
		./srcs/utils/char_search.c						\
		./srcs/utils/env_utils.c						\
		./srcs/pipex/px.c								\
		./srcs/pipex/px_cmd.c							\
		./srcs/pipex/px_fork.c							\
		./srcs/pipex/px_error.c							\
		./srcs/pipex/px_parse.c							\
		./srcs/builtin/bltin_cd.c						\
		./srcs/builtin/bltin_unset.c					\
		./srcs/builtin/bltin_export.c					\
		./srcs/builtin/bltin_env.c						\
		./srcs/builtin/bltin_pwd.c						\
		./srcs/builtin/bltin_echo.c						\
		./srcs/builtin/bltin_compare.c					\
		./srcs/builtin/bltin_exit.c						\
		./srcs/builtin/bltin_eastereggs.c				\
		./srcs/pweinsto/signals.c						\
		./srcs/pweinsto/redirections.c					\
		./srcs/pweinsto/parsing.c						\


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

$(NAME):
	@make --directory=./libs/libft
	@make $(OBJECTS)
	@$(CC) $(LFLAGS) $(OBJECTS) -o $(NAME) $(LIBFT)
	@echo "|                                                             Compiling completed.                                                                   |"
	@make header_end

$(OBJECTS): $(SRC)
	@$(CC) -c $(CFLAGS) $(CPFLAGS) $(SRC)
	@rm -rf ./objs; mkdir ./objs
	@mv *.o $(OBJDIR)
	@echo
	@echo "|                                                       Object files created and moved.                                                              |"

clean: header
	@make clean --directory=./libs/libft
	@rm -f $(OBJECTS) $(D_OBJECTS)
	@rm -rf ./objs ./debug
	@echo "|                                                             Object files cleaned.                                                                  |"
	@make header_end

fclean: header
	@make fclean --directory=./libs/libft
	@rm -f $(NAME) $(D_NAME)
	@echo "|                                                             Executeable cleaned.                                                                   |"
	@rm -f $(OBJECTS) $(D_OBJECTS)
	@rm -rf ./objs ./debug
	@echo "|                                                             Object files cleaned.                                                                  |"
	@make header_end

re: header
	@make fclean --directory=./libs/libft
	@rm -f $(NAME) $(D_NAME)
	@echo "|                                                             Executeable cleaned.                                                                   |"
	@rm -f $(OBJECTS) $(D_OBJECTS)
	@rm -rf ./objs ./debug
	@echo "|                                                             Object files cleaned.                                                                  |"
	@make $(NAME)
