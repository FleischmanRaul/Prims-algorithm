# Prims-algorithm
Implementation of Prim's algorithm in Haskell and C++, a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph. 
I wrote these fairly simple programs to present the differences between functional and imperative programming.

Running the Haskell version in ghci:
```
prim graph1 - prints the minimal tree
weightOf $ prim graph1 - prints the weight
```
Running the C++ version from a terminal:
```
g++ -o p prim.cpp
./p graph.txt 
```

