#include "KMeansClusteringProcessor.h"

KMeansClusteringProcessor::KMeansClusteringProcessor()
{
    m_Dimension = 0;
    m_Data.clear();
    m_Labels.clear();
    m_Centroids.clear();
    m_CentroidIdxs.clear();
    m_ClusteredData.clear();

}

KMeansClusteringProcessor::~KMeansClusteringProcessor()
{
    //dtor
}
bool KMeansClusteringProcessor::procCentroidFile(string path)
{
    ifstream ifStream;
    ifStream.open(path.c_str());
    string line;
    for(int i = 0; i < m_Clustercount; i++)
    {
        ifStream>>line;
        m_CentroidIdxs.push_back(atoi(line.c_str()) - 1);
    }
    return true;
}
bool KMeansClusteringProcessor::procDataFile(string path, bool includeLabel)
{
    ifstream ifStream;
    ifStream.open(path.c_str());
    string line;
    while(ifStream >> line)
    {
        stringstream isStream(line);
        string token;
        vector<string> stringData;
        vector<float> floatData;
        while(getline(isStream, token, ','))
            stringData.push_back(token);
        int size = stringData.size();
        for(int i = 0; i < size - 1; i++)
            floatData.push_back(atof(stringData[i].c_str()));
        if(isNumber(stringData[size - 1]))
            floatData.push_back(atof(stringData[size - 1].c_str()));
        else
            m_Labels.push_back(stringData[size - 1]);
        m_Data.push_back(floatData);
        m_ClusterAssignment.push_back(0);
    }
    return true;
}
bool KMeansClusteringProcessor::isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void KMeansClusteringProcessor::generateCentroidIndexes()
{
    
    for(int i = 0; i < m_Clustercount; i++)
    {
        int num;
        while(true)
        {
            num = (rand() + time(NULL)) % m_Data.size();
            int j;
            for(j = 0; j < i; j++)
                if(num == m_CentroidIdxs[j])
                    break;
            if(j == i)
                break;
        }
        m_CentroidIdxs.push_back(num);
    }
}
bool KMeansClusteringProcessor::testStopCondition(vector<vector<float> > mean)
{
    float sum = 0;
    for(int i = 0; i < m_Clustercount; i++)
        sum += distance(mean[i], m_LastMean[i]);
    return sum <= EPSILON;
}
float KMeansClusteringProcessor::distance(vector<float> a, vector<float> b)
{
    float sum = 0;
    for(int i = 0; i < a.size(); i++)
        sum += (a[i] - b[i]) *(a[i] - b[i]);
    return sqrt(sum);
}
bool KMeansClusteringProcessor::proc(string dataFilePath, int clusterCount, string centroidFilePath, bool includeLabel)
{
    int i, j;
    if(!procDataFile(dataFilePath, includeLabel))
        return false;
    m_Clustercount = clusterCount;
    if(centroidFilePath == "")
        generateCentroidIndexes();
    else
        if(!procCentroidFile(centroidFilePath))
            return false;
    for(i = 0; i < m_CentroidIdxs.size(); i++)
        m_Centroids.push_back(m_Data[m_CentroidIdxs[i]]);

    int m_IterationCount = 0;

    for(i = 0; i < m_Clustercount; i++)
        m_ClusteredData.push_back(m_Data);
    while(true)
    {
        m_IterationCount++;
        for(i = 0; i < m_Clustercount; i++)
            m_ClusteredData[i].clear();

        for(i = 0; i < m_Data.size(); i++)
        {
            int idx = 0; float minv = 1000000000;
            for(j = 0; j < m_Clustercount; j++)
            {
                float dist = distance(m_Centroids[j], m_Data[i]);
                if(dist < minv)
                {
                    minv = dist;
                    idx = j;
                }
            }
            m_ClusteredData[idx].push_back(m_Data[i]);
            m_ClusterAssignment[i] = idx;
        }
        vector<vector<float> > means;
        for(int i = 0; i < m_Clustercount; i++)
        {
            vector<float> rv = getMeanVector(m_ClusteredData[i]);
            means.push_back(rv);
        }

        if(m_IterationCount != 1)
        {
            if(testStopCondition(means))
            {
                m_LastMean = means;
                break;
            }
        }
        m_LastMean = means;
    }

}
float KMeansClusteringProcessor::getSSE()
{
    float sum = 0;
    for(int i = 0; i < m_Clustercount; i++)
    {
        for(int j = 0; j < m_ClusteredData[i].size(); j++)
        {
            float v = distance(m_ClusteredData[i][j], m_LastMean[i]);
            v *= v;
            sum += (v);
        }
    }
    return sum;
}
vector<float> KMeansClusteringProcessor::getMeanVector(vector<vector<float> > vec)
{
    vector<float> sum = vec[0];
    for(int i = 1; i < vec.size(); i++)
        for(int j = 0; j < vec[i].size(); j++)
            sum[j] += vec[i][j];
    for(int i = 0; i < sum.size(); i++)
        sum[i] /= vec.size();
    return sum;
}
void KMeansClusteringProcessor::output()
{
    cout<<"Number of data points="<<m_Data.size()<<", dimension="<<m_Data[0].size()<<", k="<<m_Clustercount<<endl;
    cout<<"Iteration count="<<m_IterationCount<<endl;
    cout<<"Final mean values"<<endl;
    for(int i = 0; i < m_Clustercount; i++)
    {
        cout<<"Cluster "<<i + 1<<"--";
        outputVector(m_LastMean[i]);
    }
    cout<<"SSE score="<<getSSE()<<endl;
    for(int i = 0; i < m_Data.size(); i++)
    {
        cout<<"Data1=";
        for(int j = 0; j < m_Data[i].size() - 1; j++)
            cout<<m_Data[i][j]<<",";
        cout<<m_Data[i][m_Data[i].size() - 1];
        cout<<" Cluster idx="<<m_ClusterAssignment[i]<<endl;
    }

    for(int i = 0; i < m_Clustercount; i++)
        cout<<"cluster size "<<i + 1<<" = "<<m_ClusteredData[i].size()<<"  ";
    cout<<endl;

}
void KMeansClusteringProcessor::outputVector(vector<float> vec)
{
    for(int i = 0; i < vec.size() - 1; i++)
        cout<<vec[i]<<", ";
    cout<<vec[vec.size() - 1]<<endl;
}
