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


    Node(int M_){
      keys = new T[M_-1];
      children = new Node*[M_];

    }


    bool isLeaf(){
      return leaf;
    }



  };

  int M;
  Node* root{nullptr};


  pair<pair<Node*,Node*>,T> leaf_division_pre(Node*& leaf, T data){}
  void leaf_division(Node*&leaf){}
  void node_division(Node*&node){}
  void node_overload(Node*& node, T data, Node* left, Node* right){}
  void depth_position(Node*& node,T data){}
  void key_insertion(Node*& node, T data, int pos){}
  void two_child_insertion(Node*& node, Node* left, Node* right,int pos){}


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
	  auto retorno = leaf_division(actual);
	  node_overload(actual,retorno.second,retorno.first.first,retorno.first.second);

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
