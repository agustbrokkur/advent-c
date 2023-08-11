# %.o: %.c $(DEPEND)
# $@ = left side (%.o)
# $^ = right side (%.c $(DEPEND))
# $< = first right side (%.c)

FILES :=  day05.c
OBJECTS := day05.o
#DEPEND =: day01.h

OUTPUT := solution

all: $(OUTPUT)

# Run the compiler on object files, naming the output executable
$(OUTPUT): $(OBJECTS)
	gcc -o $(OUTPUT) $(OBJECTS)

# Create the object files (-c) and define the names (-o)
%.o: %.c 
	gcc -c -o $@ $^

.PHONY: clean

clean:
	rm -f $(OUTPUT) $(OBJECTS)