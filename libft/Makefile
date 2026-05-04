CC=cc
CFLAGS=-Wall -Wextra -Werror -c 
SOURCEFILES=src/str/ft_atoi.c src/mem/ft_bzero.c src/mem/ft_calloc.c src/cond/ft_isalnum.c \
	    src/cond/ft_isalpha.c src/cond/ft_isascii.c src/cond/ft_isdigit.c \
	    src/cond/ft_isprint.c src/str/ft_itoa.c src/lst/ft_lstadd_back_bonus.c \
	    src/lst/ft_lstadd_front_bonus.c src/lst/ft_lstclear_bonus.c \
	    src/lst/ft_lstdelone_bonus.c src/lst/ft_lstiter_bonus.c \
	    src/lst/ft_lstlast_bonus.c src/lst/ft_lstmap_bonus.c \
	    src/lst/ft_lstnew_bonus.c src/lst/ft_lstsize_bonus.c src/mem/ft_memchr.c \
	    src/mem/ft_memcmp.c src/mem/ft_memcpy.c src/mem/ft_memmove.c src/mem/ft_memset.c \
	    src/printf/ft_printf.c src/io/ft_putchar_fd.c src/io/ft_putendl_fd.c \
	    src/io/ft_putnbr_fd.c src/io/ft_putstr_fd.c src/str/ft_split.c \
	    src/str/ft_strchr.c src/str/ft_strdup.c src/str/ft_striteri.c \
	    src/str/ft_strjoin.c src/str/ft_strlcat.c src/str/ft_strlcpy.c \
	    src/str/ft_strlen.c src/str/ft_strmapi.c src/str/ft_strncmp.c \
	    src/str/ft_strnstr.c src/str/ft_strrchr.c src/str/ft_strtrim.c \
	    src/str/ft_substr.c src/str/ft_tolower.c src/str/ft_toupper.c \
	    src/gnl/get_next_line.c src/gnl/get_next_line_utils.c src/printf/printhex.c \
	    src/printf/printnumbers.c src/printf/printptr.c
OBJECTS=$(patsubst src/%.c,objects/%.o,$(SOURCEFILES))
OBJDIR=objects
NAME=libft.a

all: $(OBJECTS) $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs libft.a $(OBJECTS)

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
