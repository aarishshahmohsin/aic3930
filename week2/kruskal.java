import java.util.Arrays;
import java.util.Scanner;

class Edge implements Comparable<Edge> {
    int source, destination, weight;

    public Edge(int source, int destination, int weight) {
        this.source = source;
        this.destination = destination;
        this.weight = weight;
    }

    @Override
    public int compareTo(Edge otherEdge) {
        return this.weight - otherEdge.weight;
    }
}

public class kruskal {
    int vertices, edges;
    Edge[] edgeList;
    int[] parent;
    int[] size;

    public kruskal(int vertices, int edges) {
        this.vertices = vertices;
        this.edges = edges;
        edgeList = new Edge[edges];
        parent = new int[vertices];
        size = new int[vertices];
    }

    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
    }

    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);

        if (a != b) {
            if (size[a] < size[b]) {
                parent[a] = b;
                size[b] += size[a];
            } else {
                parent[b] = a;
                size[a] += size[b];
            }
        }
    }

    public void kruskalMST() {
        
        Arrays.sort(edgeList);

        for (int v = 0; v < vertices; v++) {
            make_set(v);
        }

        int x = 0;

        for (Edge e: edgeList) {
            if (x == vertices - 1) break;
            if (find_set(e.source) != find_set(e.destination)) {
                System.out.println("source: " + e.source + " dest: " + e.destination + " wt: " + e.weight);
                union_sets(e.source, e.destination);
                x++;
            }
        }
    }

    // public static void main(String[] args) {

    //     Scanner scanner = new Scanner(System.in);

    //     System.out.println("Enter the number of vertices");
    //     int vertices = scanner.nextInt();

    //     System.out.println("Enter the number of edges ");
    //     int edges = scanner.nextInt();

    //     kruskal graph = new kruskal(vertices, edges);

    //     System.out.println("Enter u, v, w");
    //     for (int i = 0; i < edges; i++) {
    //         int source = scanner.nextInt();
    //         int destination = scanner.nextInt();
    //         int weight = scanner.nextInt();
    //         graph.edgeList[i] = new Edge(source, destination, weight);
    //     }

    //     graph.kruskalMST();
    //     scanner.close();

    // }

    public static void main(String[] args) {
        int vertices = 4;
        int edges = 5;
        kruskal graph = new kruskal(vertices, edges);

        graph.edgeList[0] = new Edge(0, 1, 10);
        graph.edgeList[1] = new Edge(0, 2, 6);
        graph.edgeList[2] = new Edge(0, 3, 5);
        graph.edgeList[3] = new Edge(1, 3, 15);
        graph.edgeList[4] = new Edge(2, 3, 4);

        graph.kruskalMST();
    }
}