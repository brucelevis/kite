CFLAGS = -s -O0 -Wall -Isrc -Isrc/renderer -Iluaclib -I3rd/include -I3rd/lua
LINK = -L3rd/lib -lglfw3 -lgdi32 -lopengl32

SRC := \
	src/main.c \
	src/game.c \
	src/kite.c \
	src/window.c \
	src/util.c \
	src/renderer.c \

LUACLIB := \
	luaclib/lkite.c \
	luaclib/lwindow.c \
	luaclib/lgraphics.c \
	luaclib/lsprite2d.c \
	luaclib/lmatrix.c \
	luaclib/lprogram.c \



LUASRC := \
	3rd/lua/lapi.c \
	3rd/lua/lauxlib.c \
	3rd/lua/lbaselib.c \
	3rd/lua/lbitlib.c \
	3rd/lua/lcode.c \
	3rd/lua/lcorolib.c \
	3rd/lua/lctype.c \
	3rd/lua/ldblib.c \
	3rd/lua/ldebug.c \
	3rd/lua/ldo.c \
	3rd/lua/ldump.c \
	3rd/lua/lfunc.c \
	3rd/lua/lgc.c \
	3rd/lua/linit.c \
	3rd/lua/liolib.c \
	3rd/lua/llex.c \
	3rd/lua/lmathlib.c \
	3rd/lua/lmem.c \
	3rd/lua/loadlib.c \
	3rd/lua/lobject.c \
	3rd/lua/lopcodes.c \
	3rd/lua/loslib.c \
	3rd/lua/lparser.c \
	3rd/lua/lstate.c \
	3rd/lua/lstring.c \
	3rd/lua/lstrlib.c \
	3rd/lua/ltable.c \
	3rd/lua/ltablib.c \
	3rd/lua/ltm.c \
	3rd/lua/lundump.c \
	3rd/lua/lutf8lib.c \
	3rd/lua/lvm.c \
	3rd/lua/lzio.c


THIRD_PARTY := \
	3rd/src/glad.c \
	# 3rd/src/stb_vorbis.c \


.PHONY : kite


kite:
	gcc $(CFLAGS) $(SRC) $(LUASRC) $(LUACLIB) $(THIRD_PARTY) -o kite.exe $(LINK)