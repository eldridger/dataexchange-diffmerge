
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
	bool isDiff = false;
	bool isMerge = false;
	bool hasChange = false;
	bool matched = false;
	void setFullString();

	bool isLeaf = false;
	bool canReorder = false;
	std::string fullString;
	std::vector<Node*> children;
	virtual void accept(Visitor * v) = 0;
	virtual Node* clone() const = 0;
	virtual void copy(Node* cop) = 0;
};

typedef enum {
	LEAFSYMBOL,    //NON-String symbol
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
	void copy(Node* cop);
	Node* clone() const;
	void accept(Visitor * v);
	void accept(Visitor * v1, Visitor * v2);
	JSON(std::fstream & file);
};

class Object : public Node {
public:
	void copy(Node* cop);
	Node* clone() const;
	void accept(Visitor * v);
	void accept(Visitor * v1, Visitor * v2);
	Object(std::fstream & file);
};

class Members : public Node {
public:
	void copy(Node* cop);
	Node* clone() const;
	void accept(Visitor * v1, Visitor * v2);
	void accept(Visitor * v);
	Members(std::fstream & file);
};

class Pair : public Node {
public:
	void copy(Node* cop);
	Node* clone() const;
	void accept(Visitor * v1, Visitor * v2);
	void accept(Visitor * v);
	Pair(std::fstream & file);
};

class Array : public Node {
public:
	void copy(Node* cop);
	Node* clone() const;
	void accept(Visitor * v1, Visitor * v2);
	void accept(Visitor * v);
	Array(std::fstream & file);
};

class Element : public Node {
public:
	void copy(Node* cop);
	Node* clone() const;
	void accept(Visitor * v1, Visitor * v2);
	void accept(Visitor * v);
	Element(std::fstream & file);
};

class Value : public Node {
public:
	void copy(Node* cop);
	Node* clone() const;
	void accept(Visitor * v1, Visitor * v2);
	void accept(Visitor * v);
	Value(std::fstream & file);
};

/**
* ValueNode extends Node to accept visitors
*           represents a leaf Node
*/
class ValueNode : public Node {
public:
	void copy(Node* cop);
	Node* clone() const;
	std::string stringVal;
	int numVal;
	bool boolVal;
	LeafValue leafVal;

	/**
	 * ValueNode Char Constructor
	 *    Just converts to string
	 */
	ValueNode(char ch, bool isString = true);

	/**
	* ValueNode String Constructor
	*/
	ValueNode(std::string string, bool isString = true);

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
	void accept(Visitor * v1, Visitor * v2);
	void accept(Visitor * v);
};