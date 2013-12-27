all: aoe.c
	gcc aoe.c -o aoe -g
gdb: aoe
	gdb -q aoe
