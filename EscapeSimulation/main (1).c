#include "defs.h"

int main(int argc, char *argv[])
{
 if(argc <= 1){

  runEscape();

 }else{
  
  viewEscape(argv[1]);

 }
 return(0);
}

//purpose: to make a random number between 0 and the max
//paramter: max is an in paramter to make the upper bound on random generator
//returns the random int
int randomInt(int max)
{
 return(rand() % max);
}

