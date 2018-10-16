#ifndef VERTEX_H
#define VERTEX_H
#include <list>
using std::list;

#include "Arc.h"

template <class V, class E>
class Arc;

template <class V, class E>
class Vertex
{
private:
	list<Arc<V, E>> m_arc;
	V m_data;
	int inDegree, outDegree;
	bool m_processed = false;
public:
	Vertex();
	Vertex(V data);
	void AddArc(Arc<E, V> arc);
	void DeleteArc(Arc<E, V> arc);
	Arc<V, E> FindArc(Vertex<V, E> vertex);
	list<Arc<V, E>> getArcs();
	list<Arc<V, E>> getArcs() const;
	V getData();
	V getData() const;	
	int getInDegree();
	int getInDegree() const;
	int getOutDegree();
	int getOutDegree() const;
	void IncrementInDegree();
	void IncrementOutDegree();
	void DecrementInDegree();
	void DecrementOutDegree();
	bool GetProccessed();
	void SetProcessed(bool processed);
};

template<class V, class E>
inline Vertex<V, E>::Vertex()
{	
	inDegree = 0;
	outDegree = 0;
}

template<class V, class E>
inline Vertex<V, E>::Vertex(V data)
{
	m_data = data;
}

template<class V, class E>
inline void Vertex<V, E>::AddArc(Arc<E, V> arc)
{
	m_arc.push_back(arc);
}

template<class V, class E>
inline void Vertex<V, E>::DeleteArc(Arc<E, V> arc)
{
	m_arc.remove(arc);
}

template<class V, class E>
inline Arc<V, E> Vertex<V, E>::FindArc(Vertex<V, E> vertex)
{
	for (auto iter = m_arc.begin(); iter != m_arc.end(); iter++)
	{
		if (iter->GetDestination()->getData() == vertex.getData())
		{
			return *iter;
		}
	}
}

template<class V, class E>
inline list<Arc<V, E>> Vertex<V, E>::getArcs()
{
	return m_arc;
}

template<class V, class E>
inline list<Arc<V, E>> Vertex<V, E>::getArcs() const
{
	return m_arc;
}
template<class V, class E>
inline V Vertex<V, E>::getData()
{
	return m_data;
}

template<class V, class E>
inline V Vertex<V, E>::getData() const
{
	return m_data;
}

template<class V, class E>
inline int Vertex<V, E>::getInDegree()
{
	return inDegree;
}

template<class V, class E>
inline int Vertex<V, E>::getInDegree() const
{
	return inDegree;
}

template<class V, class E>
inline int Vertex<V, E>::getOutDegree()
{
	return outDegree;
}

template<class V, class E>
inline int Vertex<V, E>::getOutDegree() const
{
	return outDegree;
}

template<class V, class E>
inline void Vertex<V, E>::IncrementInDegree()
{
	inDegree++;
}

template<class V, class E>
inline void Vertex<V, E>::IncrementOutDegree()
{
	outDegree++;
}

template<class V, class E>
inline void Vertex<V, E>::DecrementInDegree()
{
	inDegree--;
}

template<class V, class E>
inline void Vertex<V, E>::DecrementOutDegree()
{
	outDegree--;
}

template<class V, class E>
inline bool Vertex<V, E>::GetProccessed()
{
	return m_processed;
}

template<class V, class E>
inline void Vertex<V, E>::SetProcessed(bool processed)
{
	m_processed = processed;
}

#endif // !VERTEX_H
