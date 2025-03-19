import java.lang.reflect.Array;

import java.util.Comparator;

public class SkipListPQ<T> {
    private final int maxLevel;
    private final double prob;
    private final Comparator<T> comp;

    private int level;
    private int size;
    Node<T> head;

    public SkipListPQ(int maxLevel, double prob, Comparator<T> comp) {
        this.maxLevel = maxLevel;
        this.prob = prob;
        this.comp = comp;
        level = size = 0;
        head = new Node<T>(null, maxLevel);
    }

    public int getSize() { return size; }

    private int randomLevel() {
        int h = 0;
        double r = Math.random();
        while (h < maxLevel && r < prob) {
            h++;
            r = Math.random();
        }
        return h;
    }

    @SuppressWarnings("unchecked")
    public void push(T x) {
        Node<T> u = head;
        Node<T>[] update = (Node<T>[]) Array.newInstance(Node.class, maxLevel + 1);

        for (int i = level; i >= 0; i--) {
            // Go through until the next value is not less than x
            while (u.next[i] != null && comp.compare(u.next[i].getVal(), x) < 0) {
                u = u.next[i];
            }
            update[i] = u;
        }

        int h = randomLevel();
        if (h > level) {
            // Extend the current level of the skip list
            for (int i = level + 1; i <= h; i++) {
                update[i] = head;
            }
            level = h;
        }

        Node<T> n = new Node<T>(x, h);
        for (int i = 0; i <= h; i++) {
            n.next[i] = update[i].next[i];
            update[i].next[i] = n;
        }
        size++;
    }

    public T top() {
        if (size == 0) return null;
        return head.next[0].getVal();
    }

    public boolean pop() {
        if (size == 0) return false;
        for (int i = level; i >= 0; i--) {
            // We only remove from the head:
            if (head.next[i] == null) continue;

            head.next[i] = head.next[i].next[i];
            if (head.next[i] == null) {
                // Skip list size has gone down
                level--;
            }
        }
        size--;
        return true;
    }
}
