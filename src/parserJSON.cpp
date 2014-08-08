/*

GRAMMAR:
	https://code.google.com/p/bsn-goldparser/wiki/JsonGrammar

	<JSON>	->   <Object>
 	         |   <Array>

	<Object> ->   '{'  '}'
	          |    '{'   <Members   '}'

	<Members> ->   <Pair>
	           |   <Pair>  ',' <Members>

	<Pair>    ->   String  ':'   <Value>

	<Array>   ->   '['  ']'
	           |   '['   <Elements>   ']'

	<Elements> ->   <Value>
	           |    <Value> ',' <Elements>

	<Value>    ->   String
	            |   Number
	            |   <Object>
	            |   <Array>
				|   Bool
	            |   null

*/


#include <vector>
#include <iostream>
#include <fstream>
#include "parserJSON.h"

/**
 *  JSON Values
 */

void parse(std::fstream & file, JSON * json) {
	char c = (file >> std::ws).peek();

	if (c == '{') {
		json->children.push_back(new Object(file));
	}
	else if (c == '[') {
		json->children.push_back(new Array(file));
	}
	else {
		std::cout << "Invalid JSON";
	}
}