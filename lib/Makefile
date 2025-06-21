NAME = libft.a
SRC_DIR = src
INCLUDES_DIR = inc

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES_DIR)

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
      ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
      ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
      ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
      ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
      ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
      ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_numlen.c \
      ft_puthex_lower_fd.c ft_puthex_upper_fd.c ft_putnbr_unsigned_fd.c \
	  get_next_line.c	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
	  ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
	  ft_lstnew.c ft_lstsize.c ft_strcmp.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(SRCS:.c=.o)

AR = ar rcs
RM = rm -f

GREEN := \033[0;32m
BLUE  := \033[0;34m
RED   := \033[0;31m
RESET := \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)[AR] $(NAME)$(RESET)"
	@$(AR) $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/libft.h
	@echo "$(GREEN)[CC] $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)[CLEAN] object files$(RESET)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "$(RED)[FCLEAN] $(NAME)$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
