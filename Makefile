# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c11

#Input file
INPUT = inputs/values1.txt
OUTPUT = outputs/recursiveBinary.txt
REF = ref.txt
# Source file
SRCS = sortLinkedList.c
# Output
TARGET = program

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

convert_input: $(INPUT)
	@echo $(INPUT)
	dos2unix $(INPUT)

convert_output: $(OUTPUT)
	dos2unix $(OUTPUT)

check: $(OUTPUT) $(REF)
	@diff -q $(OUTPUT) $(REF) > /dev/null; \
	if [ $$? -eq 0 ]; then \
		echo "Pass"; \
	else \
		echo "Fail"; \
	fi

# Rule to run the program
run: $(TARGET)
	./$(TARGET) $(INPUT)

# Rule to clean generated files
clean:
	rm -f $(TARGET)
