all:
	gcc -fno-exceptions -fno-rtti -m32 -o sign sign.cpp libipriv.a
	gcc -fno-exceptions -fno-rtti -m32 -o verify verify.cpp libipriv.a