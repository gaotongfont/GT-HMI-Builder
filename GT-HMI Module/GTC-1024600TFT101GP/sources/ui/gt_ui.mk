CSRCS += $(notdir $(wildcard $(GT_DIR)/app/ui/*.c))

DEPPATH += --dep-path $(GT_DIR)/app/ui

VPATH += :$(GT_DIR)/app/ui

CFLAGS += "-I$(GT_DIR)/app/ui"

