#include <iostream>
#include "b_plus_tree.h"

using namespace std;


int main(){
  b_plus_tree<int> bmas(4);

  bmas.insert(100);
  bmas.insert(200);
  bmas.insert(300);
  bmas.insert(400);
  bmas.insert(157);
  bmas.insert(234);
  bmas.insert(299);
  bmas.insert(255);
  bmas.insert(143);
  bmas.insert(147);
  bmas.insert(150);
  bmas.insert(153);
  bmas.insert(311);
  bmas.insert(277);
  bmas.insert(283);
  bmas.insert(401);
  bmas.insert(402);
  bmas.insert(403);
  bmas.insert(1);
  bmas.insert(2);
  bmas.insert(3);
  bmas.insert(4);
  bmas.insert(5);
  bmas.insert(201);
  bmas.insert(202);
  bmas.insert(203);
  bmas.insert(204);
  bmas.insert(205);
  bmas.insert(206);

  /* bmas.showInOrder(); */

  /* cout<<bmas.find(200); */
  /* bmas.show_Range(211,312); */



  return 0;
}
