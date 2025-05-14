#include<iostream>

using namespace std;

// To pass parameters to main the standard syntax is:
// argc: number of arguments
// argv: array of arguments
// The first argument is always the executable file's name

int main(int argc, char *argv[])
{

    // Print number of arguments
    cout << "argc: " << argc << endl;


    // Write checks for number of inputs / get variables
	if (argc>6 | argc <4)
	{
		cerr <<"Number of dates are not compatible whith programm execution"<<endl;
		return 1;
	}
	
	// Print the arguments themselves
    for(int a = 0; a < argc; a++)
        cout << argv[a] << " ";
    cout << endl;
	
	if(argv[0] < 3 | argv[0] > 5)
	{
		cerr << "Wrong value for p" << endl;
		return 1;
	}
	int p = argv[0];
	
	if(argv[1] < 3 | argv[1] > 5)
	{
		cerr << "Wrong value for q" << endl;
		return 1;
	}
	int q = argv[1];
	
	if(argv[2] < 0)
	{
		cerr << "Wrong value for b" << endl;
		return 1;		
	}
	if(argv[3] < 0)
	{
		cerr << "Wrong value for c" << endl;
		return 1;
	}
	if(argv[2] == argv[3] &argv[2] < 1)
	{
		cerr << "Wrong value for b" << endl;
		return 1;		
	}
    int b = argv[2];
	int c = argv[3];

	cout << "Hello" << endl;
    return 0;
}