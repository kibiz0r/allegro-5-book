# Simple Makefile for compiling an Allegro 5 game

EXECUTABLE_NAME := my_game

ALLEGRO_LIBS := allegro-5.0 \
	allegro_main-5.0 \
	allegro_image-5.0 \
	allegro_font-5.0 \
	allegro_audio-5.0 \
	allegro_acodec-5.0 \
	allegro_primitives-5.0

# Your compiler may be different
CC := clang
PKG_CONFIG := /opt/local/bin/pkg-config
CFLAGS := -g -Wall -MMD -Iinclude `$(PKG_CONFIG) --cflags $(ALLEGRO_LIBS)`
LIBS := `$(PKG_CONFIG) --libs $(ALLEGRO_LIBS)`

SOURCE_FILES := $(wildcard src/*.c)
OBJECT_FILES := $(patsubst src/%, obj/%, $(SOURCE_FILES:.c=.o))

# The -MMD in CFLAGS generates dependency files, which are Makefile rules
# to detect changed header files
DEPENDENCY_FILES := $(OBJECT_FILES:.o=.d)

$(EXECUTABLE_NAME): $(OBJECT_FILES)
	$(CC) $^ -o $(EXECUTABLE_NAME) $(LIBS)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(EXECUTABLE_NAME)

clean:
	$(RM) -r obj $(EXECUTABLE_NAME)

run: $(EXECUTABLE_NAME)
	./$(EXECUTABLE_NAME)

# Here we load rules to detect changed header files
-include $(DEPENDENCY_FILES)

