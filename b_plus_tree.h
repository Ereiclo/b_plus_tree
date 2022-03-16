#ifndef B_PLUS_TREE
#define B_PLUS_TREE
#include <iostream>
using namespace std;



template<typename T>
class b_plus_tree{
  struct Node{
    T* keys;
    Node** children;
    Node* next{nullptr};
    int count{0};
    bool leaf = 0;
    int capacity;


    Node(int M_){
      keys = new T[M_-1];
      children = new Node*[M_];
      capacity = M_;

    }


    bool isLeaf(){
      return leaf;
    }


    ~Node(){
      delete[] keys;
      delete[] children;
    }



  };

  int M;
  Node* root{nullptr};


  b_plus_tree(int M){
    root = new Node(M);
    root->leaf = 1;
  }


  pair<pair<Node*,Node*>,T> leaf_division_pre(Node*& leaf, T data){
    Node* right = new Node(M);
    right->leaf = 1;
    int pos_subir = (M-1)/2;
    int temp = 0;
    int count = 0;
    int insert = depth_position(leaf,data);


    for(int i = pos_subir;i<= leaf->count ;++i){
      if(pos_subir > insert || i <= insert)
	right->keys[temp++] = i == insert ? data : leaf->keys[i];
      else 
	right->keys[temp++] = leaf->keys[i-1];

      if(i != insert) ++count;

    }
    right->count = temp;
    leaf->count -= count;
    key_insertion(leaf,insert,data);

    right->next = leaf->next;
    leaf->next = right;
    return {{leaf,right},right->keys[0]};

  }
  pair<pair<Node*,Node*>,T> leaf_division(Node*&leaf){
    Node* right = new Node(M);
    right->leaf = 1;
    int pos_subir = (M-1)/2;
    int temp = 0;

    for(int i = pos_subir;i< leaf->count;++i){
      right->keys[temp++] = leaf->keys[i];

    }
    right->count = temp;
    leaf->count -= temp;
    right->next = leaf->next;
    leaf->next = right;
    return {{leaf,right},right->keys[0]};


  }
  pair<pair<Node*,Node*>,T> node_division(Node*&node){
    Node* right = new Node(M);
    int pos_subir = (M-1)/2;
    int temp = 0;

    for(int i = pos_subir + 1;i<= node->count ;++i){
      if(i < node->count){
	right->keys[temp++] = node->keys[i];
	right->children[temp-1] = node->children[i];
      }
      else
	right->children[temp] = node->children[i];

    }
    right->count = temp;
    node->count -= (temp + 1);

    return {{node,right},node->keys[pos_subir]};
  }
  void node_overload(Node*& node, T data, Node* left, Node* right){

    if(node->capacity != M + 1){
      Node* new_node = new Node(M+1);
      for(int i = 0;i<= node->count;++i){
	if(i < node->count)
	  new_node->keys[i] = node->keys[i];

	new_node->children[i] = node->children[i];
      }
      new_node->next = node->next;
      new_node->count = node->count;
      new_node->leaf = node->leaf;
      delete[] node->keys;
      delete[] node->children;

      node = new_node;
    }

    int dp = depth_position(node, data);

    key_insertion(node,data,dp);
    if(!node->isLeaf())
      two_child_insertion(node, left, right, dp);

  }

  int depth_position(Node*& node,T data){
    int retorno = 0;

    while(retorno < node->count && node->keys[retorno] < data) ++retorno;


    return retorno;

  }

  void key_insertion(Node*& node, T data, int pos){
    int temp = node->count;
    while(temp != pos){
      node->keys[temp] = node->keys[temp-1];
    }
    node->keys[pos] = data;
    ++node->count;
  }

  void two_child_insertion(Node*& node, Node* left, Node* right,int pos){
    int temp = node->count;
    while(temp != pos+1){
      node->children[temp] = node->children[temp-1];
    }
    node->children[pos] = left;
    node->children[pos+1] = right;

  }


  void insert(Node*& actual,T data){
    if(actual->isLeaf()){
      if(actual->count < M - 1){
	key_insertion(actual, data, depth_position(actual,data));

      }else{
	if(actual == root){
	  auto retorno = leaf_division_pre(actual,data);
	  Node* new_root = new Node(M);
	  new_root->children[0] = retorno.first.first;
	  new_root->children[1] = retorno.first.second;
	  new_root->keys[0] = retorno.second; 
	  ++new_root->count;
	  root = new_root;



	}else{
	  node_overload(actual,data,nullptr,nullptr);

	}
      }
    }else{
      int ir = depth_position(actual,data);
      insert(actual->children[ir],data);
      Node* donde_fui = actual->children[ir];

      if(donde_fui->count < (M-1)/2){
	pair<pair<Node*,Node*>,T> retorno;
	if(donde_fui->isLeaf()){
	  retorno = leaf_division(donde_fui);

	}else{

	  retorno = node_division(donde_fui);

	}


	if(actual->count >= M-1){
	  node_overload(actual,retorno.second,retorno.first.first,retorno.first.second);
	  if(actual == root){
	    auto retorno2 = node_division(actual);
	    Node* new_root = new Node(M);
	    new_root->children[0] = retorno2.first.first;
	    new_root->children[1] = retorno2.first.second;
	    new_root->keys[0] = retorno2.second;
	    ++new_root->count;
	    root = new_root;
	  }
	}else{
	  key_insertion(actual,retorno.second,ir);
	  two_child_insertion(actual,retorno.first.first,retorno.first.second,ir);

	}
      }

    }

  }

  void insert(T data){
    insert(root,data);
  }


  void remove(T data){}

  void merge(Node*& nodo, Node* left, Node*right,int & depht_pos, T data){}
  void left_rot(Node*nodo,Node*left,Node* right,int & depht_pos,T data){}
  void right_rot(Node*nodo,Node*left,Node* right,int & depht_pos,T data){}


  void show_Range(){}


  bool find(){ return false;}


  void showInOrder(){
    auto temp = root;
    while(!temp->isLeaf()){
      temp = temp->children[0];
    }


    while(temp != nullptr){
      for(int i = 0;i< temp->count;++i)
	cout<<temp->keys[i]<<" ";
      cout<<" ";
      temp = temp->next;
    }


  }


  void showPreOrder(Node*actual){

    for(int i = 0;i<= actual->count;++i){
      if(i != actual->count)
	cout<<actual->keys[i]<<" ";
      if(!actual->isLeaf())
	showPreOrder(actual->children[i]);
    }

  }
  void showPreOrder(){
    showPreOrder(root);
  }


  void showPostOrder(Node*actual){
    for(int i = 0;i<= actual->count;++i){

      if(!actual->isLeaf())
	showPreOrder(actual->children[i]);
      if(i != actual->count)
	cout<<actual->keys[i]<<" ";
    }
  }
  void showPostOrder(){
    showPostOrder(root);

  }





};




#endif 
