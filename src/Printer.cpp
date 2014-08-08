

#include "Printer.h"
#include <vector>
#include <iostream>
#include <string>

void Printer::visit(const ValueNode * leaf) {
	//std::cout << "ValueNode Visited!" << std::endl;

	switch (leaf->leafVal) {
	case LEAFSTRING:
		std::cout << '"' << leaf->stringVal << '"' << std::endl;
		break;
	case LEAFNUM:
		std::cout << leaf->numVal << std::endl;
		break;
	case LEAFBOOL:
		if (leaf->boolVal) {
			std::cout << "true" << std::endl;
		}
		else {
			std::cout << "false" << std::endl;
		}
		break;
	case LEAFNULL:
		std::cout << "NULL" << std::endl;
		break;
	default:
		std::cout << "IDK?" << std::endl;
		break;

	}
}

void Printer::visit(const Value * value) {
	//std::cout << "Value Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = value->children.begin(); it != value->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Printer::visit(const Element * element) {
	//std::cout << "Element Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = element->children.begin(); it != element->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Printer::visit(const Array * arr) {
	//std::cout << "Array Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = arr->children.begin(); it != arr->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Printer::visit(const Pair * pair) {
	//std::cout << "Pair Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = pair->children.begin(); it != pair->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Printer::visit(const Members * members) {
	//std::cout << "Members Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = members->children.begin(); it != members->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Printer::visit(const Object * object) {
	//std::cout << "Object Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = object->children.begin(); it != object->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Printer::visit(const JSON * json) {
	//std::cout << "JSON Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = json->children.begin(); it != json->children.end(); ++it) {
		(*it)->accept(this);
	}
}
