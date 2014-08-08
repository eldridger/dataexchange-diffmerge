#include "Nodes.h"
#include <iostream>
#include <fstream>
#include <string>

void JSON::accept(Visitor * v) {
	v->visit(this);
}

/************************************************************************/
/* Object Constructor                                                   */
/*       <Object> ->   '{'  '}'                                         */
/*                   | '{' < Members > '}'                              */
/************************************************************************/
Object::Object(std::fstream & file) {
	char c = (file >> std::ws).peek();
	if (c == '{') {
		children.push_back(new ValueNode('{'));
		file >> c;
	} else{
		std::cout << "SUMTHIN DUN GOOFED" << std::endl;
	}

	c = (file >> std::ws).peek();

	if (c != '}') { //     '{' <Members>
		children.push_back(new Members(file));
	} //     ELSE '{' '}'

	children.push_back(new ValueNode('}'));
	file >> c;
}

void Object::accept(Visitor * v) {
	v->visit(this);
}


/************************************************************************/
/* Members Constructor                                                  */
/*       <Members> ->   <Pair>                                          */
/*                   |   <Pair>  ',' <Members>                          */
/************************************************************************/
Members::Members(std::fstream & file) {
	char c;

	children.push_back(new Pair(file));
	c = (char)(file >> std::ws).peek();

	if (c == ',') {
		children.push_back(new ValueNode(','));
		file >> c;
		c = (char)(file >> std::ws).peek();
		children.push_back(new Members(file));
	}

}
void Members::accept(Visitor * v) {
	v->visit(this);
}

/************************************************************************/
/* Pair Constructor                                                     */
/*       <Pair> ->    String  ':'   <Value>                             */
/************************************************************************/
Pair::Pair(std::fstream & file) {
	std::string s;
	char c = (char)(file >> std::ws).peek();

	if (c != '"') {
		std::cout << "No Starting \" found! ";
	}
	file >> c;
	c = (char)(file >> std::ws).peek();
	while (c != '"' && file) {
		s += c;
		file >> c;
		c = (char)(file >> std::ws).peek();
	}
	children.push_back(new ValueNode(s));

	file >> c;
	c = (char)(file >> std::ws).peek();
	std::cout << c << std::endl;
	if (c != ':') {
		std::cout << "ERROR: no : found after String Key in Pair";
	}
	else {
		children.push_back(new ValueNode(':'));
		file >> c;
		children.push_back(new Value(file));
	}
}
void Pair::accept(Visitor * v) {
	v->visit(this);
}

/************************************************************************/
/* Array Constructor                                                    */
/*       <Array> ->    '['  ']'                                          */
/*              |     '['   <Elements>   ']'                            */
/************************************************************************/
Array::Array(std::fstream & file) {
	char c = (char)(file >> std::ws).peek();

	if (c != '[') {
		std::cout << "Something is wrong! (Array Const)";
	}
	else {
		children.push_back(new ValueNode('['));
		file >> c;

		c = (char)(file >> std::ws).peek();

		if (c != ']') {
			children.push_back(new Element(file));
		}

		children.push_back(new ValueNode(']'));
		file >> c;
	}
}
void Array::accept(Visitor * v) {
	v->visit(this);
}

/************************************************************************/
/* Element Constructor                                                  */
/*       <Elements> ->    <Value>                                       */
/*                  |     <Value> ',' <Elements>                        */
/************************************************************************/
Element::Element(std::fstream & file) {
	children.push_back(new Value(file));
	char c;
	c = (char)(file >> std::ws).peek();

	if (c == ',') {
		children.push_back(new ValueNode(','));
		file >> c;
		children.push_back(new Element(file));
	}
	
}
void Element::accept(Visitor * v) {
	v->visit(this);
}

/************************************************************************/
/* Value Constructor                                                    */
/*       <Value> ->   String                                            */
/*				|     Number                                            */
/*				|     <Object>                                          */
/*				|     <Array>                                           */
/*				|     true                                              */
/*				|     false                                             */
/*				|     null                                              */
/************************************************************************/
Value::Value(std::fstream & file) {
	char c = (char)(file >> std::ws).peek();
	std::string s;

	switch (c) {
	case '"': //Begin double quote string
		file >> c;
		c = (char)(file >> std::ws).peek();
		while (c != '"') {
			s += c;
			file >> c;
			c = (char)(file >> std::ws).peek();
		}
		file >> c;
		children.push_back(new ValueNode(s));
		break;
	case '{':
		children.push_back(new Object(file));
		break;
	case '[':
		children.push_back(new Array(file));
		break;

	case 'T':
	case 't': //true or True (no quotes)
		s += 't';
		file >> c;
		c = (char)(file >> std::ws).peek();
		while (s != "true") {
			file >> c;
			c = (char)file.peek();
			s += c;
		}
		file >> c;
		children.push_back(new ValueNode(true));
		break;

	case 'F':
	case 'f': //false of False (no quotes)
		s += 'f';
		file >> c;
		c = (char)(file >> std::ws).peek();
		while (s != "false") {
			file >> c;
			c = (char)file.peek();
			s += c;
		}
		file >> c;
		children.push_back(new ValueNode(false));
		break;

	default:
		//Number
		if (isdigit(c)) {
			int num = (c - '0');
			file >> c;
			c = (char)(file >> std::ws).peek();
			while (isdigit(c)) {
				num = (num * 10) + (c - '0'); //multiply by 10 and add new digit
				file >> c;
				c = (char)(file >> std::ws).peek();
			}
			children.push_back(new ValueNode( num ));
		}
		else {
			children.push_back(new ValueNode());
		}

	}
}
void Value::accept(Visitor * v) {
	v->visit(this);
}

ValueNode::ValueNode(char ch) {
	leafVal = LEAFSTRING;
	stringVal += ch;
}

ValueNode::ValueNode(std::string string) {
	leafVal = LEAFSTRING;
	stringVal = string;
}

ValueNode::ValueNode(int number) {
	leafVal = LEAFNUM;
	numVal = number;
}

ValueNode::ValueNode(bool boolValue) {
	leafVal = LEAFBOOL;
	boolVal = boolValue;
}

ValueNode::ValueNode() {
	leafVal = LEAFNULL;
}

void ValueNode::accept(Visitor * v) {
	v->visit(this);
}
