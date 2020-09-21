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
void game();

int main()
{
    //Set up ncurses
    initscr();
    noecho();
    curs_set(FALSE);

    //Tread game and key input
    game();
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
void game(){

    while(1){

        getmaxyx(stdscr, max_y, max_x);
        clear();
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

