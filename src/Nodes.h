
#ifndef visitors_h__
#define visitors_h__

#include "Visitors.h"
#endif // visitors_h__


#include <vector>

/**
* Node class. virtual class that accepts visitors
*/
class Node {
public:
	virtual void accept(Visitor * v) = 0;
};

typedef enum {
	LEAFSTRING,    //String
	LEAFNUM,       //Number
	LEAFBOOL,      //Boolean
	LEAFNULL       //Null
} LeafValue;


/*
	NON-TERMINAL Nodes

<JSON>	->   <Object>
|   <Array>

<Object> ->   '{'  '}'
|    '{'   <Members   '}'

<Members> ->   <Pair>
|   <Pair>  ',' <Members>

<Pair>    ->   String  ':'   <Value>

<Array>   ->   '['  ']'
|   '['   <Elements>   ']'

<Elements> ->   <Value>
|    <Value> ',' <Elements>

*/

class JSON : public Node {
public:
	std::vector<Node*> children;
	void accept(Visitor * v);
};

class Object : public Node {
public:
	std::vector<Node*> children;
	void accept(Visitor * v);
	Object(std::fstream & file);
};

class Members : public Node {
public:
	std::vector<Node*> children;
	void accept(Visitor * v);
	Members(std::fstream & file);
};

class Pair : public Node {
public:
	std::vector<Node*> children;
	void accept(Visitor * v);
	Pair(std::fstream & file);
};

class Array : public Node {
public:
	std::vector<Node*> children;
	void accept(Visitor * v);
	Array(std::fstream & file);
};

class Element : public Node {
public:
	std::vector<Node*> children;
	void accept(Visitor * v);
	Element(std::fstream & file);
};

class Value : public Node {
public:
	std::vector<Node*> children;
	void accept(Visitor * v);
	Value(std::fstream & file);
};

/**
* ValueNode extends Node to accept visitors
*           represents a leaf Node
*/
class ValueNode : public Node {
public:
	std::string stringVal;
	int numVal;
	bool boolVal;
	LeafValue leafVal;

	/**
	 * ValueNode Char Constructor
	 *    Just converts to string
	 */
	ValueNode(char ch);

	/**
	* ValueNode String Constructor
	*/
	ValueNode(std::string string);

	/**
	* ValueNode number Constructor
	*/
	ValueNode(int number);

	/**
	* ValueNode Boolean True Constructor
	*/
	ValueNode(bool boolValue);

	/**
	* ValueNode Null Constructor
	*/
	ValueNode();

	void accept(Visitor * v);
};