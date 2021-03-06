#include "stdafx.h"
#include "CrtDbg.h"
#include <iostream>
#include "Graph.h"
#include "Dijkstra.h"

#define _CRTDBG_MAP_ALLOC

//void TestCopyConstructor();

int main()
{

	{
		//TestCopyConstructor();
		string filename = R"(C:\Users\shant\Desktop\Dijkstra\Dijkstra\Lab_04.txt)";
		Dijkstra dijkstra;
		ShortestPath shortest_path;
		string origin, destination;
		dijkstra.CreateGraph(filename);
		cout << "Hello, what two places do you need to find the shortest path between? (please enter two strings)" << endl;
		cout << "Please enter origin" << endl;
		getline(cin, origin);
		cout << "Please enter destination" << endl;
		getline(cin, destination);
		shortest_path = dijkstra.FindShortestPath(origin, destination);
		stack<string> directions = shortest_path.GetDirection();
		cout << "Traveling from: " << origin << " to: " << destination << endl;
		cout << "It will be a distance of " << shortest_path.GetDistance() << " miles" << endl;
		cout.setf(ios::fixed); cout.setf(ios::showpoint); cout.precision(2);
		cout << "And a time of " << shortest_path.GetTime() << " hours." << endl;
		while (!directions.empty())
		{
			cout << directions.top();
			directions.pop();
			if (!directions.empty())
			{
				cout << ", ";
			}
		}
		cout << endl;
		cout << system("pause");
	}
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
	return 0;
}

/*
void TestCopyConstructor()
{
// Arrange
Pair<int, int> pair1(5, 10);

// Act
Pair<int, int> pair2(pair1);


// Assert
bool pass = (pair1.GetKey() == pair2.GetKey() &&
pair1.GetValue() == pair2.GetValue())
? true : false;

if (pass)
{
std::cout << "TestCopyConstructor() PASS" << std::endl;
}
else
{
std::cout << "TestCopyConstructor() FAIL" << std::endl;
}

}

*/

