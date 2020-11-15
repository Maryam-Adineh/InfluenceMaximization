# InfluenceMaximization
Implementation of Influence Maximization algorithms of bellow papers:

Maximum Degree Based Heuristics for Influence Maximization
https://ieeexplore.ieee.org/abstract/document/8566515

High Quality Degree Based Heuristics for the Influence Maximization Problem
https://arxiv.org/abs/1904.12164

This c++ code is compiled on linux OS with gcc version 10.2.0.

To compile:
	make InfluenceMaximization
	
To execute:
	./InfluenceMaximization <remove|decrease> <dataset> <d|u> <p> <k> <R>
	
	<remove|decrease>
		Algorithm name. 'remove' refers to NeighborsRemove and 'degree' refers to DegreeDecrease.
	<dataset>
		Path of dataset file. An example of file format is described in the following.	
	<d|u>
		'd' for directed graph file and 'u' for undirected.
	<p>
		Propagation probability of IC model. A number in [0,1].
	<k>
		Size of the seed set.
	<R>
		Number of simulations to calculate influnce spread.
		
example:
	./InfluenceMaximization remove graph.txt d 0.01 2 1000

graph.txt:
5 10  => #n #m: Number of vertices and edges
0 1  \
0 2   \
1 3    => #m line of edges(source target)
. .   /
. .  /

