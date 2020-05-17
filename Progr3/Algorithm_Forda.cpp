#include "Algorithm_Forda.h"

Algorithm_Forda::Algorithm_Forda()
{
	amount_of_cities = 0;
	amount_of_ribs = 0;
}

Algorithm_Forda::~Algorithm_Forda()
{
	city.~ListtempClass();
	ribs.~List();
}

void Algorithm_Forda::set_data()						//gets data from "input.txt" file
{
	if (!city.isEmpty()) {
		city.clear();
		ribs.clear();
	}
	ifstream file("input.txt");
	if (!file.is_open())
		throw runtime_error("File is not found");

	List<char> cur_city;
	rib cur_rib;
	char symbol;
	bool second_city = false;
	while (!file.eof()) {
		file >> noskipws >> symbol;
		if (file.eof())
			break;
		if (symbol == ';')
		{
			file >> symbol;
			if (!city.contains(cur_city))
			{
				amount_of_cities++;
				city.push_back(cur_city);
				if (!second_city)
					cur_rib.vertex1 = city.get_number(cur_city);
				else
					cur_rib.vertex2 = city.get_number(cur_city);
				cur_city.nullify();
			}
			else {
				if (!second_city)
					cur_rib.vertex1 = city.get_number(cur_city);
				else
					cur_rib.vertex2 = city.get_number(cur_city);
				cur_city.clear();
			}
			if (!second_city) {
				second_city = true;
			}
			else {
				if (symbol == 'N') {
					cur_rib.cost = INF;
					while (symbol != '\n' && !file.eof() && symbol != ';')
						file >> symbol;
				}
				else {
					file.unget();
					file >> cur_rib.cost;
					file >> symbol;
				}
				ribs.push_back(cur_rib);
				swap(cur_rib.vertex1, cur_rib.vertex2);
				file >> symbol;
				if (symbol == 'N') {
					cur_rib.cost = INF;
					while (symbol != '\n' && !file.eof() && symbol != ';')
						file >> symbol;
				}
				else {
					file.unget();
					file >> cur_rib.cost;
				}
				ribs.push_back(cur_rib);
				while (symbol != '\n' && !file.eof())
					file >> symbol;
				second_city = false;
				continue;
			}
		}
		cur_city.push_back(symbol);
	}
	amount_of_ribs = ribs.get_size();
	file.close();
}

void Algorithm_Forda::find_way(size_t start, size_t destination) {							//prints the shortest path from one city to another
	if (city.isEmpty())
		throw runtime_error("Data is not set");
	if (start < 0 || destination < 0 || start > amount_of_cities - 1 || destination > amount_of_cities - 1)
		throw invalid_argument("Number of city is incorrect");

	List<int> distance(amount_of_cities, INF);
	List<int> predecessor(amount_of_cities, -1);
	distance.set(start, 0);
	bool any;
	for (;;) {
		any = false;
		for (size_t j = 0; j < amount_of_ribs; ++j) {
			if (distance.at(ribs.at(j).vertex1) < INF) {
				if (distance.at(ribs.at(j).vertex2) > distance.at(ribs.at(j).vertex1) + ribs.at(j).cost)
				{
					distance.set(ribs.at(j).vertex2, distance.at(ribs.at(j).vertex1) + ribs.at(j).cost);
					predecessor.set(ribs.at(j).vertex2, ribs.at(j).vertex1);
					any = true;
				}
			}
		}
		if (!any)  break;
	}
	if (distance.at(destination) == INF) {
		cout << "No flights from ";
		city.at(start).print_to_console();
		cout << " to ";
		city.at(destination).print_to_console();
		cout << '.' << endl;
		return;
	}
	List<int> way;
	int price = 0;
	for (int cur = destination; cur != -1; cur = predecessor.at(cur))
	{
		way.push_back(cur);
	}
	way.reverse();
	for (size_t i = 1; i < way.get_size(); i++) {
		price += ribs.get_price(way.at(i - 1), way.at(i));
	}
	cout << "Flight from ";
	city.at(start).print_to_console();
	cout << " to ";
	city.at(destination).print_to_console();
	cout << ":\n";
	for (size_t i = 0; i < way.get_size(); ++i)
	{
		city.at(way.at(i)).print_to_console();
		if (i + 1 != way.get_size())
			cout << " - ";
	}
	cout << endl << "Total cost of the way: " << price << endl;
}

List<int> Algorithm_Forda::return_way(size_t start, size_t destination) {							//returns the shortest path as list of indices
	if (city.isEmpty())
		throw runtime_error("Data is not set");
	if (start < 0 || destination < 0 || start > amount_of_cities - 1 || destination > amount_of_cities - 1)
		throw invalid_argument("Number of city is incorrect");
	List<int> distance(amount_of_cities, INF);
	List<int> predecessor(amount_of_cities, -1);
	distance.set(start, 0);
	bool any;
	for (;;) {
		any = false;
		for (size_t j = 0; j < amount_of_ribs; ++j) {
			if (distance.at(ribs.at(j).vertex1) < INF) {
				if (distance.at(ribs.at(j).vertex2) > distance.at(ribs.at(j).vertex1) + ribs.at(j).cost)
				{
					distance.set(ribs.at(j).vertex2, distance.at(ribs.at(j).vertex1) + ribs.at(j).cost);
					predecessor.set(ribs.at(j).vertex2, ribs.at(j).vertex1);
					any = true;
				}
			}
		}
		if (!any)  break;
	}
	List<int> way;
	if (distance.at(destination) == INF) {
		cout << "No flights from ";
		city.at(start).print_to_console();
		cout << " to ";
		city.at(destination).print_to_console();
		cout << '.' << endl;
		return way;
	}
	for (int cur = destination; cur != -1; cur = predecessor.at(cur))
	{
		way.push_back(cur);
	}
	way.reverse();
	return way;
}

void Algorithm_Forda::swap(int& value1, int& value2) {					//swaps values of arguments
	int cur = value1;
	value1 = value2;
	value2 = cur;
}

void Algorithm_Forda::set_data(string way)								//sets info from file with path specified as argument
{
	if (!city.isEmpty()) {
		city.clear();
		ribs.clear();
	}
	ifstream file(way);
	if (!file.is_open())
		throw runtime_error("File is not found");

	List<char> cur_city;
	rib cur_edge;
	char symbol;
	bool second_city = false;
	while (!file.eof()) {
		file >> noskipws >> symbol;
		if (file.eof())
			break;
		if (symbol == ';')
		{
			file >> symbol;
			if (!city.contains(cur_city))
			{
				amount_of_cities++;
				city.push_back(cur_city);
				if (!second_city)
					cur_edge.vertex1 = city.get_number(cur_city);
				else
					cur_edge.vertex2 = city.get_number(cur_city);
				cur_city.nullify();
			}
			else {
				if (!second_city)
					cur_edge.vertex1 = city.get_number(cur_city);
				else
					cur_edge.vertex2 = city.get_number(cur_city);
				cur_city.clear();
			}
			if (!second_city) {
				second_city = true;
			}
			else {
				if (symbol == 'N') {
					cur_edge.cost = INF;
					while (symbol != '\n' && !file.eof() && symbol != ';')
						file >> symbol;
				}
				else {
					file.unget();
					file >> cur_edge.cost;
					file >> symbol;
				}
				ribs.push_back(cur_edge);
				swap(cur_edge.vertex1, cur_edge.vertex2);
				file >> symbol;
				if (symbol == 'N') {
					cur_edge.cost = INF;
					while (symbol != '\n' && !file.eof() && symbol != ';')
						file >> symbol;
				}
				else {
					file.unget();
					file >> cur_edge.cost;
				}
				ribs.push_back(cur_edge);
				while (symbol != '\n' && !file.eof())
					file >> symbol;
				second_city = false;
				continue;
			}
		}
		cur_city.push_back(symbol);
	}
	amount_of_ribs = ribs.get_size();
	file.close();
}
