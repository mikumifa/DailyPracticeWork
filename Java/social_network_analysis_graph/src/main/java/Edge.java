import java.util.Objects;

public class Edge {
    private Vertex u;
    private Vertex v;

    public Edge(Vertex _u, Vertex _v) {
        u = _u;
        v = _v;
    }

    public Vertex getU() {
        return u;
    }

    public Vertex getV() {
        return v;
    }

    public boolean equals(Object o) {
        if (o instanceof Edge) {
            return Objects.equals(u.getName(), ((Edge) o).getU().getName()) && Objects.equals(v.getName(), ((Edge) o).getV().getName());
        }
        return false;
    }
}
