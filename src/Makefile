NAME =	s21_string.a
FLAGS = -Wall -Wextra -Werror -std=c11
CC = gcc
EXECUTE = exe

SRCS = s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memmove.c s21_memset.c \
	s21_strcat.c s21_strncat.c s21_strchr.c s21_strcmp.c s21_strncmp.c \
	s21_strcpy.c s21_strncpy.c s21_strcspn.c s21_strerror.c s21_strlen.c \
	s21_strpbrk.c s21_strrchr.c s21_strspn.c s21_strstr.c s21_strtok.c s21_sprintf.c \
	s21_to_lower.c s21_to_upper.c s21_insert.c s21_trim.c

OBJS =	$(SRCS:.c=.o)

.PHONY: all clean gcov_report test $(NAME) re

all: gcov_report

gcov_report: test
	$(MAKE) -C ./tests report

test: $(NAME)
	$(MAKE) -C ./tests test

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@rm -f $(OBJS)

define CC_RULE =
$(patsubst %c,%o,$(SOURCE)): $(SOURCE)
 gcc $(FLAGS) -c $< -o $@
endef

$(foreach SOURCE,$(SRCS),$(call $(SOURCE),CC_RULE))

clean:
	$(MAKE) -C ./tests clean
	@rm -f $(NAME)
	@rm -f $(OBJS)

re:	clean all
