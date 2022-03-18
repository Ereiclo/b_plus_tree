#include <iostream>
#include "b_plus_tree.h"

using namespace std;


int main(){
  b_plus_tree<int> bmas(5);


  //test remove 1


  bmas.insert(10);
  bmas.insert(20);
  bmas.insert(30);
  bmas.insert(40);
  bmas.insert(13);
  bmas.insert(11);
  bmas.insert(38);
  bmas.insert(43);
  bmas.insert(33);
  bmas.insert(36);
  bmas.insert(12);
  bmas.insert(19);
  bmas.insert(21);
  bmas.insert(23);
  bmas.insert(27);
  bmas.insert(31);
  bmas.insert(25);
  bmas.insert(35);
  bmas.insert(1);
  bmas.insert(2);
  bmas.insert(3);
  bmas.insert(34);
  bmas.insert(37);
  bmas.insert(45);
  bmas.insert(50);


  bmas.remove(35);
  bmas.remove(30);
  bmas.remove(23);
  bmas.remove(36);
  bmas.insert(120341);


  cout<<bmas.max()<<endl;
  cout<<bmas.min()<<endl;


  /* bmas.remove(36); */
  /* bmas.remove(38); */
  /* bmas.remove(40); */
  /* bmas.remove(20); */
  /* bmas.remove(23); */
  /* bmas.remove(21); */
  /* bmas.remove(13); */
  /* bmas.remove(11); */
  /* bmas.remove(12); */
  /* bmas.remove(19); */
  bmas.showInOrder();
  cout<<endl;
  bmas.showPreOrder();
  /* cout<<bmas.height(); */




  //test remove 2 
  /* bmas.insert(10); */
  /* bmas.insert(20); */
  /* bmas.insert(30); */
  /* bmas.insert(40); */
  /* bmas.insert(50); */
  /* bmas.insert(13); */
  /* bmas.insert(17); */
  /* bmas.insert(43); */
  /* bmas.insert(37); */
  /* bmas.insert(31); */
  /* bmas.insert(27); */
  /* bmas.insert(15); */
  /* bmas.insert(3); */
  /* bmas.insert(26); */

  /* bmas.showPreOrder(); */
  /* cout<<endl; */


  /* bmas.remove(30); */
  /* bmas.remove(15); */
  /* bmas.remove(20); */
  /* bmas.remove(13); */
  /* bmas.remove(3); */
  /* bmas.remove(40); */

  /* bmas.insert(39); */
  /* bmas.remove(31); */

  /* bmas.showPreOrder(); */


  /* bmas.show_Range(20,40); */



  //test insert
  /* bmas.insert(100); */
  /* bmas.insert(200); */
  /* bmas.insert(300); */
  /* bmas.insert(400); */
  /* bmas.insert(157); */
  /* bmas.insert(234); */
  /* bmas.insert(299); */
  /* bmas.insert(255); */
  /* bmas.insert(143); */
  /* bmas.insert(147); */
  /* bmas.insert(150); */
  /* bmas.insert(153); */
  /* bmas.insert(311); */
  /* bmas.insert(277); */
  /* bmas.insert(283); */
  /* bmas.insert(401); */
  /* bmas.insert(402); */
  /* bmas.insert(403); */
  /* bmas.insert(1); */
  /* bmas.insert(2); */
  /* bmas.insert(3); */
  /* bmas.insert(4); */
  /* bmas.insert(5); */
  /* bmas.insert(201); */
  /* bmas.insert(202); */
  /* bmas.insert(203); */
  /* bmas.insert(204); */
  /* bmas.insert(205); */
  /* bmas.insert(206); */

  /* bmas.showInOrder(); */

  /* cout<<bmas.find(200); */
  /* bmas.show_Range(211,312); */












  return 0;
}
