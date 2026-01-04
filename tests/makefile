# ==============================================================================
# CHAOSLIB - Tests root Makefile
# ==============================================================================
include ../config.mk

export CFLAGS_CONFIG := -DCHAOS_PTR_WIDTH=$(CHAOS_PTR_WIDTH) \
                        -DCHAOS_ENABLE_ASSERT=$(CHAOS_ENABLE_ASSERT) \
                        -DCHAOS_ENABLE_ALLOC=$(CHAOS_ENABLE_ALLOC) \
                        -DCHAOS_ALLOC_ALIGNMENT=$(CHAOS_ALLOC_ALIGNMENT) \
                        -DCHAOS_ENABLE_FLOAT=$(CHAOS_ENABLE_FLOAT) \
                        -DCHAOS_ENABLE_INT64=$(CHAOS_ENABLE_INT64)

.PHONY: all test-all test-memory test-alloc clean

MODULES := memory string alloc

# Default
all: test-all

# ------------------------------------------------------------------------------

test-all:
	@for mod in $(MODULES); do \
		echo "===== Testing $$mod ====="; \
		$(MAKE) -C $$mod run || exit 1; \
	done

test-memory:
	$(MAKE) -C memory run

test-string:
	$(MAKE) -C string run

test-alloc:
	$(MAKE) -C alloc run
# ------------------------------------------------------------------------------

clean:
	@for mod in $(MODULES); do \
		$(MAKE) -C $$mod clean; \
	done
