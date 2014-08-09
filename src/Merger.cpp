#include <vector>
#include <iostream>
#include <string>
#include <list>
#include "Merger.h"

/*
Merger::Merger(JSON * first, JSON * second) {
	this->firstFile = first;
	this->secondFile = second;

	this->firstFile->accept(this);
	this->secondFile->accept(this);
}*/

void Merger::visit(const ValueNode * leaf) {

}

void Merger::visit(const Value * value) {

	for (std::vector<Node*>::const_iterator it = value->children.begin(); it != value->children.end(); ++it) {
		(*it)->accept(this);
	}

}

void Merger::visit(const Element * element) {

	for (std::vector<Node*>::const_iterator it = element->children.begin(); it != element->children.end(); ++it) {
		(*it)->accept(this);
	}

}

void Merger::visit(const Array * arr) {

	for (std::vector<Node*>::const_iterator it = arr->children.begin(); it != arr->children.end(); ++it) {
		(*it)->accept(this);
	}

}

void Merger::visit(const Pair * pair) {
	for (std::vector<Node*>::const_iterator it = pair->children.begin(); it != pair->children.end(); ++it) {
		(*it)->accept(this);
	}

}

void Merger::visit(const Members * members) {

	for (std::vector<Node*>::const_iterator it = members->children.begin(); it != members->children.end(); ++it) {
		(*it)->accept(this);
	}

}

void Merger::visit(const Object * object) {
	for (std::vector<Node*>::const_iterator it = object->children.begin(); it != object->children.end(); ++it) {
		(*it)->accept(this);
	}

}

void Merger::visit(const JSON * json1) {

	for (std::vector<Node*>::const_iterator it = json1->children.begin(); it != json1->children.end(); ++it) {
		(*it)->accept(this);
	}

}


void Merger::visit(const ValueNode * leaf1, const ValueNode * leaf2) {

}

void Merger::visit(const Value * value1, const Value * value2) {

}

void Merger::visit(const Element * element1, const Element * element2) {

}

void Merger::visit(const Array * arr1, const Array * arr2) {

}

void Merger::visit(const Pair * pair1, const Pair * pair2) {

}

void Merger::visit(const Members * members1, const Members * members2) {

}

void Merger::visit(const Object * object1, const Object * object2) {

}

void Merger::visit(const JSON * json1, const JSON * json2) {
}


void Merger::merge(const Node * node1, const Node * node2) {
	//Copy vector of nodes to lists to avoid iterator invalidation of removing mid-vector
	std::list<Node*> first;
	std::copy(node1->children.begin(), node1->children.end(), std::back_inserter(first));
	std::list<Node*> second;
	std::copy(node2->children.begin(), node2->children.end(), std::back_inserter(second));

	std::vector<Node*> merged;

	if (node1->fullString != node2->fullString) {

		std::list<Node*>::const_iterator it = first.begin();
		std::list<Node*>::const_iterator innerIT = second.begin();

		do {
			do {

				std::cout << "FIRST STRING: " << std::endl;
				std::cout << std::right << (*it)->fullString << std::endl;
				std::cout << std::left << "SECOND STRING: " << std::endl;
				std::cout << std::right << (*innerIT)->fullString << std::endl;

				if ((*it)->fullString == (*innerIT)->fullString) {
					merged.push_back(*it);

					it = first.erase(it);
					innerIT = second.erase(innerIT);
				}
				else {
					++innerIT;
				}
			} while (innerIT != second.end());
			++it;
		} while (it != first.end());

		std::cout << "FIRST SIZE: " << first.size() << std::endl << "SECOND SIZE: " << second.size() << std::endl;
		if (first.empty() && second.empty()) {
			std::cout << "Files are the same! nothing to diff/merge!";
		}
		else {

		}
	}
	else {
		std::cout << "Files are the same! nothing to diff/merge!";
	}
}
