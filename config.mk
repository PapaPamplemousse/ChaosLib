# =============================
# TOOLCHAIN
# =============================
CC              := gcc
AR              := ar
SIZE            := size
OBJDUMP         := objdump
NM              := nm

# =============================
# STANDARD & BUILD TYPE
# =============================
C_STANDARD      := c99
BUILD_TYPE      := release   # debug | release | size | analyze

# =============================
# OPTIMIZATION LEVELS
# =============================
OPT_DEBUG       := -O0 -g3
OPT_RELEASE     := -O2
OPT_SIZE        := -Os
OPT_ANALYZE     := -O0 -g

# =============================
# WARNINGS / MISRA STYLE
# =============================
WARNINGS := \
  -Wall -Wextra -Wpedantic \
  -Wshadow -Wconversion \
  -Wstrict-prototypes \
  -Wmissing-prototypes \
  -Wundef \
  -Wdouble-promotion

# =============================
# CHAOS OPTIONS
# =============================
CHAOS_ENABLE_ASSERT    := 1
CHAOS_ENABLE_ALLOC     := 1
CHAOS_ENABLE_LOG       := 1
CHAOS_ENABLE_FLOAT 	   := 1
CHAOS_ENABLE_INT64     := 1
CHAOS_STRICT_ABI_CHECK := 0
# =============================
# ANALYSIS TOOLS
# =============================
ENABLE_COVERAGE := 0
ENABLE_ASM      := 0
