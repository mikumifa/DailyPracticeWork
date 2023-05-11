import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;


public class Graph {
    private final ArrayList<Vertex> vertices;
    private final ArrayList<Edge> edges;

    public ArrayList<Vertex> getVertices() {
        return vertices;
    }

    public ArrayList<Edge> getEdges() {
        return edges;
    }

    public Graph() {
        vertices = new ArrayList<Vertex>();
        edges = new ArrayList<Edge>();
    }

    public void addVertex(Vertex v) {
        if (!vertices.contains(v)) {
            vertices.add(v);
        } else {
            System.err.println("Vertex already exists");
        }
    }

    public void addEdge(Edge v) {
        if (!this.edges.contains(v)) {
            edges.add(v);
            if (!vertices.contains(v.getU())) {
                System.out.println("New edge is add successfully");
                addVertex(v.getU());
            }
            if (!vertices.contains(v.getV())) {
                System.out.println("New edge is add successfully");
                addVertex(v.getV());
            }
        } else
            System.out.println("Edge already exists");
    }

    public void addEdgeWithoutInfo(Edge v) {
        if (!this.edges.contains(v)) {
            edges.add(v);
            if (!vertices.contains(v.getU())) {
                addVertex(v.getU());
            }
            if (!vertices.contains(v.getV())) {
                addVertex(v.getV());
            }
        }
    }


    public Graph SpanningTreeBuild(Vertex root) {
        Graph g = new Graph(); // Create an empty graph G
        g.addVertex(root); // Add root to G
        buildSpanningTreeRecur(g, root);
        for (Vertex v : vertices) {
            if (!(g.containsVertex(v))) {
                return null;
            }
        }
        return g;
    }

    public void buildSpanningTreeRecur(Graph g, Vertex u) {
        ArrayList<Vertex> neighbors = this.getNeighbors(u);
        for (Vertex v : neighbors) {
            if (!g.containsVertex(v)) {
                if (!g.edges.contains(new Edge(u, v)))
                    g.edges.add(new Edge(u, v)); // Add the edge (u, v) to G
                if (!g.edges.contains(new Edge(v, u)))
                    g.edges.add(new Edge(v, u));
                if (!g.containsVertex(v))
                    g.addVertex(v);
                buildSpanningTreeRecur(g, v);
            }
        }
    }

    private boolean isContainCycle;

    public boolean containCycle() {

        for (Vertex root : vertices) {
            isContainCycle = false;
            Graph g = new Graph(); // Create an empty graph G
            g.addVertex(root); // Add root to G
            containCycleRecur(g, root);
            if (isContainCycle)
                return true;
        }
        return false;

    }

    public void containCycleRecur(Graph g, Vertex u) {
        ArrayList<Vertex> neighbors = getNeighbors(u);
        for (Vertex v : neighbors) {
            if (v.equals(u))
                continue;
            if (!g.containsVertex(v)) {
                g.addVertex(v);
                containCycleRecur(g, v);
            } else {
                isContainCycle = true;
                return;
            }
        }
    }

    public boolean connected() {
        Graph g = new Graph(); // Create an empty graph G
        Vertex root = vertices.get(0);
        g.addVertex(root); // Add root to G
        connectedRecur(g, root);
        return g.getVertices().size() == getVertices().size();
    }

    public void connectedRecur(Graph g, Vertex u) {
        ArrayList<Vertex> neighbors = getNeighbors(u);
        for (Vertex v : neighbors) {
            if (v.equals(u))
                continue;
            if (!g.containsVertex(v)) {
                g.addVertex(v);
                connectedRecur(g, v);
            }
        }
    }

    private boolean containsVertex(Vertex v) {
        return vertices.contains(v);
    }

    private ArrayList<Vertex> getNeighbors(Vertex u) {

        ArrayList<Vertex> neighbors = new ArrayList<Vertex>();
        for (Edge e : edges) {
            if (e.getU().equals(u))
                neighbors.add(e.getV());
        }
        return neighbors;
    }

    public void print() {
        vertices.sort(new Comparator<Vertex>() {

            @Override
            public int compare(Vertex o1, Vertex o2) {
                return o1.getName().compareTo(o2.getName());
            }
        });
        for (Vertex v : vertices) {

            ArrayList<String> ans = new ArrayList<String>();
            for (Edge e : edges) {
                if (v.equals(e.getU())) {
                    ans.add(e.getV().getName());
                }
            }
            System.out.print(v.getName() + ":");
            for (int i = 0; i < ans.size(); i++) {
                if (i != ans.size() - 1)
                    System.out.print(" " + ans.get(i) + ',');
                else
                    System.out.print(" " + ans.get(i));
            }
            System.out.println();
        }
    }

    public void saveFile(String path) throws IOException {
        vertices.sort(new Comparator<Vertex>() {

            @Override
            public int compare(Vertex o1, Vertex o2) {
                return o1.getName().compareTo(o2.getName());
            }
        });
        BufferedWriter out = new BufferedWriter(new FileWriter(path));
        for (Vertex v : vertices) {

            ArrayList<String> ans = new ArrayList<String>();
            for (Edge e : edges) {
                if (v.equals(e.getU())) {
                    ans.add(e.getV().getName());
                }
            }

            out.write(v.getName() + ":");
            for (int i = 0; i < ans.size(); i++) {
                if (i != ans.size() - 1)
                    out.write(" " + ans.get(i) + ',');
                else
                    out.write(" " + ans.get(i));
            }
            out.write("\n");
        }
        out.close();
    }
}