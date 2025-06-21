
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

all: $(NAME)

$(SRCS:.c=.o): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)


$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

bonus: 
	$(CC) $

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
