

#include "Writer.h"
#include <vector>
#include <iostream>
#include <string>

void Writer::visit(const ValueNode * leaf) {
	std::string msgStart;
	std::string msgEnd;

	if (leaf->isDiff) {
		msgStart = "**********DIFF START*************";
		msgEnd = "**********DIFF END*************";
	}
	else if (leaf->isMerge) {
		msgStart = "**********MERGE START*************";
		msgEnd = "**********MERGE END*************";
	}


	//std::cout << msgStart << leaf->fullString << std::endl << msgEnd;
	writeTo << leaf->fullString << std::endl;
	//writeTo << msgStart << leaf->fullString << std::endl << msgEnd;
}

void Writer::visit(const Value * value) {
	//std::cout << "Value Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = value->children.begin(); it != value->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Writer::visit(const Element * element) {
	//std::cout << "Element Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = element->children.begin(); it != element->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Writer::visit(const Array * arr) {
	//std::cout << "Array Visited!" << std::endl;
	for (std::vector<Node*>::const_iterator it = arr->children.begin(); it != arr->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Writer::visit(const Pair * pair) {
	//std::cout << "Pair Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = pair->children.begin(); it != pair->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Writer::visit(const Members * members) {
	//std::cout << "Members Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = members->children.begin(); it != members->children.end(); ++it) {
		(*it)->accept(this);
	}
}

void Writer::visit(const Object * object) {
	//std::cout << "Object Visited!" << std::endl;

	for (std::vector<Node*>::const_iterator it = object->children.begin(); it != object->children.end(); ++it) {
		(*it)->accept(this);
	}

}

void Writer::visit(const JSON * json) {
	//std::cout << "JSON Visited!" << std::endl;

	writeTo.open(filename);

	for (std::vector<Node*>::const_iterator it = json->children.begin(); it != json->children.end(); ++it) {
		(*it)->accept(this);
	}

	writeTo.close();
}
