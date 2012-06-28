#include <iostream>
#include <io.h>
using namespace std;

int main()
{
    struct _finddata_t c_file;
    strcpy(c_file.name, "Tester");
    cout << "Hello World!" << endl;
    return 0;
}

