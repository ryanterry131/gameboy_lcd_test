BINARY := test
LIBS_PATH := ./libs
MINIFB := $(LIBS_PATH)/libminifb.a

SRCS := main.c
OBJS := $(addprefix build/,$(SRCS:.c=.o))

FRAMEWORKS := $(addprefix -framework ,CoreGraphics AppKit)

CC := clang
LD := $(CC)


build/%.o: %.c
	$(CC) -c $< -o $@

$(BINARY): $(OBJS) $(MINIFB)
	$(LD) $(FRAMEWORKS) -L$(LIBS_PATH) -o $@ $^

clean:
	@rm -rf build
	@mkdir build

redo: clean $(BINARY)