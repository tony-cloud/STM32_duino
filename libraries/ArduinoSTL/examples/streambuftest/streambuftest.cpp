#include <ArduinoSTL.h>
#include <iostream>
#include <fstream>


void testmain(void)
{
	//We will work on the stream buffer for std::cin
	std::streambuf * buf;
	buf = std::cin.rdbuf();

	int c;

	while ( (c = buf->snextc()) != std::char_traits<char>::eof() ){
		std::cout << "Read in char: " << std::char_traits<char>::to_char_type(c) << std::endl;
	}
}
