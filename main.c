//
//  main.c
//  cs220 project1
//
//  Created by Ezgi Yuksektepe on 2/13/16.
//  Copyright © 2016 Ezgi Yuksektepe. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <assert.h>

/*-----------------------------------------------------------------------------------------------------
 A program to play tic-tac-toe.

 ----------------------------------------------------------------------------------------------*/
#define STATE_TIE 3*3*3*3*3*3*3*3*3
#define STATE_XWIN STATE_TIE+1
#define STATE_OWIN STATE_TIE+2
#define DBG 1

int game[3][3];
int winArray[9];
int defArray[9];

void CalcWDP(int index, int me, int n1, int n2);
void updateWinDef(int index, int win, int defeat);
void horizontalCheck(int index, int me, int i, int j);
void verticalCheck(int index,int me, int i, int j);
void dLeftCheck(int index, int me, int i, int j);
void dRightCheck(int index, int me, int i, int j);



short int myTurn(short int state, char me);
short int theirTurn(short int state, char them);
short int checkWin(short int state);
short int addState(short int state, char pos, char xo);
char getState(short int state, char pos);
void fprintState(short int state);
char p2c(short int state,char pos);

int main(int argc,char **argv) {
    
    setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);
    
    char me=0; // Am I X or O... don't know yet
    char them=0; // Is my opponent X or O
    
    if (argc<2) {
        fprintf(stderr,"Please specify whether %s should play X or O.\n",
                argv[0]);
        return 1; /* Issue a non-zero return code to indicate an error */
    }
    
    if (argv[1][0]=='X') {
        me=1;
        them=2;
    } else if (argv[1][0]=='O') {
        me=2;
        them=1;
    } else {
        fprintf(stderr,"Please enter either X or O as the first argument to %s\n",
                argv[0]);
        return 1;
    }
    
    short int state=0; // Current state... starts off empty
    int turn=1; // Whose turn is it?  X or O?
    
    while(state<STATE_TIE) {
        
        if (DBG) {
            fprintf(stderr,"It's %c's turn...\n",(turn==1)?'X':'O');
        }
        
        // printf("State before game : %d",state);
        
        if (me==turn) state = myTurn(state,me);
        else state=theirTurn(state,them);
        
        printf("%d\n",state); // Write state after each move to standard out
        state=checkWin(state);
        
        if (turn==1) turn=2; // X just went... O next
        else turn=1; // O just went... X next
    }
    printf("%d\n",state); // Write final state to standard out
    
    if (state==STATE_TIE) fprintf(stderr,"Good game, but you didn't beat me.... it's a tie.\n");
    else if (state==(STATE_TIE+me))
        fprintf(stderr,"Got you this time!... I won.\n");
    else
        fprintf(stderr,"You got me this time... you won.\n");
    
    return 0;
}

short int myTurn(short int state, char me) {

    int m;
    if(me== '1'){
        
        m= 1;
        
    }
    else{
        
        m = 2;
        
    }
    int g;
    
    for(g =0;g<9;g++)
    {
        if(winArray[g]!=-1)
            winArray[g]=0;
        
        if(winArray[g]!=-1)
            defArray[g]=0;
    }
    
    int i,j,k;
    k=0;
    
    
    
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            game[i][j]=getState(state, (char)k);
            k++;
        }
    }
    
    
    k=0;i=0;j=0;
    
    
    
    
    
    for(i=0; i<3; i++){
        
        for(j=0; j<3; j++){
           // printf("\n #######  About to perform checks");
            //game[i][j] = getState(state, (char)k);
            //printf("\n%d",game[i][j]);
            if(game[i][j]==0){
                
                horizontalCheck(k, m, i, j);
                verticalCheck(k, m, i, j);
                dLeftCheck(k, m, i, j);
                dRightCheck(k, m, i, j);
            }
           /* else
            {
                printf("\nValue is not 0\n");
            }*/
            k++;
        }
        
    }
    
   /* for(int g=0;g<9;g++)
    {
        printf("%d  %d \n",winArray[g],defArray[g]);
    }*/
    
    
    int x,y,winState, defState;
    winState=0;
    defState=0;
    int winMax=0, defMax=0;
    for(x=0; x<9; x++){
        
        if(winArray[x] > winMax){
            
            winMax = winArray[x];
            winState = x;
            
        }
    }
    
    for(y=0; y<9; y++){
        
        if(defArray[y] > defMax){
            
            defMax = defArray[y];
            defState = y;
            
        }
    }
    
    int final;
    final=0;
    
    if(winMax==100){
        
        final = winState;
        
    }
    
    else{
        
        if(winMax > defMax){
            
            final = winState;
            
        }
        
        else{
            
            final= defState;
            
        }
        
    }
    
   /* printf("After Calcs\n");
    for(int g=0;g<9;g++)
    {
        printf("%d  %d \n",winArray[g],defArray[g]);
    }*/
    
    winArray[final]=-1;
    defArray[final]=-1;
    
    /*printf("After -1\n");
    for(int g=0;g<9;g++)
    {
        printf("%d  %d \n",winArray[g],defArray[g]);
    }*/
    
    
    
    while(getState(state, (char)final)!=(char)0)
    {
        if(final>8)
        { final=0;}
        else
        {   final++;}
    }
    
    
   // printf("\n@@@@@@@@@@@@  final Pick : %d @@@@@@@@@@@@@@",final);
    return addState(state, (char)final, me); // Return an updated state
}

short int theirTurn(short int state, char them) {
    int pos=9; // Position they choose... initialized to an invalid position
    char me;
    if (them==1) me=2; else me=1;
    fprintState(state); // Print out the current board to standard error
    fprintf(stderr,"Enter the position for the next %c: ",(them==1)?'X':'O'); // write a prompt to stderr
    assert(!feof(stdin));
    if (1!=scanf("%d",&pos)) { // Read opponents choice from standard input, and save it in pos
        fprintf(stderr,"Illegal or no position entered... I win!\n");
        return STATE_TIE+me;
    }
    if (DBG) {
        fprintf(stderr,"User asked for a %c at position %d\n",(them==1)?'X':'O',pos);
    }
    if ((pos>8) || (pos<0)) {
        fprintf(stderr,"Illegal position of %d must be 0-8... I win!\n",pos);
        return STATE_TIE+me;
    }
    if (0!=getState(state,pos)) {
        fprintf(stderr,"Illegal position of %d already taken... I win!\n",pos);
        return STATE_TIE+me;
    }
    return addState(state,pos,them);
}

short int checkWin(short int state) {
    /* Checks state to see if there is a winner or a tie */
    char ul=getState(state,0); // Get the upper left corner value
    if (ul!=0) {
        if ((ul==getState(state,1)) && (ul==getState(state,2)))
            return STATE_TIE+ul;
        if ((ul==getState(state,4)) && (ul==getState(state,8)))
            return STATE_TIE+ul;
        if ((ul==getState(state,3)) && (ul==getState(state,6)))
            return STATE_TIE+ul;
    }
    
    char ce=getState(state,4); // Get the center square value
    if (ce!=0) {
        if ((ce==getState(state,3)) && (ce==getState(state,5)))
            return STATE_TIE+ce;
        if ((ce==getState(state,1)) && (ce==getState(state,7)))
            return STATE_TIE+ce;
        if ((ce==getState(state,2)) && (ce==getState(state,6)))
            return STATE_TIE+ce;
    }
    
    char lr=getState(state,8); // Get the lower right value
    if (lr!=0) {
        if ((lr==getState(state,6)) && (lr==getState(state,7)))
            return STATE_TIE+lr;
        if ((lr==getState(state,2)) && (lr==getState(state,5)))
            return STATE_TIE+lr;
    }
    
    /* No winner... maybe a tie? */
    int pos;
    for(pos=0;pos<9;pos++) {
        if (0==getState(state,pos)) return state; // There is an open space
    }
    return STATE_TIE; // No open positions left
}

short int addState(short int state, char pos, char xo) {
    assert(0==getState(state,pos));
    return state + pow(3,pos)*xo;
}

char getState(short int state, char pos) {
    assert(pos>=0);
    assert(pos<9);
    return (state/(int)pow(3,pos))%3;
}

void fprintState(short int state) {
    fprintf(stderr," 0: %c | 1: %c | 2: %c\n", p2c(state,0), p2c(state,1),p2c(state,2));
    fprintf(stderr," -----+------+------\n");
    fprintf(stderr," 3: %c | 4: %c | 5: %c\n", p2c(state,3), p2c(state,4),p2c(state,5));
    fprintf(stderr," -----+------+------\n");
    fprintf(stderr," 6: %c | 7: %c | 8: %c\n", p2c(state,6), p2c(state,7),p2c(state,8));
}


char p2c(short int state,char pos) {
    int val=getState(state,pos);
    if (val==0) return '_';
    if (val==1) return 'X';
    return 'O';
}

void CalcWDP(int index,int me, int n1, int n2){
    //printf("\nCalculating WDP\n");
    if(n1==n2){
        
        if(n1==0){
           // printf("\n25,25\n");
            updateWinDef(index, 25, 25);
            
            //25% win and defeat
            
        }
        
        else if(me == n1){
           // printf("\n100,100");
            updateWinDef(index, 100, 100);
            
        }
        
        else{
           // printf("\n0,100");
            updateWinDef(index, 0, 100);
            //0 win 100 defeat
            
        }
    }
    
    else{
        
        if(n1>n2){
            
            int temp = n1;
            n1 = n2;
            n2 = temp;
            
        }
        
        if(n1==0){
            
            if(me==n2){
              //  printf("\n50,0");
                updateWinDef(index, 50, 0);
            }
            
            else{
               // printf("\n0,50");
                updateWinDef(index, 0, 50);
            }
            
        }
        
    }
    
}

void updateWinDef(int index, int win, int defeat){
    
    if(winArray[index]<win && winArray[index]!=-1){
        
        winArray[index] = win;
        
    }
    
    if(defArray[index]<defeat && defArray[index]!=-1){
        
        defArray[index] = defeat;
        
    }
}

void horizontalCheck(int index,int me, int i, int j){
   // printf("/n performing Horizontal for position %d",index);
    int n[2];
    int z;
    int l = 0;
    
    for(z=0; z<3; z++){
       // printf("\nRow, Col :%d,%d\n",i,z);
        if(z!=j){
            n[l] = game[i][z];
            //printf("\nme : %d Vals : %d",me,n[l]);
            l++;
            
        }
        
    }
    CalcWDP(index, me, n[0], n[1]);
}

void verticalCheck(int index,int me, int i, int j){
    
    int n[2];
    int z;
    int l = 0;
    
    for(z=0; z<3; z++){
        if(z!=i){
            n[l] = game[z][j];
            l++;
            
        }
        
    }
    CalcWDP(index, me, n[0], n[1]);
}

void dLeftCheck(int index, int me, int i, int j){
    
    if(i==j){
        
        int n1,n2;
        
        if(i ==0){
            n1= game[1][1];
            n2= game[2][2];
            CalcWDP(index, me, n1, n2 );
            
            
        }
        
        else if (i==1){
            
            n1= game[0][0];
            n2= game[2][2];
            CalcWDP(index, me, n1, n2 );
            
        }
        
        else{
            
            n1= game[1][1];
            n2= game[0][0];
            CalcWDP(index, me, n1, n2 );
            
            
        }
        
    }
    
}
void dRightCheck(int index, int me, int i, int j){
    
    if(i+j==2){
        
        int n1,n2;
        if(i==j){
            n1= game[0][2];
            n2= game[2][0];
            CalcWDP(index, me, n1, n2);
            
        }
        
        else if(i==0){
            
            n1=game[1][1];
            n2 = game[2][0];
            CalcWDP(index, me, n1, n2);
            
        }
        
        else{
            
            n1 = game[1][1];
            n2 = game[0][2];
            CalcWDP(index, me, n1, n2);
            
        }
        
    }
    
    
    
}
