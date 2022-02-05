#include "quadTree.h"

QuadTree::QuadTree(const Point& botLeft, const Point& topRight, const int& maxCellSize) :m_botLeft{ botLeft },
m_topRight{ topRight } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::quadTree_cpp, &mS_objectsCount);
#endif

	if (node == NULL)
		return;

	// Current quad cannot contain it
	if (!inBoundary(node->pos))
		return;

	// We are at a quad of unit area
	// We cannot subdivide this quad further
	if (abs(m_topRight.x - m_botLeft.x) <= 1 &&
		abs(m_topRight.y - m_botLeft.y) <= 1)
	{
		if (m_node == NULL)
			m_node = node;
		return;
	}

	// indicatest left
	if ((m_botLeft.x + m_topRight.x) / 2 >= node->pos.x)
	{
		// Indicates bot
		if ((m_botLeft.y + m_topRight.y) / 2 >= node->pos.y)
		{
			if (m_botLeftTree == NULL)
				m_botLeftTree = new QuadTree{
				m_botLeft, Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}
			};

			m_botLeftTree->insert(node);
		}
		// Indicates top
		else
		{
			if (m_topLeftTree == NULL)
				m_topLeftTree = new QuadTree{
				Point{m_botLeft.x, (m_botLeft.y + m_topRight.y) / 2 },
				Point{(m_botLeft.x + m_topRight.x) / 2, m_topRight.y}
			};
			m_topLeftTree->insert(node);
		}
	}
	// indicates right
	else
	{
		// Indicates bot
		if ((m_botLeft.y + m_topRight.y) / 2 >= node->pos.y)
		{
			if (m_botRightTree == NULL)
				m_botRightTree = new QuadTree{
				Point{(m_botLeft.x + m_topRight.x) / 2, m_botLeft.y },
				Point{m_botLeft.x + m_topRight.x, (m_botLeft.y + m_topRight.y) / 2}
			};
			m_botRightTree->insert(node);
		}

		// Indicates top
		else
		{
			if (m_topRightTree == NULL)
				m_topRightTree = new QuadTree{
				Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, m_topRight
			};
			m_topRightTree->insert(node);
		}
	}
}

QuadTree::~QuadTree() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::quadTree_cpp);
	delete m_botLeftTree;
	delete m_botRightTree;
	delete m_topLeftTree;
	delete m_topRightTree;
#endif
}

// Insert a node into the quadtree
//void QuadTree::insert(Node* node)
{
	if (node == NULL)
		return;

	// Current quad cannot contain it
	if (!inBoundary(node->pos))
		return;

	// We are at a quad of unit area
	// We cannot subdivide this quad further
	if (abs(m_topRight.x - m_botLeft.x) <= 1 &&
		abs(m_topRight.y - m_botLeft.y) <= 1)
	{
		if (m_node == NULL)
			m_node = node;
		return;
	}

	// indicatest left
	if ((m_botLeft.x + m_topRight.x) / 2 >= node->pos.x)
	{
		// Indicates bot
		if ((m_botLeft.y + m_topRight.y) / 2 >= node->pos.y)
		{
			if (m_botLeftTree == NULL)
				m_botLeftTree = new QuadTree{
				m_botLeft, Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}
			};

			m_botLeftTree->insert(node);
		}
		// Indicates top
		else
		{
			if (m_topLeftTree == NULL)
				m_topLeftTree = new QuadTree{
				Point{m_botLeft.x, (m_botLeft.y + m_topRight.y) / 2 },
				Point{(m_botLeft.x + m_topRight.x) / 2, m_topRight.y}
			};
			m_topLeftTree->insert(node);
		}
	}
	// indicates right
	else
	{
		// Indicates bot
		if ((m_botLeft.y + m_topRight.y) / 2 >= node->pos.y)
		{
			if (m_botRightTree == NULL)
				m_botRightTree = new QuadTree{
				Point{(m_botLeft.x + m_topRight.x) / 2, m_botLeft.y },
				Point{m_botLeft.x + m_topRight.x, (m_botLeft.y + m_topRight.y) / 2}
			};
			m_botRightTree->insert(node);
		}

		// Indicates top
		else
		{
			if (m_topRightTree == NULL)
				m_topRightTree = new QuadTree{
				Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, m_topRight
			};
			m_topRightTree->insert(node);
		}
	}
}

bool QuadTree::inBoundary(const Point& p)
{
	return (p.x >= m_botLeft.x && p.x <= m_topRight.x &&
		p.y >= m_botLeft.y && p.y <= m_topRight.y);
}


Node* QuadTree::search(const Point& p)
{
	// Current quad cannot contain it
	if (!inBoundary(p))
		return NULL;

	// We are at a quad of unit length
	// We cannot subdivide this quad further
	if (m_node != NULL)
		return m_node;

	// indicates left
	if ((m_botLeft.x + m_topRight.x) / 2 >= p.x)
	{
		// Indicates bot
		if ((m_botLeft.y + m_topRight.y) / 2 >= p.y)
		{
			if (m_botLeftTree == NULL)
				return NULL;
			return m_botLeftTree->search(p);
		}

		// Indicates top
		else
		{
			if (m_topLeftTree == NULL)
				return NULL;
			return m_topLeftTree->search(p);
		}
	}
	// indicates right
	else
	{
		// Indicates bot
		if ((m_botLeft.y + m_topRight.y) / 2 >= p.y)
		{
			if (m_botRightTree == NULL)
				return NULL;
			return m_botRightTree->search(p);
		}

		// Indicates top
		else
		{
			if (m_topRightTree == NULL)
				return NULL;
			return m_topRightTree->search(p);
		}
	}
	return nullptr;
};