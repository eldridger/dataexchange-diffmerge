/*
#ifndef nodes_h__
#define nodes_h__

#include "Nodes.h"
#endif  //nodes_h__
*/

//Forward declarations
class ValueNode;
class Value;
class Element;
class Array;
class Pair;
class Members;
class Object;
class JSON;
class Node;

/**
* Interface that walks through a tree
*/
class Visitor {
public:
	virtual void visit(const ValueNode * leaf) = 0;
	virtual void visit(const Value * value) = 0;
	virtual void visit(const Element * element) = 0;
	virtual void visit(const Array * arr) = 0;
	virtual void visit(const Pair * pair) = 0;
	virtual void visit(const Members * members) = 0;
	virtual void visit(const Object * object) = 0;
	virtual void visit(const JSON * json) = 0;
};