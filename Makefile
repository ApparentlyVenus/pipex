NAME = pipex

SRC_DIR = src
INC_DIR = inc
LIB_DIR = lib

SRC_FILES = main.c parse_utils.c parse.c pipex.c utils.c utils2.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

LIBFT = $(LIB_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIB_DIR)

GREEN = \033[0;32m
BLUE  = \033[0;34m
RED   = \033[0;31m
RESET = \033[0m

all: bonus

bonus: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)[Building: $(NAME)]$(RESET)"
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo "$(BLUE)[Building libft]$(RESET)"
	@$(MAKE) -C $(LIB_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(GREEN)[Compiling] $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)[Cleaning object files]$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@echo "$(RED)[Removing binary: $(NAME)]$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re


