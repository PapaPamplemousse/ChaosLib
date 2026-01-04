# ==============================================================================
# CHAOSLIB - Memory module tests
# ==============================================================================

CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -g

CHAOS_ROOT := ../..
TEST_ROOT  := ..

LIB_DIR := $(CHAOS_ROOT)/build/lib
LIBS    := -L$(LIB_DIR) -lchaoslib

INC_FLAGS := \
    -I$(CHAOS_ROOT)/chaos_core/inc \
    -I$(CHAOS_ROOT)/chaos_types/inc \
    -I$(CHAOS_ROOT)/chaos_memory/inc \
    -I$(CHAOS_ROOT)/chaos_string/inc \
    -I$(CHAOS_ROOT)/chaos_alloc/inc \
    -I$(CHAOS_ROOT)/chaos_math/inc \
    -I$(CHAOS_ROOT)/chaos_stdlib/inc \
    -I$(TEST_ROOT)

# ------------------------------------------------------------------------------

TEST_SRCS := strlen.c strcpy.c strcat.c strcmp.c strstr.c
TEST_BINS := $(TEST_SRCS:.c=)

# ------------------------------------------------------------------------------

.PHONY: all clean run

all: $(TEST_BINS)

%: %.c
	@echo "Building test $@"
	$(CC) $(CFLAGS) $(CFLAGS_CONFIG) $(INC_FLAGS) $< $(LIBS) -o $@

run: all
	@for test in $(TEST_BINS); do \
		echo "---- Running $$test ----"; \
		./$$test || exit 1; \
	done

clean:
	rm -f $(TEST_BINS)
# ------------------------------------------------------------------------------
