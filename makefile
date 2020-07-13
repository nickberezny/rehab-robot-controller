run:
	gcc -Iunity/src/ -Itest -Isrc test/testExample.c src/example.c ./unity/src/unity.c -o TestExample.exe
	./TestExample