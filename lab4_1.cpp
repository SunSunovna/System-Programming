#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char **file_1)
{
    char buffer[256];
    strcat(buffer, "cp ");
    strcat(buffer, file_1[1]);
    strcat(buffer, " ");
    strcat(buffer, file_1[2]); 

    if (system(buffer))
        cout << "Failed" << endl;
    else cout << "Successful" << endl;
    return 0;
}
