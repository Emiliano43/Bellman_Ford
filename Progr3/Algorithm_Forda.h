#pragma once
#include <fstream>
#include "ListTempClass.h"
class Algorithm_Forda
{
private:
	int amount_of_cities, amount_of_ribs;
	ListtempClass<List<char>> city;
	struct rib {
		int vertex1, vertex2, cost;
	};
	List<rib> ribs;
	void swap(int&, int&);
	const int INF = 1000000000;
public:
	Algorithm_Forda();
	~Algorithm_Forda();
	void set_data();
	void set_data(string);
	void find_way(size_t, size_t);
	List<int> return_way(size_t, size_t);
};
