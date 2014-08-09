
#ifndef visitors_h__
#define visitors_h__
#include "Visitors.h"
#endif // visitors_h__

#ifndef nodes_h__
#define nodes_h__
#include "Nodes.h"
#endif // nodes_h__

class Merger : public Visitor {
public:
	//JSON *firstFile;
	//JSON *secondFile;
	//JSON *currFile;
	//Merger(JSON*, JSON*);

	bool isDiff;
	std::vector<Node*> consumed;
	void visit(const ValueNode * leaf);
	void visit(const Value * value);
	void visit(const Element * element);
	void visit(const Array * arr);
	void visit(const Pair * pair);
	void visit(const Members * members);
	void visit(const Object * object);
	void visit(const JSON * json);

	void visit(const ValueNode * leaf1, const ValueNode * leaf2);
	void visit(const Value * value1, const Value * value2);
	void visit(const Element * element1, const Element * element2);
	void visit(const Array * arr1, const Array * arr2);
	void visit(const Pair * pair1, const Pair * pair2);
	void visit(const Members * members1, const Members * members2);
	void visit(const Object * object1, const Object * object2);
	void visit(const JSON * json1, const JSON * json2);
	void merge(const JSON * json1, const JSON * json2);
};