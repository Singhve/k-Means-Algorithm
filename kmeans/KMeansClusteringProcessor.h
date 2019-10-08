#ifndef KMEANSCLUSTERINGPROCESSOR_H
#define KMEANSCLUSTERINGPROCESSOR_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define EPSILON 0.0001

class KMeansClusteringProcessor
{
    int m_Clustercount;
    int m_Dimension; //
    vector<vector<float> > m_Data; //data
    vector<int> m_ClusterAssignment;
    vector<string> m_Labels; //labels of data
    vector<vector<float> > m_Centroids; //centroids
    vector<int> m_CentroidIdxs; //centroid indexes
    vector<vector<vector<float> > > m_ClusteredData; //[cluster idx][data idx in cluster][element idx in data]
    vector<vector<float> > m_LastMean; //last mean value vector

    int m_IterationCount;


    public:
        KMeansClusteringProcessor();
        virtual ~KMeansClusteringProcessor();
        bool proc(string dataFilePath, int clusterCount, string centroidFilePath = "", bool includeLabel = false);
        void output();

    protected:

    private:
        bool procCentroidFile(string path);
        bool procDataFile(string path, bool includeLabel = false);
        void generateCentroidIndexes();
        bool testStopCondition(vector<vector<float> > mean);
        vector<float> getMeanVector(vector<vector<float> > vec);
        float distance(vector<float> a, vector<float> b);
        float getSSE();
        void outputVector(vector<float> vec);
        bool isNumber(const std::string& s);
};

#endif // KMEANSCLUSTERINGPROCESSOR_H
