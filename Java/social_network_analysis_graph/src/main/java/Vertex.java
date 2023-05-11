import java.util.ArrayList;
import java.util.Objects;

public class Vertex {

    private String name;

    public Vertex(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public boolean equals(Object x) {

        if (x instanceof Vertex) {
            return Objects.equals(name, ((Vertex) x).getName());
        }
        return false;
    }
}
