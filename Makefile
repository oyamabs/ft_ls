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
			  src/utils.c \
			  src/free.c \
			  src/sort.c \
			  src/print.c \
			  src/arguments/flags.c \
			  src/arguments/arguments.c \
			  src/explore/explore.c \

OBJECTS = $(SOURCEFILES:.c=.o)
NAME = ft_ls
DEPS = $(OBJECTS:.o=.d)

.PHONY: all clean fclean bonus re sane test_all test_single test_multiple test_l

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

DEBUG_FT   = debug_ft.out
DEBUG_REAL = debug_real.out

test_all: test_single test_multiple

test_single: $(NAME)
	@echo "🐛 Test single_file"
	@echo "----------------------------------------------------"
	
	@./$(NAME) /sgoinfre/goinfre/Perso/tchampio/Public/usr/bin/kitty > $(DEBUG_FT) 2>&1
	
	@ls -la /sgoinfre/goinfre/Perso/tchampio/Public/usr/bin/kitty > $(DEBUG_REAL) 2>&1
	
	@if diff $(DEBUG_FT) $(DEBUG_REAL) > /dev/null; then \
		echo "✅ Test OK"; \
	else \
		echo "❌ TEST KO ! Left: my output. Right: expected output) :"; \
		echo "----------------------------------------------------"; \
		diff -y --suppress-common-lines $(DEBUG_FT) $(DEBUG_REAL) || true; \
		echo "----------------------------------------------------"; \
	fi

	@echo "\n🔬 Checking valgrind..."
	@valgrind --leak-check=full --errors-for-leak-kinds=all ./$(NAME) /sgoinfre/goinfre/Perso/tchampio/Public/usr/bin/kitty > /dev/null 2> valgrind.log
	@if grep -q "ERROR SUMMARY: 0 errors" valgrind.log; then \
		echo "✅ No leak!"; \
	else \
		echo "⚠️ LEAK Detected! (check valgrind.log)"; \
		grep "ERROR SUMMARY" valgrind.log || true; \
		grep "definitely lost" valgrind.log || true; \
	fi
	
	@rm -f $(DEBUG_FT) $(DEBUG_REAL) valgrind.log

test_multiple: $(NAME)
	@echo "🐛 Test multiple_file"
	@echo "----------------------------------------------------"
	
	@./$(NAME) /sgoinfre/goinfre/Perso/tchampio/Public/usr/bin/kitty ./src/main.c > $(DEBUG_FT) 2>&1
	
	@ls -la /sgoinfre/goinfre/Perso/tchampio/Public/usr/bin/kitty ./src/main.c > $(DEBUG_REAL) 2>&1
	
	@if diff $(DEBUG_FT) $(DEBUG_REAL) > /dev/null; then \
		echo "✅ Test OK"; \
	else \
		echo "❌ TEST KO ! Left: my output. Right: expected output) :"; \
		echo "----------------------------------------------------"; \
		diff -y --suppress-common-lines $(DEBUG_FT) $(DEBUG_REAL) || true; \
		echo "----------------------------------------------------"; \
	fi

	@echo "\n🔬 Checking valgrind..."
	@valgrind --leak-check=full --errors-for-leak-kinds=all ./$(NAME) /sgoinfre/goinfre/Perso/tchampio/Public/usr/bin/kitty ./src/main.c > /dev/null 2> valgrind.log
	@if grep -q "ERROR SUMMARY: 0 errors" valgrind.log; then \
		echo "✅ No leak!"; \
	else \
		echo "⚠️ LEAK Detected! (check valgrind.log)"; \
		grep "ERROR SUMMARY" valgrind.log || true; \
		grep "definitely lost" valgrind.log || true; \
	fi
	
	@rm -f $(DEBUG_FT) $(DEBUG_REAL) valgrind.log

