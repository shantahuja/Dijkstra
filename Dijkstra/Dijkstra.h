#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "Graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <stack>
using std::back_inserter;
using namespace std;

class ShortestPath
{
private:
	stack<string> m_direction;
	double m_time;
	int m_distance;
public:
	ShortestPath();
	stack<string> GetDirection();
	double GetTime();
	double GetDistance();
	void SetDirection(stack<string> direction);
	void SetTime(double time);
	void SetDistance(int distance);
};

ShortestPath::ShortestPath()
{
	m_time = 0;
	m_distance = 0;
}

stack<string> ShortestPath::GetDirection()
{
	return m_direction;
}

inline double ShortestPath::GetTime()
{
	return m_time;
}

inline double ShortestPath::GetDistance()
{
	return m_distance;
}

inline void ShortestPath::SetDirection(stack<string> direction)
{
	m_direction = direction;
}

inline void ShortestPath::SetTime(double time)
{
	m_time = time;
}

inline void ShortestPath::SetDistance(int distance)
{
	m_distance = distance;
}


class Dijkstra
{
private:
	Graph<string, string> m_dijkstra;
	template <class Out>
	void m_split(const string & line, char delimiter, Out result);
	vector<string> m_split(const string & line, const char delimiter);
public:
	void CreateGraph(string filename);
	ShortestPath FindShortestPath(string origin, string destination);

};

template <class Out>
inline void Dijkstra::m_split(const string & line, char delimiter, Out result)
{
	stringstream stream;
	stream.str(line);
	string item;
	while (getline(stream, item, delimiter))
	{
		*(result++) = item;
	}
}

inline vector<string> Dijkstra::m_split(const string & line, const char delimiter)
{
	vector<string> elements;
	m_split(line, delimiter, back_inserter(elements));
	return elements;
}


void Dijkstra::CreateGraph(string filename)
{
	ifstream myFile;
	myFile.open(filename);
	string line;
	if (myFile.is_open())
	{
		getline(myFile, line);
		while (!myFile.eof())
		{
			auto strings = m_split(line, ',');
			string start = strings[0];
			string dest = strings[1];
			string arc_data = strings[2];
			int miles = atoi(strings[3].c_str());

			auto start_vertex = m_dijkstra.GetVertex(start);
			auto dest_vertex = m_dijkstra.GetVertex(dest);
			if (!start_vertex)
			{
				m_dijkstra.InsertVertex(start);
				start_vertex = m_dijkstra.GetVertex(start);
			}
			if (!dest_vertex)
			{
				m_dijkstra.InsertVertex(dest);
				dest_vertex = m_dijkstra.GetVertex(dest);
			}

			auto start_to_dest = Arc<string, string>(dest_vertex, miles, arc_data);
			auto dest_to_start = Arc<string, string>(start_vertex, miles, arc_data);
			m_dijkstra.InsertArc(start, dest, start_to_dest);
			m_dijkstra.InsertArc(dest, start, dest_to_start);
			getline(myFile, line);
		}
	}
}

inline ShortestPath Dijkstra::FindShortestPath(string origin, string destination)
{
	int start_index, end_index;
	int min_index = 0;
	int min_distance = -1;
	size_t size = m_dijkstra.GetCount();
	Vertex<string, string> * vertices = new Vertex<string, string>[size];
	int * distances = new int[size] {-1};
	double * time = new double[size];
	int * predecessor = new int[size];
	for (int i = 0; i < size; i++)
	{
		predecessor[i] = -1;
		distances[i] = -1;
	}
	string * roads = new string[size];
	int i = 0;
	for (auto vertex : m_dijkstra.GetVertices())
	{
		vertices[i] = *&vertex;
		i++;
	}

	for (int j = 0; j < size; j++)
	{
		if (vertices[j].getData() == origin)
		{
			start_index = j;
		}
		if (vertices[j].getData() == destination)
		{
			end_index = j;
		}
	}

	time[start_index] = 0;
	distances[start_index] = 0;

	for (int k = 0; k < size && !vertices[end_index].GetProccessed(); k++)
	{
		for (auto vertex = 0; vertex < size; vertex++)
		{
			if (!vertices[vertex].GetProccessed() && distances[vertex] != -1 && (min_distance == -1 || distances[vertex] < min_distance))
			{
				min_distance = distances[vertex];
				min_index = vertex;
			}
		}
		auto arc_list = vertices[min_index].getArcs();
		for (auto arc : arc_list)
		{
			int arc_index = 0;
			for (int j = 0; j < size; j++)
			{
				if (arc.GetDestination()->getData() == vertices[j].getData())
				{
					arc_index = j;
				}
			}
			int total_distance = distances[min_index] + arc.GetWeight();
			if (total_distance < distances[arc_index] || distances[arc_index] == -1)
			{
				distances[arc_index] = total_distance;
				predecessor[arc_index] = min_index;
				roads[arc_index] = arc.GetData();

				if (roads[arc_index] == "I-5")
				{
					time[arc_index] = (time[min_index]) + (arc.GetWeight() / 65.0);
				}
				else
				{
					time[arc_index] = (time[min_index]) + (arc.GetWeight() / 55.0);
				}
			}
		}
		vertices[min_index].SetProcessed(true);
		min_distance = -1;
	}

	int predecessor_index = end_index;
	stack<string> directions;

	while (predecessor_index != -1)
	{
		if (!roads[predecessor_index].empty())
		{
			if (directions.empty())
			{
				directions.push(roads[predecessor_index]);
			}
			else if (roads[predecessor_index] != directions.top())
			{
				directions.push(roads[predecessor_index]);
			}
		}
		predecessor_index = predecessor[predecessor_index];
	}
	ShortestPath shortest_path;
	shortest_path.SetDirection(directions);
	shortest_path.SetTime(time[end_index]);
	shortest_path.SetDistance(distances[end_index]);

	delete[]vertices;
	delete[]distances;
	delete[]time;
	delete[]predecessor;
	delete[]roads;

	return shortest_path;
}


#endif // !DIJKSTRA_H
