# k-Means-Algorithm
Implementing k-Means algorithm for clustering

Implement k-Means algorithm for clustering. The program should take a comma-separated data ﬁle, and the number of clusters(k-value) as command line parameters. There is one optional parameter, which is another ﬁlename which lists the id of initial centroids. For example, without the optional parameter, we may run your program (mykMeans) as below:

./mykMeans datafile.txt 3

In that case, it should cluster the data points in datafile.txt into 3 clusters. The data ﬁle datafile.txt lists one data point in each line. The values of a data points along diﬀerent dimensions are separated by a comma. No id is given for a data point, but you must assume that the id of a data point is the same as its line number in the input ﬁle assuming that the line numbering starts from 1. For initial centroid you should use k random data points.

Now, with the optional parameter, we can also run your program as below:

./mykMeans datafile.txt 5 centroidfile.txt

Say, the centroidfile.txt contains the following integers for a clustering task with k=5:
1
5 
19 
201 
371 
390

In that case you must use the points with id 5,19,201,371,and 390 as your initial centroids. For all cases, use  = 0.0001 as your stopping condition.

The program output should consists of the following information:
1. The number of data points in the input ﬁle, the dimension, and the value of k 
2. The number of iterations the program took for convergence 
3. The ﬁnal mean of each cluster and the SSE score (sum of square error) 
4. The ﬁnal cluster assignment of all the points. 
5. The ﬁnal size of each cluster.

Execute your program on the iris.txt dataset. Run it for at least 10 times with diﬀerent random initializations of centroid (make sure to randomize your random seeds so that diﬀerent runs of the program starts with a diﬀerent random set of centroids). Now, evaluate the clustering using purity-based evaluation and report the best purity score. Note that for purity based evaluation you need to know the true label of a data points. Here is the true label assignments on the iris.txt dataset: 1-50: class 1, 51-100: class 2, and 101-150: class 3.
