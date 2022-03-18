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


  public:
  b_plus_tree(int M_){
    M = M_;
    root = new Node(M);
    root->leaf = 1;

  }

  private:

  pair<pair<Node*,Node*>,T> leaf_division_pre(Node*& leaf, T data){
    Node* right = new Node(M);
    right->leaf = 1;
    int pos_subir = M % 2 == 0 ? M/2 :  (M-1)/2;
    int temp = 0;
    int count = 0;
    int insert = depth_position(leaf,data);


    for(int i = pos_subir;i<= leaf->count ;++i){
      //if(pos_subir > insert || i <= insert)
      if(i <= insert)
	right->keys[temp++] = i == insert ? data : leaf->keys[i];
      else 
	right->keys[temp++] = leaf->keys[i-1];

      if(i != insert) ++count;

    }
    right->count = temp;
    leaf->count -= count;
    if(pos_subir > insert){
      key_insertion(leaf,data,insert);
    }

    right->next = leaf->next;
    leaf->next = right;
    return {{leaf,right},right->keys[0]};

  }
  pair<pair<Node*,Node*>,T> leaf_division(Node*&leaf){
    Node* right = new Node(M);
    right->leaf = 1;
    int pos_subir = M % 2 == 0 ? M/2 :  (M-1)/2;
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

    int pos_subir = M % 2 == 0 ? M/2 :  (M-1)/2;

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
      T* n_keys = new T[M];
      Node** n_children = new Node*[M+1];

      for(int i = 0;i<= node->count;++i){
	if(i < node->count)
	  n_keys[i] = node->keys[i];

	n_children[i] = node->children[i];
      }
      delete[] node->keys;
      delete[] node->children;

      node->keys = n_keys;
      node->children = n_children;
      node->capacity = M+1;

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
      --temp;
    }
    node->keys[pos] = data;
    ++node->count;
  }

  void two_child_insertion(Node*& node, Node* left, Node* right,int pos){
    int temp = node->count;
    while(temp != pos+1){
      node->children[temp] = node->children[temp-1];
      --temp;
    }
    node->children[pos] = left;
    node->children[pos+1] = right;

  }

  public:

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

      if(donde_fui->count > M-1){
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

  void remove(T data){
    if(root->count == 0) return;
    Node* temp = nullptr;
    int pos = -1;
    remove(root,data,temp,pos);
  }


  int height(){
    int count = 0;
    auto temp = root;
    while(!temp->isLeaf()){
      temp = temp->children[0];
      ++count;
    }
    return count;
  }


  private:

  void remove(Node*& actual,T data,Node*&cambiar,int&pos){
    if(actual->isLeaf()){
      int dp = depth_position(actual,data) + 1;

      while(dp < actual->count){
	actual->keys[dp-1] = actual->keys[dp];
	++dp;
      }
      --actual->count;
    }else{
      int dp = depth_position(actual,data);

      if(actual->keys[dp] == data){
	cambiar = actual;
	pos = dp;
	dp = dp+1;
      }
      auto donde_ire = actual->children[dp];
      remove(donde_ire,data,cambiar,pos);


      if(donde_ire->count < (M-1)/2){

	if(dp > 0 && actual->children[dp-1]->count > (M-1)/2) {
	  right_rot(actual,actual->children[dp-1],actual->children[dp],dp-1);

	}
	else if( dp < actual->count && actual->children[dp+1]->count > (M-1)/2 ){
	  left_rot(actual,actual->children[dp],actual->children[dp+1],dp);
	}else{

	  if(cambiar == actual && donde_ire->isLeaf()) cambiar = nullptr;
	  if(dp > 0){



	    merge(actual,actual->children[dp-1],actual->children[dp],dp-1);
	    donde_ire = actual->children[dp-1];

	  }else if(dp < actual->count){

	    merge(actual,actual->children[dp],actual->children[dp+1],dp);
	  }

	}

      }

      if(cambiar != nullptr && donde_ire->isLeaf() ){
	cambiar->keys[pos] = donde_ire->keys[0];
	cambiar = nullptr;
	pos = -1;

      }





    }
  }

  void merge(Node*& nodo, Node* left, Node*right,int  depht_pos){
    if(!left->isLeaf()){
      left->keys[left->count++] = nodo->keys[depht_pos];

      int temp_c = left->count;

      for(int i = 0;i<= right->count;++i){
	left->children[temp_c++] = right->children[i];
      }
    }else{
      left->next = right->next;
    }

    for(int i = 0;i < right->count;++i){
      left->keys[left->count++] = right->keys[i];

    }

    delete[] right->keys;
    delete[] right->children;

    if(nodo == root && nodo->count == 1){
      delete[] nodo->keys;
      delete[] nodo->children;
      nodo = left; 
    }else{
      int dp = depht_pos + 1;
      while(dp < nodo->count){
	nodo->keys[dp-1] = nodo->keys[dp];
	nodo->children[dp] = nodo->children[dp+1];
	++dp;
      }
      --nodo->count;

    }

  }
  void left_rot(Node*&nodo,Node*&left,Node*& right,int  depht_pos){
    if(!left->isLeaf()){
      key_insertion(left,nodo->keys[depht_pos],left->count);
      two_child_insertion(left, left->children[left->count-1],right->children[0], left->count-1);
      nodo->keys[depht_pos] = right->keys[0];

      int dp = 1;
      while(dp <= right->count){
	if(dp < right->count)
	  right->keys[dp-1] = right->keys[dp];
	right->children[dp-1] = right->children[dp];
	++dp;
      }
      --right->count;

    }else{
      key_insertion(left,right->keys[0],left->count);
      int dp = 1;
      while(dp < right->count){
	right->keys[dp-1] = right->keys[dp];
	++dp;
      }
      --right->count;
      nodo->keys[depht_pos] = right->keys[0];


    }

  }
  void right_rot(Node*&nodo,Node*&left,Node*& right,int depht_pos){
    if(!left->isLeaf()){

      key_insertion(right,nodo->keys[depht_pos],0);

      two_child_insertion(right, left->children[left->count],right->children[0], 0);

      nodo->keys[depht_pos] = left->keys[left->count-1];

      --left->count;

    }else{


      key_insertion(right,left->keys[left->count -1],0);
      --left->count;
      nodo->keys[depht_pos] = right->keys[0];


    }

  }

  pair<Node*,int> findSucc(T data){
    auto temp = root;


    while(!temp->isLeaf()){
      int ir = depth_position(temp,data);

      if(ir < temp->count && temp->keys[ir] == data) temp = temp->children[ir+1];
      else temp = temp->children[ir];
    }

    for(int i = 0;i< temp->count;++i){
      if(temp->keys[i] >= data)
	return {temp,i};
    }

    return {temp,temp->count};
  }

  public:


  void show_Range(T begin, T end){
    if(begin == end) cout<<begin;
    else if(begin > end) return;


    auto buscar = findSucc(begin);
    if(buscar.first != nullptr){
      int it = buscar.second;
      auto temp = buscar.first;

      while(temp->keys[it] <= end){
	if(it != temp->count)
	  cout<<temp->keys[it++]<<" ";
	if(it == temp->count){
	  if(temp->next == nullptr) return;
	  temp = temp->next;
	  it = 0;
	}

      }


    }

  }

  T min(){
    auto temp = root;
    while(!temp->isLeaf()){
      temp = temp->children[0];
    }

    return temp->keys[0];
    return 0;

  }

  T max(){
    auto temp = root;
    while(!temp->isLeaf()){
      temp = temp->children[temp->count];
    }

    return temp->keys[temp->count-1];

  }



  bool find(T data){
    auto temp = root;


    while(!temp->isLeaf()){
      int ir = depth_position(temp,data);
      if(ir < temp->count && temp->keys[ir] == data) return true;

      temp = temp->children[ir];
    }

    for(int i = 0;i< temp->count;++i){
      if(temp->keys[i] == data)
	return true;
    }

    return false;
  }


  void showInOrder(){
    auto temp = root;
    while(!temp->isLeaf()){
      temp = temp->children[0];
    }


    while(temp != nullptr){
      for(int i = 0;i< temp->count;++i)
	cout<<temp->keys[i]<<" ";
      cout<<"\n";
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
