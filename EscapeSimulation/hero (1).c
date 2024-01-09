#include "defs.h"

//purpose: dynamically allocates and initializes one hero
//parameter: hero is used out to initlize the fields of hero
//parameter: avater is in used to set the avatar
//parameter: col is in used to set col of hero
//parameter: name is in used to set name of hero
void initHero(HeroType **hero, char avatar, int col, char *name ){
 
 HeroType *tmpHero;
 tmpHero = (HeroType*)malloc(sizeof(HeroType));

 strcpy(tmpHero->name, name);
 tmpHero->health = MAX_HEALTH;
 tmpHero->dead = C_FALSE;
 tmpHero->partInfo.avatar = avatar;
 setPos(&(tmpHero->partInfo.pos), MAX_ROW-1, col);
 
 *hero = tmpHero;

}

//purpose: adds hero to escape's hero collection
//paramter: heroes is an in-out paramter used to set the hero and get the size
//parameter hero is used as in to set the element in the array to hero
//no return values
void addHero(HeroArrayType *heroes , HeroType *hero){

 heroes->elements[heroes->size]=hero;
 heroes->size = heroes->size+1;

}

//purpose: computes hero's next move in accordance to instruction 3.4, and updates hero's position 
//parameter: hero is used in-out to set the pos and to get the col 
//paramter: escape is used and in
//no return value
void moveHero(HeroType *hero , EscapeType *escape ){
 
 int col =hero->partInfo.pos.col;
 int row =MAX_ROW-1;

 int randInt = randomInt(10); 

 if(!heroIsSafe(hero)){
  if(hero->partInfo.avatar == '+'){
  }else if(strcmp(hero->name,"Timmy")){
   if(randInt <2){

    col += 1;

   }else if(randInt >=2 && randInt <5){

    col += -1;

   }else{

    col += 2;

   }
  }else{
   if(randInt <2){
   }else if(randInt ==2){

    col += 5;

   }else if(randInt ==3){

    col += -4;

   }else if(randInt >=4 && randInt <6){

    col += -2;

   }else{

    col += 3;

   }
  } 
 }

 setPos(&(hero->partInfo.pos), row, col);
 
}

//purpose: determines if a hero has successfully escaped the Hollow
//parameter: hero is an in paramter used to check if the hero is safe
//returns C_TRUE for safe and C_FALSE for not safe
int heroIsSafe(HeroType *hero){

 if(hero->partInfo.pos.col >= MAX_COL-1){

  hero->partInfo.avatar = ' ';
  return C_TRUE;

 }

  return C_FALSE;

}

//purpose: decreases hero's health by flyer's strength (if health gets negative, reset to 0)if hero dies, its avatar is changed
//paramter hero is an in-out paramter used to change the healh and get the fields
//paramter flyer is in used to get the strength
//no return values
void incurDamage(HeroType *hero, FlyerType *flyer){

 hero->health = hero->health-flyer->strength;
 
 if(hero->health <=0){

  hero->health = 0;
  hero->dead = C_TRUE;
  hero->partInfo.avatar ='+';

 }
}

//purpose sets a participant's position to given row/col, with values reset to closest edge if outside of range 
//paramter: pos is in-out parameter used to set position
//paramter: row is an in paramter used to set row
//paramter: col is and in paramter used to set col
//no return values
void setPos(PositionType *pos, int row, int col){
 if(col < 0){

  pos->col = 0;

 }else if(col > MAX_COL-1){

  pos->col = MAX_COL-1;

 }else if(row >= MAX_ROW){

  pos->row = MAX_ROW+1;

 }else if(row < 0){

  pos->row = 0;
	 	 
 }else{

  pos->row = row;
  pos->col = col;

 }
}

