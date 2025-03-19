#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Node {
public:
    T val;
    vector<Node<T> *> next;
    vector<int> lengths;
    Node(T _val, int h) : val(_val) {
        next = vector<Node<T> *>(h + 1);
        lengths = vector<int>(h + 1);
    }
    int get_height() { return next.size() - 1; }
};

template<typename T>
class SkipListList {
public:
    int MAX_LEVEL;
    double PROB;
    int level;
    int size;
    Node<T> *head;

    SkipListList (int max_level, double prob) : MAX_LEVEL(max_level), PROB(prob) {
        level = size = 0;
        head = new Node<T>(T(), MAX_LEVEL);
    }

    int get_size() { return size; }

    int random_level() {
        int h = 0;
        double r = rand() / (double) RAND_MAX;
        while (h < MAX_LEVEL && r < PROB) {
            h++;
            r = rand() / (double) RAND_MAX;
        }
        return h;
    }

    Node<T> *find(int index) {
        Node<T> *u = head;
        int pos = -1; // The index of the current node in list 0 (layer_0)
        for (int i = level; i >= 0; i--) {
            while (u->next[i] != nullptr && pos + u->lengths[i] < index) {
                pos += u->lengths[i];
                u = u->next[i];
            }
        }
        return u;
    }

    Node<T> *add(int index, Node<T> *w) {
        Node<T> *u = head;
        int k = w->get_height();
        int pos = -1; // Index of u
        for (int i = level; i >= 0; i--) {
            while (u->next[i] != nullptr && pos + u->lengths[i] < index) {
                pos += u->lengths[i];
                u = u->next[i];
            }
            u->lengths[i]++; // To account for new node in list 0
            if (i <= k) {
                w->next[i] = u->next[i];
                u->next[i] = w;
                w->lengths[i] = u->lengths[i] - index + pos;
                u->lengths[i] = index - pos;
            }
        }
        size++;
        return u;
    }

    T get(int index) {
        if (index < 0 || index >= size) return T();
        return find(index)->next[0]->val;
    }

    T set(int index, T val) {
        if (index < 0 || index >= size) return T();
        Node<T> *u = find(index);
        T y = u->val;
        u->val = val;
        return y;
    }

    void add(int index, T val) {
        if (index < 0 || index > size) return;
        Node<T> *w = new Node<T>(val, random_level());
        if (w->get_height() > level) level = w->get_height();
        add(index, w);
    }

    T remove(int index) {
        if (index < 0 || index >= size) return T();
        T val = T();
        Node<T> *u = head;
        int pos = -1;
        for (int i = level; i >= 0; i--) {
            while (u->next[i] != nullptr && pos + u->lengths[i] < index) {
                pos += u->lengths[i];
                u = u->next[i];
            }
            u->lengths[i]--;
            if (pos + u->lengths[i] + 1 == index && u->next[i] != nullptr) {
                val = u->next[i]->val;
                u->lengths[i] += u->next[i]->lengths[i];
                u->next[i] = u->next[i]->next[i];
                if (u == head && u->next[i] == nullptr) {
                    level--;
                }
            }
        }
        size--;
        return val;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    srand(time(0));
    SkipListList<int> s(10, 0.5);
    s.add(0, 5);
    s.add(0, 6);
    cout << s.get(0) << '\n';
    cout << s.get(1) << '\n';
    cout << s.remove(0) << '\n';
    cout << s.get(0) << '\n';
}
