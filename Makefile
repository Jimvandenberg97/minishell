# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jkoopman <jkoopman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/29 12:04:22 by jkoopman      #+#    #+#                  #
#    Updated: 2020/12/03 11:29:52 by JKCTech       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CLR_GREEN	= \033[0;32m
CLR_CYAN	= \033[0;36m
CLR_RED		= \033[1;31m
CLR_YELLOW	= \033[0;33m
CLR_RESET	= \033[m

STR_OK		= [OK]
STR_FAIL	= [FAIL]

NAME = minishell
FLAGS = -g -Wall -Werror -Wextra -Ilibft -Isrc/headers
SOURCES = src/main.c \
			src/utils.c \
			src/builtins/builtins.c \
			src/builtins/cd.c \
			src/builtins/echo.c \
			src/builtins/env.c \
			src/builtins/exit.c \
			src/builtins/export.c \
			src/builtins/pwd.c \
			src/environment/env_control.c \
			src/environment/env_init.c \
			src/environment/env_path.c \
			src/environment/env_set.c \
			src/executer/command.c \
			src/executer/debug.c \
			src/executer/executer.c \
			src/executer/fd.c \
			src/executer/fork.c \
			src/executer/redirections.c \
			src/executer/signals.c \
			src/executer/utils.c \
			src/lexer/chars.c \
			src/lexer/elements.c \
			src/lexer/envvar_stepper.c \
			src/lexer/envvar.c \
			src/lexer/lexer_operators.c \
			src/lexer/lexer_strings.c \
			src/lexer/lexer.c \
			src/lexer/slicer.c \
			src/lexer/state.c \
			src/lexer/utils.c \
			src/parser/args.c \
			src/parser/command.c \
			src/parser/debug.c \
			src/parser/parser.c \
			src/parser/tokens.c \
			src/parser/utils.c \
			src/ui/commandline.c \
			src/ui/error.c \
			src/ui/prefix.c

HEADERS	= src/headers/builtins.h \
			src/headers/environment.h \
			src/headers/executer.h \
			src/headers/lexer.h \
			src/headers/messages.h \
			src/headers/minishell.h \
			src/headers/parser.h \
			src/headers/ui.h

CC = clang

LIBFT = libft.a
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@printf "%-64b" "$(CLR_RED)Compiling $(CLR_YELLOW)Minishell: $(CLR_RESET)"
	@$(CC) $(OBJECTS) $(LIBFT) -o $(NAME)
	@printf "%b" "$(CLR_GREEN)$(STR_OK)\n$(CLR_RESET)"
	@printf "%b" "$(CLR_GREEN) -- Complete! --\n"

$(LIBFT):
	@printf "%b" "$(CLR_RED)Yeeting out LibFT...\n$(CLR_RESET)"
	@$(MAKE) -C libft --no-print-directory
	@printf "%b" "$(CLR_RED)Moving LibFT to root...\n$(CLR_RESET)"
	@mv libft/$(LIBFT) .

%.o: %.c $(HEADERS)
	@$(CC) -c $(FLAGS) $< -o $@; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-60b %b" "$(CLR_RED)Compiling$(CLR_CYAN) $<" \
				"$(CLR_RED)$(STR_FAIL)$(CLR_RESET)\n"; \
		else  \
            printf "%-60b %b" "$(CLR_RED)Compiling$(CLR_CYAN) $<" \
				"$(CLR_GREEN)$(STR_OK)$(CLR_RESET)\n"; \
        fi; \
        exit $$RESULT

clean:
	@printf "%-57b" "$(CLR_RED)Cleaning up objects: $(CLR_RESET)"
	@$(RM) $(OBJECTS)
	@printf "%b" "$(CLR_GREEN)$(STR_OK)\n$(CLR_RESET)"

fclean: clean
	@$(MAKE) -C libft fclean --no-print-directory
	@printf "%-57b" "$(CLR_RED)Cleaning up binary file: $(CLR_RESET)"
	@$(RM) $(NAME) $(LIBFT)
	@printf "%b" "$(CLR_GREEN)$(STR_OK)\n$(CLR_RESET)"

re: fclean all

.PHONY: all clean fclean re
