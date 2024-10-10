CSRCS += $(notdir $(wildcard $(APP_DIR)/ui/*.c))

DEPPATH += --dep-path $(APP_DIR)/ui

VPATH += :$(APP_DIR)/ui

CFLAGS += "-I$(APP_DIR)/ui"

