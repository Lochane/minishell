CC = cc
CFLAGS = -g3 

SRCDIR = src
OBJDIR = obj

SRCS = $(SRCDIR)/minishell.c $(SRCDIR)/utils.c $(SRCDIR)/parsing.c\

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
 

NAME = minishell
LIBPATH = ./libft/libft.a

all: $(NAME)


$(NAME): $(OBJS) | lib
		@echo "			-> Compiling $(NAME)..."
		@$(CC) $(OBJS) $(LIBPATH) -lreadline -o $@
		@echo "			-> Finished $(NAME)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

lib:
	@make -C ./libft

clean:
	@rm -rf $(OBJDIR)
	@make clean -C ./libft

fclean: clean
		@rm -f $(NAME)
		@make fclean -C ./libft

norme:
		norminette $(SRCS)

re: fclean all

.PHONY: all lib clean fclean re norme