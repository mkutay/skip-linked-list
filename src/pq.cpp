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
class SkipListPQ {
public:
  int MAX_LEVEL;
  double PROB;
  int level;
  int size;
  Node<T> *head;

  SkipListPQ(int max_level, double prob) : MAX_LEVEL(max_level), PROB(prob) {
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

  void push(T x) {
    Node<T> *u = head;
    vector<Node<T> *> update(MAX_LEVEL + 1);
    for (int i = level; i >= 0; i--) {
      while (u->next[i] != nullptr && u->next[i]->val < x) {
        u = u->next[i];
      }
      update[i] = u;
    }

    u = u->next[0];
    // We can contain duplicates

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

  T top() {
    if (size == 0) return T();
    return head->next[0]->val;
  }

  bool pop() {
    if (size == 0) return false;
    for (int i = level; i >= 0; i--) {
      // We only remove from the head
      if (head->next[i] != nullptr) {
        head->next[i] = head->next[i]->next[i];
        if (head->next[i] == nullptr) {
          // Skip list size has gone down
          level--;
        }
      }
    }
    return true;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  srand(time(0));
  SkipListPQ<int> s(10, 0.5);
  s.push(2);
  s.push(2);
  cout << s.top() << '\n';
  s.push(3);
  s.push(4);
  s.push(5);
  cout << s.top() << '\n';
  s.push(1);
  cout << s.top() << '\n';
  s.pop();
  cout << s.top() << '\n';
  s.pop();
  s.pop();
  cout << s.top() << '\n';
  // Should output: 2 2 1 2 3
}
