#include "Polyhedron.hpp"
#include "Utils.hpp"


using namespace std;
using namespace PolyhedralLibrary;

// To pass parameters to main the standard syntax is:
// argc: number of arguments
// argv: array of arguments
// The first argument is always the executable file's name

int main(int argc, char *argv[])
{
	// Print number of arguments
	cout << "Number of arguments: " << argc << endl;


	// Check number of inputs
	if ((argc != 7) && (argc != 5))
	{
		cerr << "Number of inputs is not compatible with program execution" << endl;
		return 1;
	}
	
	// Get value of p 
	int p;
	istringstream convert_p(argv[1]);
		convert_p >> p;
	if((p < 3) || (p > 5))
	{
		cerr << "Wrong value for p" << endl;
		return 1;
	}
	
	// Get value of q
	int q;
	istringstream convert_q(argv[2]);
		convert_q >> q;
	if((q < 3) || (q > 5))
	{
		cerr << "Wrong value for q" << endl;
		return 1;
	}

	// Check if p and q are compatible
	if( (p == 3) && ((q == 3) || (q == 4) || (q == 5)))
	{
		cout << "p: " << p << endl;
		cout << "q: " << q << endl;
	} 
	else if((q == 3) && ((p == 3) || (p == 4) || (p == 5)))
	{
		cout << "p: " << p << endl;
		cout << "q: " << q << endl;
	} 
	else
	{
		cerr << "p and q are not compatible" << endl;
		return 1;
	}

	// Get value of b
	int b;
	istringstream convert_b(argv[3]);
		convert_b >> b;
	if(b < 0)
	{
		cerr << "Wrong value for b" << endl;
		return 1;
	}

	// Get value of c
	int c;
	istringstream convert_c(argv[4]);
		convert_c >> c;
	if(c < 0)
	{
		cerr << "Wrong value for c" << endl;
		return 1;
	}

	// Check if b and c are compatible
	int val;

	if((b == c) && (b != 0))
	{
		cout << "b: " << b << endl;
		cout << "c: " << c << endl;

		val = b;
		cout << "Class II with parameter: " << val << endl;
	}
	else if(((b == 0) && (c != 0)) || ((b != 0) && (c == 0)))
	{
		cout << "b: " << b << endl;
		cout << "c: " << c << endl;

		if(b != 0)
		{
			val = b;
		}
		else
		{
			val = c;
		}
		cout << "Class I with parameter: " << val << endl;
	}
	else
	{
		cerr << "b and c are not compatible" << endl;
		return 1;
	}

	// Get ID of starting vertex
	// (da completare)


	
	return 0;
	
}