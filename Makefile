
NAME = pipex
NAME_BONUS = pipex_bonux

SRC_DIR = src
INC_DIR = inc
LIB_DIR = lib

SRC_FILES = pipex.c utils.c
SRC_BONUS = parse_bonus.c
			
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRCS_BONUS = $(addprefix $(SRC_DIR)/, $(SRC_BONUS))
OBJS = $(SRCS:.c=.o)

LIBFT = $(LIB_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIB_DIR)

GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(SRCS:.c=.o): %.o: %.c
	@echo "$(GREEN)[Compiling] $<$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(BLUE)[Building libft]$(RESET)"
	$(MAKE) -C $(LIB_DIR)


$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)[Making executable: $(NAME)]$(RESET)"
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(OBJS_BONUS)
	@echo "$(GREEN)[Making bonus executable: $(NAME_BONUS)]$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)[Cleaning object files]$(RESET)"
	rm -f $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@echo "$(RED)[Removing executables]$(RESET)"
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
