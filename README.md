## Graph Coloring (Vertex)
C++ program that implements greedy algorithm and generates LaTeX (TikZ) code of the graph colored.

## Creating the `input.txt`
First you should describe the graph in the `input.txt`. The first line is the number `V` of vertices and the following ones should contain the edges `E`. Let's say we have the graph below:

<img src="http://toribeiro.com/static/img/input_graph.png" width="242" height="260" class="img-responsive center-block" />

The input file should look like this:

```
5
0 1
0 2
1 2
1 3
1 4
2 3
3 4
```
## How to run
Simply open the Terminal and run `./gColoring` and see the `.pdf` file as the output.

P.S: You need to have LaTeX installed so the `pdflatex` command is recognized by the Terminal (Linux/Mac OS).

For more details: http://toribeiro.com/understanding-graph-coloring-part-II.html
