template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList();

  void PushFront(const T& value);
  void InsertAfter(Node* node, const T& value);
  void RemoveAfter(Node* node);
  void PopFront();

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};

template <typename T>
LinkedList<T>::~LinkedList() {
  while (head) {
    PopFront();
  }
}

template <typename T>
void LinkedList<T>::PushFront(const T& value) {
  auto node = new Node{value};
  node->next = head;
  head = node;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& value) {
  if (node) {
    auto new_node = new Node{value};
    new_node->next = node->next;
    node->next = new_node;
  } else {
    PushFront(value);
  }
}

template <typename T>
void LinkedList<T>::RemoveAfter(Node* node) {
  if (!node) {
    PopFront();
  } else if (node->next) {
    auto removing_node = node->next;
    node->next = removing_node->next;
    delete removing_node;
  }
}

template <typename T>
void LinkedList<T>::PopFront() {
  if (head) {
    Node* new_head = head->next;
    delete head;
    head = new_head;
  }
}
