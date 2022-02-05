#pragma once
#include "utils.h"
#include "entity.h"
#include "basicBlock.h"
#include "text.h"

struct Point
{
	int x{};
	int y{};
};

// The objects that we want stored in the quadtree
struct Node
{
	Point pos;
	Node(const Point& _pos)
	{
		pos = _pos;
	}
};

// The main quadtree class
class QuadTree
{
	// Hold details of the boundary of this node
	Point m_botLeft{ 0,0 };
	Point m_topRight{ 0,0 };

	// Contains details of node
	Node* m_node{};

	// Children of this tree
	QuadTree* m_topLeftTree{};
	QuadTree* m_topRightTree{};
	QuadTree* m_botLeftTree{};
	QuadTree* m_botRightTree{};

public:
	~QuadTree();
	QuadTree(const QuadTree& quadTree) = delete;
	QuadTree& operator=(const QuadTree& quadTree) = delete;
	QuadTree(const Point& botLeft, const Point& topRight, const int& maxCellSize) : m_botLeft{ botLeft }, m_topRight{ topRight }{}

	//void insert(Node*);
	bool inBoundary(const Point&);
	Node* search(const Point&);

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};


