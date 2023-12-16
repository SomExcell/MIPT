#include <matrix.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void tests()
{
	ifstream in("Tests.txt");
	if (in.is_open())
	{
		size_t side, size;
		int result;
		string test;
		while (getline(in, test))
		{
			cout << test << '\t';
			in >> side;
			size = side * side;
			int* m = new int[size];
			for (size_t i = 0; i < side; ++i)
			{
				for (size_t j = 0; j < side; ++j)
				{
					in >> m[i * side + j];
				}
			}
			Matrix<int> matrix(side, side, m, m + size - 1);
			in >> result;
			if (result == matrix.determinant())
				cout << "OK" << endl;
			else
				cout << '-' << endl;
			cout << "--------------------------------------" << endl;
			getline(in, test);
		}
	}
	in.close();

}


int main()
{
	tests();
	return 0;
}
