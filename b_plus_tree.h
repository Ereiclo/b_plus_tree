#ifndef B_PLUS_TREE
#define B_PLUS_TREE



template<typename T>
class b_plus_tree{
  struct Node{
    T* keys;
    Node** children;
    Node* next{nullptr};


    Node(int M_){
      keys = new T[M_-1];
      children = new Node*[M_];

    }


    bool isLeaf(){
      return next == nullptr;
    }



  };

  int M;
  Node* root{nullptr};


  void leaf_division_pre(Node*& leaf, T data){}
  void leaf_division(Node*&leaf){}
  void node_division(Node*&leaf){}
  void node_overload(Node*& node, T data, Node* left, Node* right){}
  void depth_position(Node*& node,T data){}
  void key_insertion(Node*& node, T data, int pos){}
  void two_child_insertion(Node*& node, Node* left, Node* right,int pos){}


  void insert(T data){}


  void remove(T data){}

  void merge(Node*& nodo, Node* left, Node*right,int & depht_pos, T data){}
  void left_rot(Node*nodo,Node*left,Node* right,int & depht_pos,T data){}


  void show_Range(){}


  bool find(){ return false;}


  void showInOrder(){}


  void showPreOrder(){}


  void showPostOrder(){}





};




#endif 
