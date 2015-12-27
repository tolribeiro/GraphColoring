// A C++ program to implement greedy algorithm for graph coloring
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

ofstream output_tikz_code("graphColored.tex"); // name of the file
ostringstream tikz_code;    // the latex code that will be printed 
string key_value_colors[] = {"red", "yellow", "blue"}; // array of colors (add more colors if needed)
FILE *fp = fopen("input.txt", "r"); // input file (this is the graph itself)

// class that represents the graph (undirected)
class Graph
{
    int V;              // V is the number of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
    public:
        // Constructor and destructor
        Graph(int V)   { this->V = V; adj = new list<int>[V]; }
        ~Graph()       { delete [] adj; }
     
        // function to add an edge to graph
        void addEdge(int v, int w);
     
        // Prints greedy coloring of the vertices
        void greedyColoring();
};
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // the graph is undirected
}

void printing_result(int result[], int V)
{
    for (int u = 0; u < V; u++)
        tikz_code << "\\AddVertexColor{" << key_value_colors[result[u]] << "}" << "{" << u << "}" << endl;
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring()
{
    int result[V];
 
    // Assign the first color to first vertex
    result[0]  = 0;
 
    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        result[u] = -1;  // no color is assigned to u
 
    // A temporary array to store the available colors. True
    // value of available_colors[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available_colors[V];
    for (int cr = 0; cr < V; cr++)
        available_colors[cr] = false;
 
    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available_colors[result[*i]] = true;
 
        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available_colors[cr] == false)
                break;
 
        result[u] = cr; // Assign the found color
 
        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available_colors[result[*i]] = false;
    }
 
    printing_result(result, V);
}

// Driver program to test function above
int main()
{
    int V, E = 0, a, b, i, j;
    vector<int> edges;
    
    tikz_code << 
                "\\documentclass[11pt]{article}\n"<<
                "\\usepackage{tkz-graph}\n"<<
                "\\begin{document}\n"<<
                "\\begin{figure}\n" << 
                "\\centering\n" << 
                "\\huge{\\bf{Graph Colored from }{\\tt gColoring.cpp}.}\n" <<
                "\\begin{tikzpicture}[scale=1.2]\n" << "\\renewcommand*{\\VertexLineWidth}{2pt}\n" << 
                "\\GraphInit[vstyle=Welsh]\n" << 
                "\\Vertices[unit=3]{circle}{"; //<< somevar << "1" << ",";

    system("clear");

    // current date/time based on current system
    time_t now = time(0);
   
    // convert now to string form
    char* dt = ctime(&now);

    fscanf(fp, "%d\n", &V); // read number of vertices from file

    Graph g(V); // create instance of Graph

    // read edges from file and add to creates the graph
    while (fscanf(fp, "%d %d\n", &a, &b) != EOF) {
        E++;
        edges.push_back(a);
        edges.push_back(b);
        g.addEdge(a, b);
    }

    for (i = 0; i < V; ++i) {
        tikz_code << i;
        if (i < V-1) tikz_code << ",";
        else if (i == V-1) tikz_code << "}" << "\n";
    }

    for (i = 0; i < E; i++) {
        tikz_code << "\\Edges(" << edges[j] << "," << edges[j+1] << ")" << "\n";
        j+=2;
    }

    tikz_code << "\\SetVertexNoLabel\n";

    g.greedyColoring(); // call to color the graph
    
    tikz_code   << "\\end{tikzpicture}\n\\caption{" << "TikZ-Graph generated in " << dt << ".}\n" 
                << "\\end{figure}\n"
                << "\\vspace{0.5cm}\n\\begin{center}For more details: {\\tt tolribeiro.github.com/repository}\\end{center}." 
                << "\\end{document}\n";

    output_tikz_code << tikz_code.str();
    output_tikz_code.close();

    cout << "\nPress ENTER to generate the graph from \e[1;33minput.txt\e[0m. ";
    if (cin.get()) {
        cout    << "\n* Graph \e[1;33mG("<< V << ", " << E << ")\e[0m read from \e[1;33minput.txt\e[0m successfully!" 
                << "\n\nPress ENTER to compile and see the result. ";
        cin.get();
        system("pdflatex graphColored.tex");
        system("clear");
    }

    system("open graphColored.pdf");

    return 0;
}