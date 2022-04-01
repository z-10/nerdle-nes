@echo off

set name="nerdle"

set path=%path%;..\cc65\bin\

set CC65_HOME=..\cc65\

mkdir bin
mkdir obj
mkdir words_db
python scripts/build_words_db.py words/support.txt words_db/support_words
python scripts/build_words_db.py words/win.txt words_db/win_words


cc65 -Oirs src/input.c --add-source -o obj/input.s
cc65 -Oirs src/intro.c --add-source -o obj/intro.s
cc65 -Oirs src/game.c --add-source -o obj/game.s
cc65 -Oirs src/main.c --add-source -o obj/main.s
cc65 -Oirs src/palettes.c --add-source -o obj/palettes.s
cc65 -Oirs src/globals.c --add-source -o obj/globals.s

cc65 -Oirs words_db/support_words.c --add-source -o obj/support_words.s
cc65 -Oirs words_db/win_words.c --add-source -o obj/win_words.s


ca65 crt0.s -o obj/crt0.o
ca65 obj/input.s -g -o obj/input.o
ca65 obj/intro.s -g -o obj/intro.o
ca65 obj/game.s -g -o obj/game.o
ca65 obj/main.s -g -o obj/main.o
ca65 obj/palettes.s -g -o obj/palettes.o
ca65 obj/globals.s -g -o obj/globals.o
ca65 obj/support_words.s -g -o obj/support_words.o
ca65 obj/win_words.s -g -o obj/win_words.o


ld65 -C nrom_32k_vert.cfg -o %name%.nes obj/crt0.o obj/input.o obj/intro.o obj/game.o obj/main.o obj/palettes.o  obj/globals.o obj/support_words.o obj/win_words.o nes.lib 

move /Y %name%.nes bin\ 

del obj\*.o
del obj\*.s

