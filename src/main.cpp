
#ifndef parserJSON_h__
#define parserJSON_h__

#include "parserJSON.h"
#endif // parserJSON_h__

#ifndef printer_h__
#define printer_h__

#include "Printer.h"
#endif // printer_h__

#ifndef merger_h__
#define merger_h__

#include "Merger.h"
#endif // merger_h__

#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
	std::fstream file;
	JSON *json1;
	JSON *json2;
	Printer printer;
	Merger merger;
	if(argc == 1) {
		std::cout << argv[0] << ": No input files." << std::endl;
	} else if (argc == 3) {
		//for (int i = 1; i < argc; i++) {
		std::cout << "*************FILE 1*************" << std::endl;
			file.open(argv[1], std::fstream::in);
			json1 = new JSON(file);
			json1->accept(&printer);
			//merger.mergeWith = json1;
			file.close();

			std::cout << "*************FILE 2*************" << std::endl;

			file.open(argv[2], std::fstream::in);
			//parse(file,json2);
			json2 = new JSON(file);
			json2->accept(&printer);

			merger.merge(json1, json2);
			//json2->accept(merger);

			/*
			if (merger->isDiff()) {
				std::cout << "These files are exactly the same!!!" << std::endl;
			}
			else {
				std::cout << "These two files are not the same!!!!!!!!" << std::endl;
			}*/
			std::cout << std::endl;
			file.close();
			std::cout << "*****************DONE*****************" << std::endl << std::endl;
		//}
	}
	else {
		std::cout << "Incorrect number of arguments";
	}
}