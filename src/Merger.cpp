
#include <vector>
#include <iostream>
#include <string>
#include "Merger.h"

//merged node, new node
void setFlags(Node* mNode, Node* nNode) {
	//Neither are empty = DIFF
	std::vector<Node*>::iterator it1 = mNode->children.begin();
	std::vector<Node*>::iterator it2 = nNode->children.begin();

	while (it1 != mNode->children.end()) {

		while (it2 != nNode->children.end()) {
			if ((*it1)->isMerge != (*it2)->isMerge) {
				(*it1)->isMerge = (*it2)->isMerge;
				std::cout << "MERGEFLAG: " << (*it1)->fullString << std::endl;
			}
			if ((*it1)->isDiff != (*it2)->isDiff) {
				(*it1)->isDiff = (*it2)->isDiff;
				std::cout << "DIFFFLAG: " << (*it1)->fullString << std::endl;
			}
			if ((*it1)->hasChange != (*it2)->hasChange) {
				(*it1)->hasChange = (*it2)->hasChange;
				std::cout << "CHANGEFLAG: " << (*it1)->fullString << std::endl;
			}

			++it2;
		}
		++it1;
	}

}
Node* Merger::merge(const Node * node1, const Node * node2) {
	Node* mergedNode = node1->clone();
	Node* first = node1->clone();
	Node* second = node2->clone();

	//Copy vector of nodes to lists to avoid iterator invalidation of removing mid-vector
	//std::list<Node*> first;
	//std::copy(node1->children.begin(), node1->children.end(), std::back_inserter(first));
	//std::list<Node*> second;
	//std::copy(node2->children.begin(), node2->children.end(), std::back_inserter(second));
	//std::copy(node1->children.begin(), node1->children.end(), std::back_inserter(mergedNode->children));

	std::cout << "FIRST: " << first->children.size() << std::endl << "SECOND: " << second->children.size() << std::endl;

	if (first->fullString != second->fullString) {

		//std::list<Node*>::iterator it = first.begin();
		//std::list<Node*>::iterator innerIT = second.begin();
		std::vector<Node*>::iterator it = first->children.begin();
		std::vector<Node*>::iterator innerIT = second->children.begin();

		std::cout << std::endl << "COMPARING: " << std::endl;
		std::cout << std::right << first->fullString << std::endl;
		std::cout << std::left << "WITH: " << std::endl;
		std::cout << std::right << second->fullString << std::endl << std::endl << std::endl;

		std::cout << "Children of Node 1..." << std::endl;
		int i = 1;
		while (it != first->children.end()) {
			std::cout << "Child " << i << ": " << (*it)->fullString << std::endl;
			i++;
			it++;
		}
		std::cout << "Children of Node 2..." << std::endl;
		i = 1;
		while (innerIT != second->children.end()) {
			std::cout << "Child " << i << ": " << (*innerIT)->fullString << std::endl;
			i++;
			innerIT++;
		}

		it = first->children.begin();
		innerIT = second->children.begin();

		while (it != first->children.end()) {
			if (innerIT == second->children.end()) {
				innerIT = second->children.begin();
			}

			while (innerIT != second->children.end()) {
				std::string firstString = (*it)->fullString;
				std::string secondString = (*innerIT)->fullString;
				
				if (firstString == secondString) {

					//it = first.erase(it);
					//innerIT = second.erase(innerIT);
					(*it)->matched = true;
					(*innerIT)->matched = true;
					++it;
					++innerIT;
					break;
				}
				else {
					if (innerIT != second->children.end()) ++innerIT;
				}
			}
			if(it != first->children.end()) ++it;
		}

		it = first->children.begin();
		innerIT = second->children.begin();
		int firstSize = first->children.size();
		int secondSize = second->children.size();
		while (it != first->children.end()) {
			if ((*it)->matched) {
				firstSize--;
			}
			++it;
		}
		while (innerIT != second->children.end()) {
			if ((*innerIT)->matched) {
				secondSize--;
			}
			++innerIT;
		}

		std::cout << "Sizes after matching nodes" << std::endl;
		std::cout << "FIRST SIZE: " << firstSize << std::endl << "SECOND SIZE: " << secondSize << std::endl;

		//if (first.empty() && second.empty()) {
		if (firstSize == 0 && secondSize == 0) {
			std::cout << "Nodes are the same! nothing to diff/merge!" << std::endl;
		}
		else if (firstSize == 0) {//   first.empty()) {
			//FIRST EMPTY = ADDITION MERGE

			std::cout << "First is empty!!!" << std::endl;

			std::cout << "BEFORE FIRST EMPTY: " << std::endl;
			std::vector<Node*>::iterator it = second->children.begin();

			unsigned int index = 0;

			while (it != second->children.end()) {
				if (!(*it)->matched) {
					std::cout << (*it)->fullString << " -- ";
					(*it)->isMerge = true;
					(*it)->matched = true;
					second->children.insert(it, new ValueNode("++++", false));
					it = second->children.begin() + ++index;
					++it;
				}
				if(it != second->children.end()) ++it;
			}
			mergedNode = second->clone();
			mergedNode->setFullString();
			//std::cout << "FULLSTRING: " << mergedNode->fullString << std::endl;
		}
		else if (secondSize == 0){// second.empty()) {
			//SECOND EMPTY = REMOVAL MERGE
			std::cout << "Second is empty!!!" << std::endl;
			std::vector<Node*>::iterator it = first->children.begin();
			std::vector<Node*>::iterator secondit = second->children.begin();

			int index = 0;

			//Match remaining nodes in first with node1 and set isMerge to true
			while (it != first->children.end()) {
				if (!(*it)->matched) {
					(*it)->isMerge = true;
					second->children.insert(secondit, new ValueNode("----", false));
					secondit = second->children.begin() + index;
					++secondit;
				}
				if (it != first->children.end()) ++it;
				if (secondit != second->children.end()) ++secondit;
				++index;
			}
			mergedNode = second->clone();
			mergedNode->setFullString();
			std::cout << "FULLSTRING: " << mergedNode->fullString << std::endl;
		}
		else {
			//Neither are empty = DIFF
			std::vector<Node*>::iterator it = first->children.begin();
			std::vector<Node*>::iterator innerIT = second->children.begin();

			while (it != first->children.end()) {
				//std::cout << "GETTING CHANGE FLAG" << (*it)->fullString << std::endl;
				if (!(*it)->matched) (*it)->hasChange = true;

				++it;
			}
			while (innerIT != second->children.end()) {
				//std::cout << "GETTING CHANGE FLAG" << (*innerIT)->fullString << std::endl;
				if (!(*innerIT)->matched) (*innerIT)->hasChange = true;
				++innerIT;
			}
			it = first->children.begin();
			innerIT = second->children.begin();

			//std::cout << "SDFDSADSFDSAFDSAFDSAFDSAFDSAFDSAFDSA: " << std::endl;
			while (it != first->children.end()) {
				//std::cout << "first-- " << (*it)->fullString << std::endl << std::endl;
				if (innerIT == second->children.end()) {
					innerIT = second->children.begin();
				}
				int index = 0;
				while (innerIT != second->children.end()) {
					//std::cout << "second-- " << (*it)->fullString << std::endl << std::endl;
					if (!(*it)->matched && !(*innerIT)->matched) {
						Node* m = merge(*it, *innerIT);
						m->setFullString();
						
						second->children.erase(innerIT);
						innerIT = second->children.begin() + index;
						second->children.insert(innerIT, m);
						innerIT = second->children.begin() + index;
						innerIT++;
						index++;

						second->setFullString();
						std::cout << "merged return-- " << m->fullString << std::endl << std::endl;

					}
					if(innerIT != second->children.end()) ++innerIT;
					++index;
				}
				++it;
			}
			mergedNode = second->clone();
		}
	}
	else {
		std::cout << "Nodes are the same! nothing to diff/merge!" << std::endl;
	}

	return mergedNode;
}

void Merger::print(std::list<Node*> printList) {
	std::cout << "*********** MERGED ***********" << std::endl << std::endl;

	for (std::list<Node*>::const_iterator it = printList.begin(); it != printList.end(); ++it) {
		std::cout << (*it)->fullString << std::endl;
	}
}
