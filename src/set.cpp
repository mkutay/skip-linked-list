#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Node {
public:
  T val;
  vector<Node<T> *> next;
  Node(T _val, int h) : val(_val) {
    next = vector<Node<T> *>(h + 1);
  }
  int get_height() { return next.size(); }
};

template<typename T>
class SkipListSet {
public:
  int MAX_LEVEL;
  double PROB;
  int level;
  int size;
  Node<T> *head;

  SkipListSet(int max_level, double prob) : MAX_LEVEL(max_level), PROB(prob) {
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

  void insert(T x) {
    Node<T> *u = head;
    vector<Node<T> *> update(MAX_LEVEL + 1);
    for (int i = level; i >= 0; i--) {
      while (u->next[i] != nullptr && u->next[i]->val < x) {
        u = u->next[i];
      }
      update[i] = u;
    }

    u = u->next[0];
    // We are assuming that the set does not contain duplicates
    if (u != nullptr && u->val == x) return;

    int h = random_level();
    if (h > level) {
      // We need to increase the height of the skip list
      for (int i = level + 1; i <= h + 1; i++) {
        update[i] = head;
      }
      level = h;
    }

    Node<T> *n = new Node<T>(x, h);
    for (int i = 0; i <= h; i++) {
      n->next[i] = update[i]->next[i];
      update[i]->next[i] = n;
    }

    size++;
  }

  T find(T x) {
    Node<T> *u = head;
    for (int i = level; i >= 0; i--) {
      while (u->next[i] != nullptr && u->next[i]->val < x) {
        u = u->next[i];
      }
    }
    u = u->next[0];
    if (u != nullptr && u->val == x) return u->val;
    return T();
  }

  bool remove(T x) {
    Node<T> *u = head;
    bool removed = false;
    for (int i = level; i >= 0; i--) {
      while (u->next[i] != nullptr && u->next[i]->val < x) {
        u = u->next[i];
      }
      if (u->next[i] != nullptr && u->next[i]->val == x) {
        removed = true;
        u->next[i] = u->next[i]->next[i];
        if (u == head && u->next[i] == nullptr) {
          // Skip list size has gone down
          level--;
        }
      }
    }
    if (removed) size--;
    return removed;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  srand(time(0));
  SkipListSet<int> s(10, 0.5);
  s.insert(2);
  s.insert(2);
  cout << s.find(2) << '\n';
  s.insert(3);
  s.insert(4);
  s.insert(5);
  cout << s.find(4) << '\n';
  s.insert(1);
  cout << s.find(10) << '\n';
  s.remove(4);
  cout << s.find(4) << '\n';
  cout << s.find(3) << '\n';
}
