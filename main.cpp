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

    // Print the arguments themselves
    for(int a = 0; a < argc; a++)
    {
        cout << argv[a] << " ";
        cout << endl; 
    }

    // Write checks for number of inputs / get variables
	if (argc>6|argc <4)
	{
		cout <<"Number of dates are not compatible whith programm execution"<<endl;
		return 1;
	}
    for(int a = 0; a < argc; a++)
        cout << argv[a] << " ";
    cout << endl;

    cout << "Hello" << endl;
    return 0;
}