#include "Nodes.h"
#include <iostream>
#include <fstream>
#include <string>

JSON::JSON(std::fstream & file) {
	char c = (file >> std::ws).peek();

	if (c == '{') {
		children.push_back(new Object(file));
	}
	else if (c == '[') {
		children.push_back(new Array(file));
	}
	else {
		std::cout << "Invalid JSON";
	}

	//Update string based on children
	for (std::vector<Node*>::const_iterator it = children.begin(); it != children.end(); ++it) {
		fullString += (*it)->fullString;
	}
}
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
		children.push_back(new ValueNode('{', false));
		file >> c;
	} else{
		std::cout << "SUMTHIN DUN GOOFED" << std::endl;
	}

	c = (file >> std::ws).peek();

	if (c != '}') { //     '{' <Members>
		children.push_back(new Members(file));
	} //     ELSE '{' '}'

	children.push_back(new ValueNode('}', false));
	file >> c;

	//Update string based on children
	for (std::vector<Node*>::const_iterator it = children.begin(); it != children.end(); ++it) {
		fullString += (*it)->fullString;
	}
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
		children.push_back(new ValueNode(',', false));
		file >> c;
		c = (char)(file >> std::ws).peek();
		children.push_back(new Members(file));
	}

	//Update string based on children
	for (std::vector<Node*>::const_iterator it = children.begin(); it != children.end(); ++it) {
		fullString += (*it)->fullString;
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
		children.push_back(new ValueNode(':', false));
		file >> c;
		children.push_back(new Value(file));
	}

	//Update string based on children
	for (std::vector<Node*>::const_iterator it = children.begin(); it != children.end(); ++it) {
		fullString += (*it)->fullString;
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
		children.push_back(new ValueNode('[', false));
		file >> c;

		c = (char)(file >> std::ws).peek();

		if (c != ']') {
			children.push_back(new Element(file));
		}

		children.push_back(new ValueNode(']', false));
		file >> c;
	}

	//Update string based on children
	for (std::vector<Node*>::const_iterator it = children.begin(); it != children.end(); ++it) {
		fullString += (*it)->fullString;
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
		children.push_back(new ValueNode(',', false));
		file >> c;
		children.push_back(new Element(file));
	}

	//Update string based on children
	for (std::vector<Node*>::const_iterator it = children.begin(); it != children.end(); ++it) {
		fullString += (*it)->fullString;
	}
	
}
void Element::accept(Visitor * v) {
	v->visit(this);
}

/************************************************************************/
/* Value Constructor                                                    */
/*       <Value> ->   String                                            */
/*      	|     Number                                            */
/*		|     <Object>                                          */
/*		|     <Array>                                           */
/*		|     true                                              */
/*		|     false                                             */
/*		|     null                                              */
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

	//Update string based on children
	for (std::vector<Node*>::const_iterator it = children.begin(); it != children.end(); ++it) {
		fullString += (*it)->fullString;
	}
}
void Value::accept(Visitor * v) {
	v->visit(this);
}

ValueNode::ValueNode(char ch, bool isString) {
	std::string s;
	if (isString) {
		leafVal = LEAFSTRING;
		s = '"';
		s += ch;
		s += '"';
	}
	else {
		leafVal = LEAFSYMBOL;
		s = ch;
	}

	fullString += s;
}

ValueNode::ValueNode(std::string string, bool isString) {
	std::string s;
	if (isString) {
		leafVal = LEAFSTRING;
		s = '"';
		s += string;
		s += '"';
	}
	else {
		leafVal = LEAFSYMBOL;
		s = string;
	}
	fullString += s;
}

ValueNode::ValueNode(int number) {
	leafVal = LEAFNUM;
	numVal = number;

	fullString += std::to_string(number);
}

ValueNode::ValueNode(bool boolValue) {
	leafVal = LEAFBOOL;
	boolVal = boolValue;
	if (boolVal) {
		fullString += "true";
	}
	else {
		fullString += "false";
	}
}

ValueNode::ValueNode() {
	leafVal = LEAFNULL;
	fullString += "null";
}

void ValueNode::accept(Visitor * v) {
	v->visit(this);
}
