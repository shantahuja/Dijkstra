#ifndef ARC_H
#define ARC_H
#include "Vertex.h"

template <class V, class E>
class Vertex;

template <class V, class E>
class Arc
{
private:
	Vertex<V, E> *m_destination;
	int m_weight = 0;
	E m_data;
public:
	Arc<V,E>();
	Arc<V, E>(Vertex<V, E> *destination, int weight, E data);
	Vertex<V, E> *GetDestination();
	int GetWeight();
	E GetData();
	bool operator==(const Arc<V, E>& rhs);
};

template<class V, class E>
inline Arc<V, E>::Arc()
{
	m_destination = 0;
	m_weight = 0;
}

template<class V, class E>
inline Arc<V, E>::Arc(Vertex<V, E>* destination, int weight, E data)
{
	m_destination = destination;
	m_weight = weight;
	m_data = data;
}

template<class V, class E>
inline Vertex<V, E>* Arc<V, E>::GetDestination()
{
	return m_destination;
}

template<class V, class E>
inline int Arc<V, E>::GetWeight()
{
	return m_weight;
}

template<class V, class E>
inline E Arc<V, E>::GetData()
{
	return m_data;
}

template<class V, class E>
inline bool Arc<V, E>::operator==(const Arc<V, E>& rhs)
{
	return (rhs.m_data == this->GetData() &&
		rhs.m_destination == GetDestination() &&
		rhs.m_weight == GetWeight());
}

#endif // !ARC_H
