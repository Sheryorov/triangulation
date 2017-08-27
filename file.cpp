#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream fout("cpp.txt", ios_base::app);
    fout << "<triangle>" << endl;
    fout << "    <Vertex>"<< "0. 0. 0. "  << "</Vertex>" << endl;
    fout << "</triangle>" << endl;   
    fout.close();   
    return 0;
}
