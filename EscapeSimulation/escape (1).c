#include "defs.h"

//purpose: top-level function for server process initializes the escape, contains game loop, handles escape result, cleans up
//no paramters
//no return values
void runEscape(){
 
 EscapeType *escape;
 escape =(EscapeType*)malloc(sizeof(EscapeType));
 initEscape(escape);

 while(1){

  if(escapeIsOver(escape)){
   break;
  }

  int randBird = randomInt(100);
  int randBirdRow = randomInt(5);
  int randBirdCol = randomInt(MAX_COL-1);
  int randBirdStr = randomInt(3)+3;

  if(randBird <= BIRD_SPAWN_RATE){

   spawnFlyer(escape, 'v', randBirdRow, randBirdCol, randBirdStr);

  }

  int randMonkey = randomInt(100);
  int randMonRow = randomInt(MAX_ROW-1);
  int randMonCol = randomInt(MAX_COL-1);
  int randMonStr = randomInt(4)+8;

  if(randMonkey <= MONKEY_SPAWN_RATE){

   spawnFlyer(escape, '@', randMonRow, randMonCol, randMonStr);

  }

  for(int i=0; i<escape->heroes.size;i++){

   moveHero(escape->heroes.elements[i] ,escape);
   heroIsSafe(escape->heroes.elements[i]);
  
  }
  
  for(int i=0; i<escape->flyers.size;i++){

   moveFlyer(escape->flyers.elements[i] ,escape);

   HeroType *hurtHero = checkForCollision(&(escape->flyers.elements[i]->partInfo.pos), escape);
   if(hurtHero != NULL){

    incurDamage(hurtHero, escape->flyers.elements[i]);

   }   
  }
  
  outputHollow(escape);
 
  usleep(OUTPUT_INTERVAL);

 }
 
 handleEscapeResult(escape);
 
 cleanupEscape(escape);
 
}

//purpose: determines if both heroes are dead or have escaped 
//paramter escape is in used to check if heros are dead or safe
//returns C_TRUE or C_FALSE for if the escape is over or not
int escapeIsOver(EscapeType *escape){
 
  if((escape->heroes.elements[0]->dead == C_TRUE || heroIsSafe(escape->heroes.elements[0])) && (escape->heroes.elements[1]->dead == C_TRUE || heroIsSafe(escape->heroes.elements[1])) ){
   
   return C_TRUE;
  
  }
   
 return C_FALSE;

}

//purpose: initializes escape, including seeding PRNG, initializing the hero and flyer arrays,allocating and initializing both heroes and adding them to the heroes array, 
//initializing sockets and blocking until client connection request is received
//parameter: escape is an in-out paramter used to set fields and used to get heros
//no return values 
void initEscape(EscapeType *escape){
 
 srand((unsigned)time(NULL));

 int listen;
 setupServerSocket(&listen);
 escape->listenSocket = listen;

 int viewSocket;
 acceptConnection(listen, &viewSocket);
 escape->viewSocket = viewSocket;


 HeroType **HeroArray;
 HeroArray = calloc(MAX_ARR, sizeof(HeroType*));
 escape->heroes.elements = HeroArray;

 escape->heroes.size =0;
 escape->flyers.size =0;
 
 int randIntTimmy = randomInt(5);

 HeroType *timmy;
 HeroType *harold;
 initHero(&timmy, 'T',(randIntTimmy),"Timmy" );

 int randIntHarold = randomInt(5);

 if(randIntTimmy == randIntHarold){
  randIntHarold += 1;
 }

 initHero(&harold, 'H', (randIntHarold),"Harold");

 addHero(&(escape->heroes), timmy);
 addHero(&(escape->heroes), harold);

}

//purpose: prints out and sends to client the outcome of the escape
//paramter: escape is an in paramter to get the name and check if the heros are dead
//no return values
void handleEscapeResult(EscapeType *escape){
 
  char escapeResult[MAX_BUFF];

  for(int i=0; i<escape->heroes.size; i++){

    char name[MAX_STR];
    strcpy(name ,escape->heroes.elements[i]->name);

   if(escape->heroes.elements[i]->dead==C_TRUE){

    strcat(escapeResult, strcat(name , " is dead \n"));

   }else{

    strcat(escapeResult, strcat(name, " escaped \n"));

   }
  }
  
  printf("%s", escapeResult);
  sendData(escape->viewSocket, escapeResult); 

}

//purpose cleans up escape, including deallocating required memory, sending termination (quit) message to client, and closing sockets 
//paramter escape is an in paramter used to close and free all the fields on escape
//no return values
void cleanupEscape(EscapeType *escape){
 
 char quit[MAX_BUFF];
 strcpy(quit, "quit\n"); 
 sendData(escape->viewSocket, quit);
 
 close(escape->viewSocket);
 close(escape->listenSocket);

 for(int i=0; i<escape->heroes.size; i++){

   free(escape->heroes.elements[i]);

 }

 for(int i=0; i<escape->flyers.size; i++){

   free(escape->flyers.elements[i]);

 }

 free(escape->heroes.elements);
 free(escape);
 
}
