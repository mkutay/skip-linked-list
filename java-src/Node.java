import java.lang.reflect.Array;

public class Node<T> {
    private final T val;
    private final int h;
    public Node<T>[] next;

    @SuppressWarnings("unchecked")
    public Node(T val, int h) {
        this.h = h;
        this.val = val;
        this.next = (Node<T>[]) Array.newInstance(Node.class, h + 1);
    }

    T getVal() { return val; }
    int getHeight() { return h; }
}
