LIBPS4	:= $(PS4SDK)/libPS4

CC		:= gcc
OBJCOPY	:= objcopy
SDIR	:= source
TDIR 	:= release
ODIR	:= $(SDIR)/x64/Debug
IDIRS	:= -I$(LIBPS4)/include -Iinclude
LDIRS	:= -L$(LIBPS4)
MAPFILE := $(ODIR)/$(shell basename "$(CURDIR)").map
CFLAGS	:= $(IDIRS) -Os -std=c11 -ffunction-sections -fdata-sections -fno-builtin -nostartfiles -nostdlib -Wall -Wextra -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=small -fpie -fPIC
LFLAGS	:= $(LDIRS) -Xlinker -T $(LIBPS4)/linker.x -Xlinker -Map="$(MAPFILE)" -Wl,--build-id=none -Wl,--gc-sections
CFILES	:= $(wildcard $(SDIR)/*.c)
SFILES	:= $(wildcard $(SDIR)/*.s)
OBJS	:= $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(CFILES)) $(patsubst $(SDIR)/%.s, $(ODIR)/%.o, $(SFILES))

LIBS	:= -lPS4

TARGET = $(TDIR)/$(shell basename "$(CURDIR)").bin

$(TARGET): clean $(ODIR) $(OBJS)
	$(CC) $(LIBPS4)/crt0.s $(ODIR)/*.o -o temp.t $(CFLAGS) $(LFLAGS) $(LIBS)
	$(OBJCOPY) -O binary temp.t "$(TARGET)"
	rm -f temp.t

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.s
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR):
	@mkdir -p $@

$(ODIR):
	@mkdir -p $@

clean:
	rm -rf "$(TARGET)" "$(MAPFILE)" $(ODIR)