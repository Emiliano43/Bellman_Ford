#include "Algorithm_Forda.h"

int main() {
	setlocale(LC_ALL, "rus");
	Algorithm_Forda solution;
	try {
		solution.set_data();
	}
	catch (runtime_error e) {
		cout << e.what() << endl;
	}
	try {
		solution.find_way(1, 3);
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
	}
	system("pause");
	return 0;
}