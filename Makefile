BUILD_DIR=build
CFLAGS=-Wall -g -std=c++1y
COMPILER = g++
AR = ar

all: $(BUILD_DIR)/test_db

ARCHIVE_OBJECTS =  $(BUILD_DIR)/DatabaseManager.o\
		   $(BUILD_DIR)/DatabaseHandler.o\
		   $(BUILD_DIR)/DatabaseProxy.o\
		   $(BUILD_DIR)/DatabaseMutex.o

OBJECTS=$(BUILD_DIR)/main.o\
	$(BUILD_DIR)/opt_runtime.o

$(BUILD_DIR)/test_db: $(OBJECTS)
	$(COMPILER) $(OBJECTS) -l sqlite3 -l papi -o $(BUILD_DIR)/test_db

$(BUILD_DIR)/opt_runtime.o: $(ARCHIVE_OBJECTS)
	$(AR) -rv  $@ $^


$(BUILD_DIR)/main.o:  main.cpp DatabaseProxy.h
	$(COMPILER) $(CFLAGS) $< -c -o $@

$(BUILD_DIR)/DatabaseManager.o: DatabaseManager.cpp DatabaseManager.h DatabaseMutex.h
	$(COMPILER) $(CFLAGS) $< -c -o $@

$(BUILD_DIR)/DatabaseHandler.o: DatabaseHandler.cpp DatabaseHandler.h
	$(COMPILER) $(CFLAGS) $< -c -o $@

$(BUILD_DIR)/DatabaseProxy.o: DatabaseProxy.cpp DatabaseManager.h DatabaseProxy.h
	$(COMPILER) $(CFLAGS) $< -c -o $@

$(BUILD_DIR)/DatabaseMutex.o: DatabaseMutex.cpp DatabaseMutex.h
	$(COMPILER) $(CFLAGS) $< -c -o $@

.PHONY: clean

clean:
	rm $(BUILD_DIR)/*.o $(BUILD_DIR)/test_db

.PHONY: clean_all

clean_all:
	python3 ClearAll.py --directory $(BUILD_DIR)
