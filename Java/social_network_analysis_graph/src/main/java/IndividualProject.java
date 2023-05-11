import java.io.BufferedReader;

import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;


public class IndividualProject {
    private static final String inFileAddress = "graph.txt";

    public static int printMenuWithAction() {

        System.out.println();
        System.out.println("Action Menu:");
        System.out.println("1. Load the graph from graph.txt.");
        System.out.println("2. Find a spanning tree of the current graph with a specified root.");
        System.out.println("3. Is the current graph contains cycle?");
        System.out.println("4. Is the current graph connected?");
        System.out.println("5. Add an edge to the current graph.");
        System.out.println("6. Print the adjacency list of the current graph.");
        System.out.println("7. Save the adjacency list of the current graph.");
        System.out.println("8. Exit");
        System.out.println();

        while (true) {
            System.out.print("Please specify an action: ");
            Scanner keyboard = new Scanner(System.in);
            try {
                int index = Integer.parseInt(keyboard.nextLine());
                if (index >= 1 && index <= 8)
                    return index;
            } catch (Exception e) {

            }
            System.out.println("Invalid action");
        }


    }


    public static void main(String[] args) throws IOException {
        System.out.println("Welcome to this social network analysis system.");

        Graph graph = null;

        boolean exit = false;

        int action;
        boolean choose1 = false;

        do {
            action = printMenuWithAction();

            switch (action) {
                case 1: {
                    choose1 = true;
                    graph = new Graph();
                    HashMap<String, Vertex> vertexMap = new HashMap<String, Vertex>();
                    try {
                        BufferedReader reader = new BufferedReader(new FileReader(inFileAddress));
                        String line;

                        while ((line = reader.readLine()) != null) {
                            String[] tokens = line.split(":");
                            String sourceLabel = tokens[0].trim();
                            String[] targetLabels = tokens[1].split(",");
                            Vertex sourceVertex;

                            if (!vertexMap.containsKey(sourceLabel)) {
                                sourceVertex = new Vertex(sourceLabel);
                                graph.addVertex(sourceVertex);
                                vertexMap.put(sourceLabel, sourceVertex);
                            } else {
                                sourceVertex = vertexMap.get(sourceLabel);
                            }

                            for (String targetLabel : targetLabels) {
                                targetLabel = targetLabel.trim();
                                Vertex targetVertex;
                                if (!vertexMap.containsKey(targetLabel)) {
                                    targetVertex = new Vertex(targetLabel);
                                    graph.addVertex(targetVertex);
                                    vertexMap.put(targetLabel, targetVertex);
                                } else {
                                    targetVertex = vertexMap.get(targetLabel);
                                }
                                graph.addEdge(new Edge(sourceVertex, targetVertex));
                            }
                        }
                        System.out.format("#vertex: %d, #edges: %d\n", graph.getVertices().size(), graph.getEdges().size() / 2);
                        reader.close();
                    } catch (Exception e) {
                        System.err.println("Error on loading graph from file.");
                        e.printStackTrace();
                    }


                    break;
                }
                case 2: {
                    if (!choose1) {
                        System.out.println("The graph is not loaded yet.");
                        continue;
                    }
                    System.out.print("Please specify a root: ");
                    Scanner scanner = new Scanner(System.in);
                    String root = scanner.next();
                    Graph g = graph.SpanningTreeBuild(new Vertex(root));
                    if (g!=null)
                        g.print();
                    else System.out.println("Spanning tree cannot be found because the graph is not connected");
                    break;
                }
                case 3: {
                    if (!choose1) {
                        System.out.println("The graph is not loaded yet.");
                        continue;
                    }
                    if (graph.containCycle())
                        System.out.println("YES");
                    else
                        System.out.println("NO");

                    break;
                }
                case 4: {
                    if (!choose1) {
                        System.out.println("The graph is not loaded yet.");
                        continue;
                    }
                    if (graph.connected())
                        System.out.println("YES");
                    else
                        System.out.println("NO");
                    break;
                }
                case 5: {
                    if (!choose1) {
                        System.out.println("The graph is not loaded yet.");
                        continue;
                    }
                    System.out.print("Enter the first endpoint id: ");
                    String root = new Scanner(System.in).next();
                    System.out.print("Enter the second endpoint id: ");
                    String end = new Scanner(System.in).next();
                    graph.addEdge(new Edge(new Vertex(root), new Vertex(end)));
                    graph.addEdgeWithoutInfo(new Edge(new Vertex(end), new Vertex(root)));
                    break;
                }
                case 6: {
                    if (!choose1) {
                        System.out.println("The graph is not loaded yet.");
                        continue;
                    }
                    graph.print();
                    break;
                }
                case 7: {
                    if (!choose1) {
                        System.out.println("The graph is not loaded yet.");
                        continue;
                    }
                    System.out.print("Where to save the adjacency list of the current graph? ");
                    String outFileAddress = new Scanner(System.in).next();
                    graph.saveFile(outFileAddress);
                    System.out.println("The adjacency list is successfully saved to the specified file.");
                    break;
                }
                case 8: {
                    System.out.println("Bye bye!");
                    exit = true;
                    break;
                }
                default: {

                }

            }


        } while (!exit);

    }

}


