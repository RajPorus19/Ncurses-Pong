#include<stdio.h>
#include<ncurses.h>
#include<unistd.h>
#include <pthread.h>

//Ball's properties
int x = 0, y = 0;
int next_x = 0;
int next_y = 0;
int direction_y = 1;
int direction_x = 1;
int delay = 40000;

//Screen's properties
int max_x = 0, max_y = 0;

//Functions
void ballFaster();
void ballColideLR();
void ballColideTB();
void ballForward();
void *game();
void *printSpeed();
void *getKeyInput();

int main()
{
    //Set up ncurses
    initscr();
    noecho();
    curs_set(FALSE);

    //Tread game and key input
    pthread_t thread_id;
    pthread_t thread_id2;
    pthread_create(&thread_id, NULL, game, NULL);
    pthread_create(&thread_id2, NULL, *getKeyInput, NULL);
    pthread_join(thread_id, NULL);
    pthread_join(thread_id2, NULL);

    endwin();
}

void ballFaster(){
    if(delay >= 15000){
        delay -= 1000;
    }

}
void ballColideLR(){
        direction_x *= -1;
        ballFaster();
}
void ballColideTB(){
        direction_y *= -1;
}
void ballForward(){
        x+= direction_x; 
        y+= direction_y; 
}
void *game(){

    while(1){

        getmaxyx(stdscr, max_y, max_x);
        clear();
        printSpeed();
        getKeyInput();
        mvprintw(y,x,"o"); 
        refresh();

        usleep(delay);
        next_x = x + direction_x;
        next_y = y + direction_y;

        if(next_x >= max_x || next_x < 0) 
        {
            ballColideLR();
        }
        else if(next_y >= max_y || next_y < 0) 
        {
            ballColideTB();
        }
        else{
            ballForward();
        }
    }
}

void *printSpeed(){
    char sdelay[10];
    sprintf(sdelay, "%d", delay);
        mvprintw(0,0,sdelay); 

}
void *getKeyInput(){
    while(1){
    char key;
    key = getchar();
    if(&key=="j"){
        delay += 1000;
    }
    else if(&key=="k"){
        delay -= 1000;
    }
    }
}
