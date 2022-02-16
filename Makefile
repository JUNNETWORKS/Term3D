NAME = term3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g -fsanitize=address

LIBFT_PATH = libft
LIBFT_MAKE = $(MAKE) -C $(LIBFT_PATH)
LIBFT_LIB = -L./libft -lft

INCLUDES = -I./libft
LDFLAGS = $(LIBFT_LIB)

SRCS = main.c file_reader.c renderer.c terminal_info.c

OBJ_DIR = objs
OBJECTS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPENDENCIES = $(OBJECTS:.o=.d)

.PHONY: all
all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -MMD -o $@

-include $(DEPENDENCIES)

$(NAME): $(OBJECTS)
	$(LIBFT_MAKE)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJECTS) $(LDFLAGS)

.PHONY: clean
clean:
	$(LIBFT_MAKE) clean
	$(RM) $(OBJECTS)

.PHONY: fclean
fclean: clean
	$(LIBFT_MAKE) fclean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
