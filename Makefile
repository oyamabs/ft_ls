CC = cc
# -fno-omit-frame-pointer is to prevent malloc stacktraces from being truncated,
# see "My malloc stacktraces are too short" here:
# https://github.com/google/sanitizers/wiki/AddressSanitizer
SANITIZERS = -fsanitize=address,undefined -fno-omit-frame-pointer
ifeq ($(CFLAGS),)
	CFLAGS = -Wall -Wextra -Werror -g
endif
IFLAGS = -I./libft

SOURCEFILES = \
			  src/main.c \
			  src/arguments/flags.c \
			  src/arguments/arguments.c \
			  src/explore/explore.c \

OBJECTS = $(SOURCEFILES:.c=.o)
NAME = ft_ls
DEPS = $(OBJECTS:.o=.d)

.PHONY: all clean fclean bonus re sane

all: $(OBJECTS) $(NAME)

-include $(DEPS)

$(NAME): $(OBJECTS)
	+$(MAKE) -C libft/
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJECTS) -o $(NAME) -Llibft -lft 

%.o: %.c
	$(CC) -c $(CFLAGS) $(IFLAGS) -o $*.o $*.c
	$(CC) -MM $(CFLAGS) $(IFLAGS) -MT $*.o $*.c > $*.d

clean:
	+make -C libft clean
	find . -name '*.o' -print -delete
	find . -name '*.d' -print -delete

fclean: clean
	+make -C libft fclean
	rm -f $(NAME)

bonus: CFLAGS += -D BONUS=1
bonus: all

bonus-sane: CFLAGS += -D BONUS=1 $(SANITIZERS)
bonus-sane: all

sane: CFLAGS += $(SANITIZERS)
sane: all

re:
	+make fclean
	+make all
