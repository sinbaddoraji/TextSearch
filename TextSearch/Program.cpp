#include "SearchEngine.h"

using namespace std;

void main(int argc, char** argv)
{
	//Create dynamic instance of search enging
	//pass file path as an argument
	new SearchEngine(argv[0]);
}

