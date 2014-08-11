
#ifndef nodes_h__
#define nodes_h__
#include "Nodes.h"
#endif // nodes_h__

#include <list>

class Merger {
public:
	//JSON *firstFile;
	//JSON *secondFile;
	//JSON *currFile;
	//Merger(JSON*, JSON*);

	Node* merge(const Node * node1, const Node * node2);
	void print(std::list<Node*> printList);
};