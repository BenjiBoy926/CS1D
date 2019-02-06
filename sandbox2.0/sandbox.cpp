#include "dyn_arr.h"

int main(int argc, char **argv) {
	dyn_arr<char> array;
	std::string input;

	std::cout << "Input some characters: ";
	getline(std::cin, input);

	for(int i = 0; i < input.size(); i++)
	{
		array.add(input[i]);
	}

	std::cout << "The characters you inputed are: ";
	array.print(std::cout);

	return 0;
}
