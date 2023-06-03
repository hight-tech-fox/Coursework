# Coursework
This program solves the following problem:
In a system of two-way roads, find a path from city A to city B with the minimum value of P+S, 
where S is the sum of the lengths of the roads and P is the sum of the tolls on them.

2.1. Initial data of the task
The first line of the input file input.txt contains the total number of cities n.
The second line of the input file contains the names of cities separated by a space.
The third line contains the names of the starting and ending points of the path (A and B).
From the fourth line to the end of the file contains information about the roads.
<toll for this road> <city name 1> <city name 2> <length of this road>.
  
Input example:
4
Prague Brno Ostrava Litomysl
Prague Ostrava
5 Ostrava Litomysl 2
2 Litomysl Prague 15
3 Prague Brno 10
4 Brno Ostrava 7

2.2. Result:
If the program worked correctly, the output file will look like this:
The first line of the out.txt output file displays the phrase "Least sum of road lengths and tolls between cities A and B" and the value of the minimum sum of road lengths and tolls.
Next, the trajectory of the path is displayed in the order of visit, after which the phrase "The sum of the lengths of roads" and the value of the sum of the lengths of the roads, the phrase "The sum of the tolls" and the value of the sum of the tolls.
Otherwise (if cities A and B) match, at least one of the cities is isolated or one of the cities is not in the input, the program will display an error message.
There will also be an error message if incorrect data is received (negative road lengths or tolls).
  
Sample output:
The smallest sum of road lengths and tolls on them between the cities of Prague and Ostrava
24
Path in order of visit:
Prague -> Brno -> Ostrava -> FINAL
The sum of the lengths of the roads:
17
Toll amount:
7

2.3 Solution:
The mathematical model is a multigraph, undirected, weighted, disconnected, labeled.

Graph analysis:
1. First, we check whether the start and end points of the route exist among the set of cities read from the file, whether these two points do not coincide (loop). In the internal representation of the data, the cities will have indices from 0 to n-1, we will create variables to store the indices A and B (int A, B). Initially, we assign a value equal to Infinity (100000) to these variables, so that the index values initially could not be equal to the indexes of other cities read from the file (with a large number of cities). Then we read the names of all cities from the file into a string array, after which we look for the names A and B in this array. After that, the variables A and B themselves (in the program) are assigned the corresponding serial numbers (indexes) in the array of names.
2. If one of the variables A or B is still equal to Infinity, then cities A and B do not exist or are the same, then the program will display the message "Start and end points are the same or do not exist."
3. This is followed by a check for the isolation of A and B. First, we fill in two weight matrices: the 1st for tolls, the 2nd for the values of the lengths of roads between cities. After that, we form a single weight matrix from them by summing the 1st and 2nd matrices. Each element of the resulting matrix (3) will be equal to P + S, where P is the toll, and S is the length of the path. Then we look for the sum of the row elements in the resulting matrix (3). If the sum of the elements is 0, then the city is completely isolated from the rest. (This option can only define complete isolation from other cities, but allows for A and B being on separate isolated road systems.)
4. Option: the city is connected to itself by a loop (property of the multigraph). This property does not affect the correctness of the program in any way.

Input data analysis:
1. Check the number of cities for a positive value. If the number of cities is set to a non-positive value, then the following phrase will be output to the file: “ERROR: an incorrect number of cities was entered”, otherwise we continue.
2. Checking for a negative length of the road, is performed during the reading of data from the files. If at least one road length specified by a negative number is found, the file will display the following message: “ERROR: path length cannot be negative”.

Formal statement of the problem:
In a weighted, undirected, disconnected and labeled multigraph, find the path from city A to city B with the smallest sum P+S, where P is the sum of the tolls, S is the sum of the lengths of the roads.
This task can be divided into 2 major subtasks:
1 Finding the smallest P+S sum using Dijkstra's algorithm.
2 Restoring the path itself, finding the sum of the tolls and the sum of the lengths of the roads.

Algorithm for solving the set subtasks:
Initially, the correctness of the received data is checked.
If all conditions are met, we can continue.
1. Finding the shortest path.
We create two two-dimensional arrays with dimensions n * n, storing matrices of weight matrices of the lengths of roads and tolls on them. We fill them with zeros so that in the input data we do not indicate pairs of cities between which there is no connection for this type of road. Then we read the data from the file until the end of the file, and change the matrices according to the following principle: If the cells of the matrix connecting these two cities contain the initial value (0) and the read path length (toll) is greater than 0, then we change the adjacency matrix (two matrices are built according to the same principle). If the path length is less than zero, we output a message to the file that the input data was entered incorrectly.
After filling in the data on road lengths and tolls, we form a single matrix (P + S) by summing the two created matrices.
After filling in the matrix (P + S), we check for a mandatory condition about the isolation of cities. We consider the sum of elements in the row of the matrix (P+S). If one of the rows with indices A or B is equal to zero, then there is no solution to the problem, because at least one city is isolated from the general road system.
Before running Dijkstra's algorithm, we declare a one-dimensional array in which we will write the minimum P + S sums from the starting point to the rest of the cities. We initialize the elements of the array by assigning them the values of infinity (constant Infinity), since the vertices have not been visited, and the distance to them is still unknown. The array element with index A is marked with zero.

Dijkstra's algorithm.

1. We start the bypass from city A. Then we go around the neighboring vertices in turn. We update data about them in a one-dimensional array of the minimum sum P + S from city A to other cities, now the minimum sum P + S from the current starting vertex to vertex A will be stored there. We continue this operation until we bypass all neighbors. Upon completion of the operation, we put a label in the array of visited cities. And move on to the next city.
2. We continue the traversal from the city that we have not visited yet (there is an array of visited cities), but we have changed the values of the shortest path to this city (from A), i.e. from neighbor A. We repeat the operation described above, bypassing all cities - neighbors, relative to our new starting point, in order to reduce the found P+S sums in the array of minimum P+S sums.
3. Repeat these steps until we visit all connected vertices.
After that, we check whether we have changed the value of the minimum sum P + S from city A to city B. If not, then cities A and B are in different closed systems of graphs. Otherwise, output to the file a value equal to the shortest distance to point B - the answer to subtask number 1.
4. Restoration of the path itself, finding the sum of the tolls and the sum of the lengths of the roads.
We fill the array of visited cities with infinities (constant Infinity). (So that P+S sums cannot be confused with any other values).
We start the search from the end. Therefore, we assign the index of the final city B to the zero element of the array. We create a variable responsible for the sum P+S and assign it the value of the minimum sum P+S from A to B (the answer to subtask 1). Next, we run a loop in which we will change the index of city B until it becomes equal to city A.

We look through all the cities for a connection with the city B.
As soon as the connection is found, we check the following condition: if the difference between the length from A to B and the length from B to the found city is equal to the length from A to the found city, then it means that the transition to city B was made from this vertex, change the index of city B to the index of the city - transition. Otherwise, we continue the search. Thus, we completely restore the path by writing the indexes of visited cities in reverse order into a one-dimensional array.
Next, we find the sums of the lengths of the roads and the sums of the tolls. The sum of the lengths of the roads are found as follows. A for loop is built, if the value in the array cell in which the indexes of visited cities were written is less than infinity, then we sum the value from the array of roads with indices <city index> <city index - 1> into a separate variable. The amount of tolls is found in the same way. We output all the received data to a separate file.


