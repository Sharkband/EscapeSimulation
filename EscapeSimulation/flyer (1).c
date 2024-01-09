#include "defs.h"

//purpose: dynamically allocates and initializes one flyer, and adds it to escape's flyer collection 
//parameter escape is in used to get the flyers array
//paramter avatar is in used to set avatar
//parameter row is in used to set row of flyer
//paramter col is in used to set col of flyer
//parameter strength is used to set the strength of flyer
void spawnFlyer(EscapeType *escape, char avatar, int row, int col, int strength){
 
if(escape->flyers.size<MAX_ARR){
  
  FlyerType *tmpFlyer;
  tmpFlyer = (FlyerType*)malloc(sizeof(FlyerType));

  tmpFlyer->strength = strength;
  tmpFlyer->partInfo.avatar = avatar;
  setPos(&(tmpFlyer->partInfo.pos),row,col);
  
  addFlyer(&(escape->flyers), tmpFlyer);

 }
}

//purpose: adds flyer to escape's flyer collection
//parameter flyers is an in-out parameter used to set the elements and get size
//parameter flyer is an in used to set the elements of the array to flyer
//no return value
void addFlyer(FlyerArrayType *flyers, FlyerType *flyer){
 
 flyers->elements[flyers->size] = flyer;
 flyers->size +=1;

}

//purpose: computes flyer's next move in accordance to instruction 3.4, updates flyer's position, and deals with collisions with heroes
//parameter flyer is in-out used to set the position
//parameter escape is in used to computer hero direction
//no return values
void moveFlyer(FlyerType *flyer, EscapeType *escape){

 int col=flyer->partInfo.pos.col;
 int row=flyer->partInfo.pos.row;
	
 if(flyerIsDone(flyer)){

  if(flyer->partInfo.avatar == 'v'){

   int randInt = randomInt(3);
   row += 1;

   if(randInt ==0){
   }else if(randInt ==1){

    col += 1;

   }else{

    col += -1;

   }
  }else{

   int randInt = randomInt(4);
   int randUpDown = randomInt(100);

   if(randUpDown <50){

    row += (-1*randInt);

   }else{

    row += randInt;

   }

   int randIntCol = randomInt(3);

   int dir;
   computeHeroDir(escape,flyer, &dir);

   if(dir==DIR_SAME){
   }else if(dir ==DIR_LEFT){

    col += (-1*(randIntCol));

   }else{

    col += (randIntCol);

   }
  }
 }

 setPos(&(flyer->partInfo.pos) ,row,col);

}

//purpose computes direction (-1 for left, +1 for right, 0 for same) of closest hero that is still alive and participating; direction is returned using parameter 
//parameter: escape is in used to find the heros in the escape
//parameter: flyer is in used to get the distance between flyer and hero
//parameter: dir is out used to get the direction in which to move
//no return values
void computeHeroDir(EscapeType *escape, FlyerType *flyer, int *dir){
 
 int smallDis=MAX_COL;
 int distance;
 int tmpDirection;
 int smallDir;

 for(int i=0;i<escape->heroes.size;i++){
  
  distance = escape->heroes.elements[i]->partInfo.pos.col-flyer->partInfo.pos.col;
    
  if(distance  < 0){

   distance = distance*-1;
   tmpDirection = DIR_LEFT;

  }else if(distance  == 0 ){

   tmpDirection = DIR_SAME;

  }else{

   tmpDirection = DIR_RIGHT;

  }
  
  if(distance <= smallDis && (escape->heroes.elements[i]->partInfo.avatar != '+' && escape->heroes.elements[i]->partInfo.avatar != ' ')){

   smallDis = distance;
   smallDir = tmpDirection;

  }

 }
 *dir = smallDir;

}

//purpose: determines if a flyer has reached the ground
//parameter flyer is in used to check if the flyer is lower then the ground
//returns C_TRUE for yes its done and C_FALSE for its not done
int flyerIsDone(FlyerType *flyer){
 
 if(flyer->partInfo.pos.row <= MAX_ROW){
  
  return C_TRUE;

 }

 return C_FALSE;

}

//purpose: checks if a flyer with the given position has collided with a hero,and returns that hero as the return value (NULL if no collision)
//parameter pos is in to check if there is a collision
//parameter escape is in to get heros position
//returns the hero that got in a collision and null otherwise
HeroType* checkForCollision(PositionType *pos, EscapeType *escape){

 for(int i =0; i<escape->heroes.size; i++){

  if((escape->heroes.elements[i]->partInfo.pos.col==pos->col) && (escape->heroes.elements[i]->partInfo.pos.row==pos->row)){
   
   return escape->heroes.elements[i];

  }
 }

 return NULL;

}
