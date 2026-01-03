# ==============================================================================
# CHAOSLIB - Tests root Makefile
# ==============================================================================

.PHONY: all test-all test-memory clean

MODULES := memory string

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

# ------------------------------------------------------------------------------

clean:
	@for mod in $(MODULES); do \
		$(MAKE) -C $$mod clean; \
	done
