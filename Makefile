SHELL = /bin/sh

CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
LFLAGS = -lcheck -lsubunit -lrt -lpthread -lm

EXE_NAME = test
LIB_NAME = s21_decimal.a

LIB_SRC = $(wildcard lib/*.c)
TEST_SRC = $(wildcard tests/*.c)

LIB_O = $(LIB_SRC:.c=.o)
TEST_O = $(TEST_SRC:.c=.o)

GCOV_NAME = gcov_tests.info

all: clean s21_decimal.a test

s21_decimal.a: $(LIB_O)
	@ar rc $(LIB_NAME) $(LIB_O)
	@ranlib $(LIB_NAME)
	@rm -rf lib/*.o
	@cat tests/worker.txt

test: $(TEST_O) $(LIB_NAME)
	@$(CC) $(CFLAGS) $(TEST_O) -o $(EXE_NAME) -L. -l:$(LIB_NAME) $(LFLAGS)
	@rm -rf $(TEST_O)
	@./$(EXE_NAME)
	@rm $(LIB_NAME)

gcov_report: clean
	$(CC) $(LIB_SRC) $(TEST_SRC) -o $(EXE_NAME) $(LFLAGS) --coverage 
	./$(EXE_NAME)
	lcov -t "gcov_tests" -o $(GCOV_NAME) -c -d .
	genhtml -o report $(GCOV_NAME)
	rm -rf *.gcno *.gcda *.gcov $(GCOV_NAME)

clean:
	rm -f $(LIB_NAME) $(EXE_NAME) ./lib/*.o
	rm -rf ./lib/*.o ./tests/*.o *.gcno *.gcda ./report
	rm -rf $(EXE_NAME)

style_check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n tests/*.c tests/*.h lib/*.c
	rm -rf .clang-format

style_fix:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i tests/*.c lib/*.c
	rm -rf .clang-format

rebuild: clean s21_decimal.a test

valgrind_test: rebuild
	valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all --track-origins=yes -s ./$(EXE_NAME)

cppcheck_test: 
	cppcheck --enable=all --suppress=missingIncludeSystem $(LIB_SRC)