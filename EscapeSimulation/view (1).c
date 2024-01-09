#include "defs.h"

//purpose: top-level function for serializing hollow, printing and sending it client
//parameter: escape is and in paramter that is used to serilize the hollow and get the view socket
//no return values
void outputHollow(EscapeType *escape){

 char serialize[MAX_BUFF];

 serializeHollow(escape ,serialize);
 
 printf("%s", serialize);
 
 sendData(escape->viewSocket, serialize);

}

//purpose: initializes 2D grid with participant avatars in current positions
//parameter: escape is a in paramter to get the contents of flyers and heros
//paramter: grid is an out variable where we put all the contents into grid
//no return value
void initHollow(EscapeType *escape, char grid[][MAX_COL]){

 for(int i=0; i<MAX_ROW; i++){
  for(int j=0; j<MAX_COL; j++){
   grid[i][j] = ' ';
  }
 }
 
for(int i=0; i<escape->flyers.size; i++){

  grid[escape->flyers.elements[i]->partInfo.pos.row][escape->flyers.elements[i]->partInfo.pos.col] = escape->flyers.elements[i]->partInfo.avatar;

 }

 for(int i=0; i<escape->heroes.size; i++){

  grid[escape->heroes.elements[i]->partInfo.pos.row][escape->heroes.elements[i]->partInfo.pos.col] = escape->heroes.elements[i]->partInfo.avatar;

 }

}

//purpose: constructs 1D array with formatted Hollow output, containing all avatars in their positions, with borders, spacing and newlines 
//parameter escape is used to init the hollow as a in function
//parameter serialized is an out paramter used to get a entire string 
//no return value
void serializeHollow(EscapeType *escape, char *serialized){
 
 char grid[MAX_ROW][MAX_COL];
 initHollow(escape,grid);
 
 int numChars =0;

 for(int i =0; i<MAX_COL+2; i++ ){

  serialized[numChars] = '-';
  numChars +=1;

 }

 serialized[numChars] = '\n';
 numChars += 1;

 for(int i=0; i<MAX_ROW; i++){
  for(int j=0; j<MAX_COL; j++){

   if((j==0 && i== MAX_ROW-1) ){

    serialized[numChars] = '=';
    numChars +=1;
    serialized[numChars] = grid[i][j];

   }else if(j == 0){

    serialized[numChars] = '|';
    numChars +=1;
    serialized[numChars] = grid[i][j];
	   
   }else{

    serialized[numChars] = grid[i][j];

   }

    numChars += 1;

  }

  if(i == MAX_ROW-2){

   serialized[numChars] = '|';
   numChars += 1;
   
   char healthTim[MAX_BUFF];
   sprintf(healthTim ,"%d",escape->heroes.elements[0]->health);
   char timString[MAX_BUFF] = "   Timmy : ";
   strcat(timString, healthTim);

   for(int i=0; i<strlen(timString); i++){

    serialized[numChars] = timString[i];
    numChars += 1;

   }
   
  }else if(i==MAX_ROW-1){

   serialized[numChars] = '=';
   numChars += 1;
     
   char healthHar[MAX_BUFF];
   sprintf(healthHar ,"%d",escape->heroes.elements[1]->health);
   char harString[MAX_BUFF] = "   Harold : ";
   strcat(harString, healthHar);
   
   for(int i=0; i<strlen(harString); i++){

    serialized[numChars] = harString[i];
    numChars += 1;

   }
   
  }else{

   serialized[numChars] = '|';
   numChars += 1;

  }
  
  serialized[numChars] = '\n';
  numChars += 1;

 }
 
 for(int i =0; i<MAX_COL+2; i++ ){

  serialized[numChars] = '-';
  numChars +=1;

 }

 serialized[numChars] = '\n';
 numChars +=1;

 serialized[numChars] = '\0';
 
}


