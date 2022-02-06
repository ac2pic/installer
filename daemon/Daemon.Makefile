# Package metadata.
TITLE       := Auto Installer Daemon
VERSION     := 0.01
TITLE_ID    := DAMN00001

AUTH_INFO 	:= 010000000010003800000000001c004000ff00000000008000000000000000000000000000000000000000c000400040000000000000008000000000000000f00040ffff000000f000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

TOOLCHAIN := $(OO_PS4_TOOLCHAIN)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
		CDIR    := linux
endif
ifeq ($(UNAME_S),Darwin)
		CDIR    := macos
endif

all: clean pkg/eboot.bin

pkg/eboot.bin: pkg/sce_sys/param.sfo
	$(TOOLCHAIN)/bin/$(CDIR)/create-fself -eboot=pkg/eboot.bin -in=daemon.elf --paid 0x3800000000000010 --authinfo $(AUTH_INFO)

pkg/sce_sys/param.sfo: Makefile
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_new $@
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ ATTRIBUTE --type Integer --maxsize 4 --value 0  
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ CATEGORY --type Utf8 --maxsize 4 --value 'gdd'  
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ CONTENT_ID --type Utf8 --maxsize 48 --value ''
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ FORMAT --type Utf8 --maxsize 48 --value 'ngh' 
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ TITLE --type Utf8 --maxsize 128 --value '$(TITLE)'
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ TITLE_ID --type Utf8 --maxsize 12 --value '$(TITLE_ID)'
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ VERSION --type Utf8 --maxsize 8 --value '$(VERSION)'

clean:
	rm -f pkg/eboot.bin pkg/sce_sys/param.sfo

