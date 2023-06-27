# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsouquie <lsouquie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 16:08:51 by lsouquie          #+#    #+#              #
#    Updated: 2023/03/21 01:06:59 by lsouquie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCFILES = 	$(addprefix src/, ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha \
			ft_isascii ft_isdigit ft_isprint ft_memchr ft_memcmp ft_memcpy \
			ft_memmove ft_memset ft_strchr ft_strdup ft_strlcat ft_strlcpy \
			ft_strlen ft_strncmp ft_strnstr ft_strrchr ft_tolower ft_toupper \
			ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
			ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_lstnew \
			ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone \
			ft_lstclear ft_lstiter ft_lstmap  ft_printf get_next_line get_next_line_utils \
			ft_putnbr_printf ft_putstr_printf ft_putchar_printf ft_make_this_p) \


OBJ = $(addsuffix .o, $(SRCFILES))
OBJ := $(addprefix obj/, $(OBJ))
HEADER = .
CC = cc
FLAGS = -Wall -Werror -Wextra
	
all: $(NAME)


$(NAME): ${OBJFLDR} $(OBJ)
		@echo "			-> Compiling $(NAME)..."
		@ar rcs $(NAME) $(OBJ)
		@echo "			-> Finish $(NAME)"

${OBJFLDR}:
		@mkdir -p .obj/

obj/%.o:	%.c
		@mkdir -p $(dir $@)
		@$(CC) -c $(FLAGS) $< -o $@ -I${HEADER}

clean:
		@rm -rf obj	
fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus