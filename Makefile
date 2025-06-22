NAME = pipex

SRC_DIR = src
INC_DIR = inc
LIB_DIR = lib

SRC_FILES = pipex.c utils.c
SRC_BONUS = parse_bonus.c parse_utils_bonus.c \
			pipex_bonus.c pipex_utils_bonus.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRCS_BONUS = $(addprefix $(SRC_DIR)/, $(SRC_BONUS))

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT = $(LIB_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIB_DIR)

GREEN = \033[0;32m
BLUE  = \033[0;34m
RED   = \033[0;31m
RESET = \033[0m

all: $(NAME)

bonus: fclean $(NAME)_bonus

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)[Building mandatory: $(NAME)]$(RESET)"
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(NAME)_bonus: $(LIBFT) $(OBJS_BONUS)
	@echo "$(GREEN)[Building bonus: $(NAME)]$(RESET)"
	@$(CC) $(OBJS_BONUS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo "$(BLUE)[Building libft]$(RESET)"
	@$(MAKE) -C $(LIB_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(GREEN)[Compiling] $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)[Cleaning object files]$(RESET)"
	@rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@echo "$(RED)[Removing binary: $(NAME)]$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re


