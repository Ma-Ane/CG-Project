# include <graphics.h>
# include <iostream>
# include <conio.h>
# include <conio.h>
# include <random>
# include <string.h>
using namespace std ;

int counter = 0 ;
int random[10] = {3, 4, 1, 5, 2, 1, 2, 3, 2, 4} ;
int i = 0 ;
// board
int width_board = 150, height_board = 10;        // dim of rectangle
int x_board = 1100/2 - width_board/2, y_board = 650;           // start position at center
int dx_board = 5, dy_board = 5;

// ball
int radius_ball = 8 ;
int x_ball = (x_board+width_board/2), y_ball = (y_board-radius_ball-3) ;

// for moving the ball 
int x_shift, y_shift ;

int a = 0 ;
char ch= 'q';           

void home_screen(int maxx, int maxy){
    settextstyle(10, 0, 5) ;
    outtextxy(maxx/3-10, 150, (char*)"Welcome to the Game") ;
    settextstyle(8, 0, 4) ;
    outtextxy(20, 300, (char*)"Manjit K Maharjan   Ishan Ghimire   Jyoti Kumari Gupta") ;
    outtextxy(34, 400, (char*)" KAT078BCT045         KAT078BCT037      KAT078BCT038") ;

    settextstyle(10, 0, 5) ;
    outtextxy(maxx/3-100, 500, (char*)"Press Enter to continue") ;

    getch() ;
}

void move_board(char prev_char, int maxx, int maxy) {
    switch (ch) {
        case 'a': // Move left
        case 'A':
            x_board -= dx_board;
            if (x_board < 0) ch = 'w' ;
            break;
        case 'd': // Move right
        case 'D':
            if (x_board+dx_board+width_board < maxx) 
                x_board += dx_board;
            break;
        case 27: // ESC key_board to exit
            a = 10 ;  
        case 'p':   // Pause
        case 'P':
            settextstyle(10, 0, 5) ;
            outtextxy(190, 210, (char*)"Game Paused") ;
            break;
        case 32:        //space for hold
            ch = 'm' ;          // any char
            break;
        default:
            ch = prev_char ;
            break;
    }
}

// int generate_random() {
//     // Initialize a random number generator
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_int_distribution<> distrib(1, 9);

//     // Generate random number in the range [min, max]
//     int randomValue = distrib(gen);
//     return randomValue ;
// }

void move_ball(int maxx, int maxy) {
    if (x_ball+x_shift+radius_ball >= maxx || x_ball+x_shift+radius_ball < 0)      // check for edges
        x_shift = -x_shift ;
    
    if (y_ball+y_shift+radius_ball < 0 || y_ball+y_shift+radius_ball > y_board)     // check for edges
        y_shift = -y_shift ;

    x_ball += x_shift ;             // shift the ball center
    y_ball += y_shift ; 
}

void strike_ball(int maxx, int maxy) {      // ball when on the board
    counter ++ ;
    //int rand_no = generate_random();
    int rand_no = random[i];
    if (i>10)
        i = 0 ;
    else
        i++ ;

    if (rand_no<5) {
        x_shift = -(rand_no * 2) ;         // angle
    }
    else if(rand_no>5){
        x_shift = (rand_no * 2) ;
    }
    else
        x_shift = 0 ;

    y_shift = -7 ;
    move_ball(maxx, maxy) ;
}

int main() {
    int gd = DETECT, gm;
    //initgraph(&gd, &gm, (char*)"");
    initwindow(1100, 700, "Game") ;
    char prev_char ;
    int maxx = getmaxx(), maxy = getmaxy() ;

    home_screen(maxx, maxy) ;

    cleardevice() ;
    settextstyle(10, 0, 5) ;
    outtextxy(maxx/3, maxy/2-30, (char*)"Ready to Play?") ;
    getch() ;

    while (a==0) {
        char count[] = {counter/10 + 48, counter%10+48,0} ;
        cleardevice();      // Clear screen
        settextstyle(10, 0, 8) ;
        setcolor(14) ;
        outtextxy(maxx/2, 20, count) ;

        setcolor(11) ;
        rectangle(x_board, y_board, x_board + width_board, y_board + height_board);     // Draw the rectangle
        setcolor(6) ;
        circle(x_ball, y_ball, radius_ball) ;           // draw the ball
        setcolor(15) ;

        prev_char = ch ;
        if (kbhit()) ch = getch();      // Check for user input

        move_board(prev_char, maxx, maxy) ;      // movement of the board

        // edi board ko ma lagxa ki lagdaina bhanera check
        if (y_ball+radius_ball == (y_board-3) && (x_ball+radius_ball>=x_board && x_ball+radius_ball<=(x_board+width_board)))
            strike_ball(maxx, maxy) ;       // when ball on the board
        else if (y_ball+radius_ball == (y_board-3) && (x_ball+radius_ball<x_board || x_ball+radius_ball>(x_board+width_board))){
            settextstyle(10, 0, 8) ;
            outtextxy(maxx/3-20, maxy/2-20, (char*)"Game Over") ;
            getch() ;
            a = 10 ;
        }
        else    
            move_ball(maxx, maxy) ;     // move the ball expect when on the board

        delay(7);      // Delay to control movement speed
    }

    cleardevice() ;
    settextstyle(10, 0, 6) ;
    outtextxy(maxx/3-90, maxy/2-20, (char*)"Thank you for playing") ;
    getch() ;

    return 0;
}