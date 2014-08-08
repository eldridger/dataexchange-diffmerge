
#ifndef parserJSON_h__
#define parserJSON_h__

#include "parserJSON.h"
#endif // parserJSON_h__

#ifndef printer_h__
#define printer_h__

#include "Printer.h"
#endif // printer_h__

#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
	std::fstream file;
	JSON json1;
	JSON json2;
	Printer printer;
	if(argc == 1) {
		std::cout << argv[0] << ": No input files." << std::endl;
	} else if (argc == 3) {
		//for (int i = 1; i < argc; i++) {
			file.open(argv[1], std::fstream::in);
			parse(file, & json1);
			json1.accept(&printer);
			std::cout << std::endl;
			file.close();

			file.open(argv[2], std::fstream::in);
			parse(file, & json2);
			json2.accept(&printer);
			std::cout << std::endl;
			file.close();
		//}
	}
	else {
		std::cout << "Incorrect number of arguments";
	}
}