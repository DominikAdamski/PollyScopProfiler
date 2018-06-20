BUILD_DIR=build
DATABASE_NAME=scops.db

all:
	echo "Empty makefile"

.PHONY: clean_all

clean_all:
	python3 ClearAll.py --directory $(BUILD_DIR)
