all:
	gcc -fno-exceptions -fno-rtti -m32 -o sign sign.cpp libipriv.a
	gcc -fno-exceptions -fno-rtti -m32 -o sign sign.cpp libipriv.a
	./test.sh