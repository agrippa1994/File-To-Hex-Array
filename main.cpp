#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


int main(int argc, char *argv[]) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <file> <header_name> <varname>" << std::endl;
		return 1;
	}

	const std::string file = argv[1];
	const std::string header = argv[2];
	const std::string var = argv[3];

	std::fstream input(file, std::ios_base::in | std::ios_base::binary);
	if (!input.is_open()) {
		std::cerr << "Input file is not readable" << std::endl;
		return 1;
	}

	std::string content((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
	if (content.length() == 0) {
		std::cerr << "Input file has no data" << std::endl;
		return 1;
	}

	std::fstream headerFile(header, std::ios_base::out);
	if (!headerFile.is_open()) {
		std::cerr << "Header file ist not writable" << std::endl;
		return 1;
	}


	headerFile << "#pragma once" << std::endl << std::endl;
	headerFile << " const unsigned char " << var << "[] = {";
	{
		int i = 0;
		for (auto it = content.begin(); it != content.end(); it++, i++) {
			if (i % 10 == 0)
				headerFile << std::endl << "\t";

			headerFile << "0x" << std::hex << (((unsigned int)(*it)) & 0xff);
			if (std::next(it) != content.end())
				headerFile << ",";
		}
	}
	headerFile << std::endl << "};" << std::endl;
	return 0;
}
