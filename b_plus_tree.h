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



};




#endif 
