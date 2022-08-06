TESTF =	s21_string_test.check

RUNTEST = test
LIBCHECK_PATH = /usr/local/lib/libcheck.a
LFLAGS += $(shell pkg-config --cflags --libs check)
LIBS21_PATH = ../s21_string.a

.PHONY : clean $(RUNTEST) $(NAME) report re

report: $(RUNTEST)
	../lcov/bin/lcov -t "$(RUNTEST)" -o gcov.info -c -d .
	../lcov/bin/genhtml -o gcov_report gcov.info
	@rm -rf ./*.gc*
	cd gcov_report && xdg-open index.html

$(RUNTEST):
	checkmk clean_mode=1 $(TESTF) > $(RUNTEST).c
	gcc --coverage -g $(RUNTEST).c ../s21_memchr.c ../s21_memcmp.c ../s21_memcpy.c ../s21_memmove.c ../s21_memset.c \
	../s21_strcat.c ../s21_strncat.c ../s21_strchr.c ../s21_strcmp.c \
	../s21_strcpy.c ../s21_strncpy.c ../s21_strcspn.c ../s21_strerror.c ../s21_strlen.c \
	../s21_strpbrk.c ../s21_strrchr.c ../s21_strspn.c ../s21_strstr.c ../s21_strtok.c ../s21_sprintf.c \
	../s21_to_lower.c ../s21_to_upper.c ../s21_insert.c ../s21_trim.c ../s21_strncmp.c $(LFLAGS) -L. $(LIBS21_PATH) -o $(RUNTEST) -lm
	@rm -rf s21_*.gcda
	./$(RUNTEST)

clean:
	@rm -rf *test.o
	@rm -rf *test.gc*
	@rm -rf s21_*.gc*
	@rm -rf *test.c
	@rm -rf $(RUNTEST)
	@rm -rfd gcov_report
	@rm -rf gcov.info
