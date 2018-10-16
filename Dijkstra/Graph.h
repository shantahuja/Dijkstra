#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include "Vertex.h"

using std::list;
using std::queue;
using std::stack;

template<class V>
void Visit(V data)
{
	std::cout << data << ' ';
};

template <class V, class E>
class Graph : public Arc<V,E>, public Vertex<V,E>
{
private:
	list<Vertex<V, E>> m_vertices;
	int m_count;

	void(*_Visit)(V data) = Visit;
	void DepthFirst(void(*visit)(V data), V startVertex);
	void BreadthFirst(void(*visit)(V data), V startVertex);
public:
	Graph();
	Graph(const Graph<V, E> & copy);
	Graph<V, E> & operator= (const Graph & rhs);
	void SetFunction(void(*func)(V data));
	void InsertVertex(V data);
	void DeleteVertex(V data);
	void InsertArc(V from, V to, Arc<E, V> arc);
	void DeleteArc(V from, V to, Arc<E, V> arc);
	void Purge();
	void SetCount(int count);
	int GetCount();
	list<Vertex<V, E>> GetVertices();
	bool IsEmpty();
	void DepthFirst() { DepthFirst(_Visit, m_vertices.front().getData()); }
	void BreadthFirst() { BreadthFirst(_Visit, m_vertices.front().getData()); }

	void PrintGraph();
	Vertex<V, E>* GetVertex(V data);
};
 // private functions //
template<class V, class E>
inline void Graph<V, E>::DepthFirst(void(*visit)(V data), V startVertex)
{
	stack<Vertex<V, E>> stack1;
	Vertex<V, E> * st_Vertex, *st_Vertex2, *st_Vertex3;

	for (auto iter = m_vertices.begin(); iter != m_vertices.end(); iter++)
	{
		if ((*iter).getData() == startVertex)
		{
			st_Vertex = &*iter;
		}
	}
	stack1.push(*st_Vertex);
	while (!stack1.empty())
	{
		int found = 0;
		st_Vertex2 = &stack1.top();
		list<Arc<V, E>> arcs = st_Vertex2->getArcs();
		for (auto iter = arcs.begin(); iter != arcs.end(); iter++)
		{

			st_Vertex3 = iter->GetDestination();
			stack1.push(*st_Vertex3);
			found = 1;
		}

		if (found > 0)
		{
			if (st_Vertex3->getData() == st_Vertex->getData())
			{
				visit(st_Vertex3->getData());
				while (!stack1.empty())
				{
					stack1.pop();
				}
			}
			else
				visit(st_Vertex3->getData());
		}
	}
}

template<class V, class E>
inline void Graph<V, E>::BreadthFirst(void(*visit)(V data), V startVertex)
{

	queue<Vertex<V, E>> queue1;
	Vertex<V, E> * st_Vertex, *st_Vertex2, *st_Vertex3;
	for (auto iter = m_vertices.begin(); iter != m_vertices.end(); iter++)
	{
		if ((*iter).getData() == startVertex)
		{
			st_Vertex = &*iter;
		}
	}
	queue1.push(*st_Vertex);
	while (!queue1.empty())
	{
		int found = 0;
		st_Vertex2 = &queue1.front();
		V vertex1 = st_Vertex2->getData();
		visit(vertex1);
		list<Arc<V, E>> arcs = st_Vertex2->getArcs();
		queue1.pop();
		for (auto iter2 = arcs.begin(); iter2 != arcs.end(); iter2++)
		{
			st_Vertex3 = iter2->GetDestination();
			queue1.push(*st_Vertex3);
			found = 1;
		}
		if (found > 0)
		{
			if (st_Vertex3->getData() == st_Vertex->getData())
			{
				while (!queue1.empty())
				{
					queue1.pop();
				}
			}
		}
	}
}
//private functions//
template<class V, class E>
inline Graph<V, E>::Graph()
{
}

template<class V, class E>
inline Graph<V, E>::Graph(const Graph<V, E>& copy)
{
	if (!IsEmpty())
	{
		Purge();
	}
	Vertex<V, E> * temp;
	for (auto iter = copy.m_vertices.begin(); iter != copy.m_vertices.end(); iter++)
	{
		V vertex1 = (*iter).getData();
		this->InsertVertex(vertex1);
	}

	for (auto iter = copy.m_vertices.begin(); iter != copy.m_vertices.end(); iter++)
	{
		if ((*iter).getOutDegree() > 0)
		{
			list<Arc<V, E>> arcs = (*iter).getArcs();
			for (auto iter2 = arcs.begin(); iter2 != arcs.end(); iter2++)
			{
				temp = iter2->GetDestination();
				InsertArc(iter->getData(), temp->getData(), *iter2);
			}
		}
	}

	SetCount(copy.m_count);
}

template<class V, class E>
inline Graph<V, E>& Graph<V, E>::operator=(const Graph & rhs)
{
	if (!IsEmpty())
	{
		Purge();
	}

	for (auto iter = rhs.m_vertices.begin(); iter != rhs.m_vertices.end(); iter++)
	{
		InsertVertex((*iter).getData());
	}
	rhs.SetCount(rhs.m_count);
}

template<class V, class E>
inline void Graph<V, E>::SetFunction(void(*func)(V data))
{
	_Visit = func;
}

template<class V, class E>
inline void Graph<V, E>::InsertVertex(V data)
{
	Vertex<V, E> temp(data);
	m_vertices.push_back(temp);
	m_count++;
}

template<class V, class E>
inline void Graph<V, E>::DeleteVertex(V data)
{
	for (auto iter = m_vertices.begin(); iter != m_vertices.end(); iter++)
	{
		if ((*iter).getData() == data)
		{
			while (iter->getOutDegree() > 0 && iter->getInDegree() > 0)
			{
				iter->DeleteArc((*iter).FindArc(*iter));
			}
			m_vertices.erase(iter);
			m_count--;
			return;
		}
	}
}

template<class V, class E>
inline void Graph<V, E>::InsertArc(V from, V to, Arc<E, V> arc)
{
	Vertex<V, E> * fromVertex = nullptr;
	Vertex<V, E> * toVertex = nullptr;

	for (auto iter = m_vertices.begin(); iter != m_vertices.end(); iter++)
	{
		if ((*iter).getData() == from)
		{
			fromVertex = &*iter;
		}
		if ((*iter).getData() == to)
		{
			toVertex = &*iter;
		}
	}
	fromVertex->AddArc(arc);
	fromVertex->IncrementOutDegree();
	toVertex->IncrementInDegree();
}

template<class V, class E>
inline void Graph<V, E>::DeleteArc(V from, V to, Arc<E,V> arc)
{
	Vertex<V, E> * fromVertex;
	Vertex<V, E> * toVertex;

	for (auto iter = m_vertices.begin(); iter != m_vertices.end(); iter++)
	{
		if ((*iter).getData() == from)
		{
			fromVertex = &*iter;
		}
		if ((*iter).getData() == to)
		{
			toVertex = &*iter;
		}
	}

	fromVertex->DeleteArc(arc);
	fromVertex->DecrementOutDegree();
	toVertex->DecrementInDegree();
}

template<class V, class E>
inline void Graph<V, E>::Purge()
{
	m_vertices.clear();
}

template<class V, class E>
inline void Graph<V, E>::SetCount(int count)
{
	m_count = count;
}

template<class V, class E>
inline int Graph<V, E>::GetCount()
{
	return m_count;
}

template<class V, class E>
inline list<Vertex<V, E>> Graph<V, E>::GetVertices()
{
	return m_vertices;
}

template<class V, class E>
inline bool Graph<V, E>::IsEmpty()
{
	return m_vertices.empty();
}

template<class V, class E>
inline void Graph<V, E>::PrintGraph()
{
}

template<class V, class E>
inline Vertex<V, E>* Graph<V, E>::GetVertex(V data)
{
	Vertex<V, E> * vertex = nullptr;
	for (auto iter = m_vertices.begin(); iter != m_vertices.end(); iter++)
	{
		if ((*iter).getData() == data)
		{
			vertex = &*iter;
		}
	}
	return vertex;
}
#endif
