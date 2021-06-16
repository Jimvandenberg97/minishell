# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jkoopman <jkoopman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 11:23:43 by jkoopman      #+#    #+#                  #
#    Updated: 2020/11/23 13:53:02 by JKCTech       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CLR_GREEN	= \033[0;32m
CLR_CYAN	= \033[0;36m
CLR_RED		= \033[1;31m
CLR_YELLOW	= \033[0;33m
CLR_RESET	= \033[m

STR_OK		= [OK]
STR_FAIL	= [FAIL]

NAME = libft.a
FLAGS = -Wall -Werror -Wextra -I.

SOURCES = ft_atoi.c \
			ft_atol.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_get_next_line.c \
			ft_getnumlen.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_itoa.c \
			ft_lotoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_base.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_split.c \
			ft_str_replace.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_uitoa.c \
			ft_uitohex.c \
			ft_printf/config.c \
			ft_printf/ft_printf.c \
			ft_printf/parser.c \
			ft_printf/print_char.c \
			ft_printf/print_hex.c \
			ft_printf/print_num.c \
			ft_printf/print_pcnt.c \
			ft_printf/print_pointer.c \
			ft_printf/print_string.c \
			ft_printf/print_uint.c \
			ft_printf/printer.c \

HEADER = libft.h

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@printf "%-57b" "$(CLR_CYAN)Building LibFT: $(CLR_RESET)"
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@printf "%b" "$(CLR_GREEN)[OK]\n -- Complete! --\n$(CLR_RESET)"

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
	@printf "%-57b" "$(CLR_RED)Cleaning up binary file: $(CLR_RESET)"
	@$(RM) $(NAME) $(LIBFT)
	@printf "%b" "$(CLR_GREEN)$(STR_OK)\n$(CLR_RESET)"

re: fclean all

.PHONY: all clean fclean re
