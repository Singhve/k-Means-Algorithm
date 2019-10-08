#include <iostream>

using namespace std;

#include "KMeansClusteringProcessor.h"

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));
    KMeansClusteringProcessor processor;

    if(argc != 3 && argc != 4)
    {
        cout<<"Parameter mismatch!"<<endl;
        return 0;
    }
    if(argc == 3)
        processor.proc(argv[1], atoi(argv[2]));
    else
        processor.proc(argv[1], atoi(argv[2]), argv[3]);
//    processor.proc("iris.data.txt", 3);
    processor.output();


    return 0;
}
