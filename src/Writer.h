
#ifndef visitors_h__
#define visitors_h__
#include "Visitors.h"
#endif // visitors_h__

#ifndef nodes_h__
#define nodes_h__
#include "Nodes.h"
#endif // nodes_h__

#include <fstream>

class Writer : public Visitor {
public:
	std::string filename = "../bin/mergedJSON.json";
	std::ofstream writeTo;
	void visit(const ValueNode * leaf);
	void visit(const Value * value);
	void visit(const Element * element);
	void visit(const Array * arr);
	void visit(const Pair * pair);
	void visit(const Members * members);
	void visit(const Object * object);
	void visit(const JSON * json);
};
