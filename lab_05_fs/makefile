CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -I ./inc -Wvla

CFILES_DIR := ./src
CFILES := $(wildcard $(CFILES_DIR)/*.c)

INC_DIR := ./inc
INCLUDES := $(wildcard $(INC_DIR)/*.h)

OBJ_DIR := ./out
OBJECTS := $(CFILES:$(CFILES_DIR)/%.c=$(OBJ_DIR)/%.o)

UNIT_DIR := ./unit_tests
UNITS := $(wildcard $(UNIT_DIR)/*.c)

UNIT_OBJECTS := $(UNITS:$(UNIT_DIR)/%.c=$(OBJ_DIR)/%.o)
UNIT_OBJECTS += $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS))

APP := app.exe
UNIT_TEST := unit_tests.exe



$(APP): $(OBJECTS)
	@$(CC) $^ -o $@

$(UNIT_TEST): $(UNIT_OBJECTS)
	@$(CC) $^ -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(CFILES_DIR)/%.c $(INCLUDES) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UNIT_DIR)/%.c $(INCLUDES) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/releaseflag: | $(OBJ_DIR)
	@rm -rf *.exe $(OBJ_DIR)/*.o $(OBJ_DIR)/debugflag
	@touch $(OBJ_DIR)/releaseflag

$(OBJ_DIR)/debugflag: | $(OBJ_DIR)
	@rm -rf *.exe $(OBJ_DIR)/*.o $(OBJ_DIR)/releaseflag
	@touch $(OBJ_DIR)/debugflag



.PHONY : release debug unit clean valgrind collect_coverage func_tests

release: CFLAGS += -O2 -g
release: $(OBJ_DIR)/releaseflag $(APP)
	
debug: CFLAGS += -O0 -ggdb -g3
debug: $(OBJ_DIR)/debugflag $(APP)

clean:
	@rm -rf $(OBJ_DIR) $(APP) $(UNIT_TEST) ./r ./d

