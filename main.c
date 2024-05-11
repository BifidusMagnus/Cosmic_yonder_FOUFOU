#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#define ENTER 10

typedef struct{
    int posx;
    int posy;
    char * name;
    int pv;
    int exp;
    char ** inventory;
}Player;

typedef struct{
    int length;
    int width;
    int nbevent;
    int nbdoor;
    char **room;
}Room;



int isInt(char * ch){
    int i = 0;
    while(ch[i]!='\0'){
        if(ch[i]<= 47 || ch[i] >=58){
            return 0;
        }
        i++;
    }
    return 1;
}














int giveSeed(WINDOW * win, int winwidth, int winlength){

    char cseed[100];
    int seed = -1;

    echo();
    //nodelay(stdscr, FALSE);

    mvwprintw(win, (winlength/2), (winwidth/2)-20, "<┘ TO CONFIRM |");        
    mvwprintw(win, (winlength/2), (winwidth/2)-5, " GIVE THE SEED : ");
    wrefresh(win);
    wgetnstr(win, cseed, 99);
    wclear(win);


    while(isInt(cseed)!=1 || atoi(cseed) > 1000000 || atoi(cseed) <= 0){
        mvwprintw(win, (winlength/2), (winwidth/2)-20, "<┘ TO CONFIRM |");
        mvwprintw(win, (winlength/2), (winwidth/2)-5, " GIVE A CORRECT SEED, BETWEEN 1 AND 1000000 : ");
        wrefresh(win);
        wgetnstr(win, cseed, 99);
        wclear(win);
    }

    noecho();
    //nodelay(stdscr, TRUE);

    seed = atoi(cseed);

    return seed;
}

















char* createName(WINDOW * win, int winwidth, int winlength){
    char ch[100];

    int c = 0;

    //wclear(win);

    echo();
    //nodelay(stdscr, FALSE);

    mvwprintw(win, (winlength/2), (winwidth/2)-20, "<┘ TO CONFIRM |");
    mvwprintw(win, (winlength/2), (winwidth/2)-5, " GIVE YOUR NAME : ");
    wrefresh(win);
    wgetnstr(win, ch, 99);

    noecho();    

    do{ 

        wclear(win);
        mvwprintw(win, (winlength/2)-1, (winwidth/2)-20, "[r] TO RESET |");
        mvwprintw(win, (winlength/2), (winwidth/2)-20, "<┘ TO CONFIRM |");
        mvwprintw(win, (winlength/2), (winwidth/2)-5, " YOU CONFIRM THE PSEUDO : %s ?", ch);

        wrefresh(win);

        c = getch();

        if(c == 'r'){
            echo();
            wclear(win);
            mvwprintw(win, (winlength/2), (winwidth/2)-20, "<┘ TO CONFIRM |");
            mvwprintw(win, (winlength/2), (winwidth/2)-5, " GIVE YOUR NAME : ");
            wrefresh(win);
            wgetnstr(win, ch, 99);
            noecho();
        }

    }while(c != 10);

    int namesize = strlen(ch);

    char * name = NULL;

    name = malloc((namesize+1)*sizeof(char));

    for(int i = 0; i<namesize+1; i++){
        name[i] = ch[i];
    }

    wclear(win);
    //nodelay(stdscr, TRUE);

    return name;

}














void startagame(WINDOW * win, int winposx, int winposy, int winlength, int winwidth){
    

    wclear(win);
    

    int ch = 0;

    int seed = giveSeed(win, winwidth, winlength);

    Player j;

    j.name = createName(win, winwidth, winlength);




    mvwprintw(stdscr, winposy-1, winposx+(winwidth/2)-13, "匚ㄖ丂爪丨匚  ㄚㄖ几ᗪ乇尺\n");
    mvwprintw(stdscr, winposy-1, winposx+1, "ACTUAL SEED : %d", seed);
    
    int t = (time(NULL));

    int te = time(NULL);


    while(ch != 10){
        
        box(win, 0,0);

        wrefresh(win);


        te = time(NULL);
        mvwprintw(stdscr, winlength+winposy+1, winposx+1, "TIME : %d", te-t);
        ch = getch();

        wclear(win);


        

    }

    wclear(stdscr);



}














void loadSave(WINDOW * win){
    wclear(win);
}






















void setting(WINDOW * win){
    wclear(win);
}

















void printMenu(WINDOW *win,int x, int y, int beg, int space){

    mvwprintw(win, y, x+2, "匚ㄖ丂爪丨匚\n");

    mvwprintw(win, y+1, x+2, "ㄚㄖ几ᗪ乇尺\n");

    mvwprintw(win, y+beg, x,"PLAY\n");

    mvwprintw(win, y+(beg+(space)), x,"SAVES\n");

    mvwprintw(win, y+(beg+(space*2)),x,"SETTINGS\n");

    mvwprintw(win, y+(beg+(space*3)), x,"QUIT\n");
}





















void startAnim(WINDOW * win, int winlength, int winwidth, int posx, int posy, int x, int y, int beg, int space){

    for(int i = 0; i<winlength; i++){
    
    mvwprintw(win, posy, posx, "-->");
        
    printMenu(win, x, y, beg, space);

    box(win, 0,0);

    for(int j = 1; j<winlength-i-1; j++){
        for(int l = 1; l<winwidth-1;l++){
            mvwprintw(win, j, l,"-");
        }
    }

    wrefresh(win);
    usleep(30000);
    wclear(win);
    }
    
}

void quitAnim(WINDOW * win, int winlength, int winwidth, int posx, int posy, int x, int y, int beg, int space){

    for(int i = 0; i<winlength; i++){
    
    mvwprintw(win, posy, posx, "-->");
        
    printMenu(win, x, y, beg, space);

    box(win, 0,0);

    for(int j = 1; j<i; j++){
        for(int l = 1; l<winwidth-1;l++){
            mvwprintw(win, j, l,"-");
        }
    }

    wrefresh(win);
    usleep(30000);
    wclear(win);
    }
}


void showMenu(WINDOW *win, int winlength, int winwidth, int winposx, int winposy){

    

    int chr = 0;

    

    int x = (winwidth/2)-10;
    int y = 2;
    
    
    int space = 4;
    int beg = y+3;


    int posx, posy;
    posx = (winwidth/3)-5;
    posy = beg+y;
    
    startAnim(win, winlength, winwidth, posx, posy, x, y, beg, space);

    wclear(win);

    while(posy != y+(beg+(3*space)) || chr != ENTER ){

        mvwprintw(win, posy, posx, "-->");
        
        printMenu(win, x, y, beg, space);

        
        box(win, 0,0);
        
        wrefresh(win);
        chr = getch();
        wclear(win);

        if (chr == ENTER && posy == y+beg){
            quitAnim(win, winlength, winwidth, posx, posy, x, y, beg, space);
            startagame(win, winposx, winposy, winlength, winwidth);
        }
        if (chr == ENTER && posy == y+(beg+(space))){
            quitAnim(win, winlength, winwidth, posx, posy, x, y, beg, space);
            loadSave(win);
        }
        if (chr == ENTER && posy == y+(beg+(space*2))){
            quitAnim(win, winlength, winwidth, posx, posy, x, y, beg, space);
            setting(win);
        }


        if(chr == KEY_UP && posy > y+beg){
            posy-= space;
        }
        if (chr == KEY_DOWN && posy < y+(beg+(space*3))){
            posy+= space;
        }


    }

    quitAnim(win, winlength, winwidth, posx, posy, x, y, beg, space);

}


//test

int main(){

    int ch = 0; 
    setlocale(LC_CTYPE,"");
    
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();


    int winposx = 5;
    int winposy = 2;
    int winlength = 30;
    int winwidth = 100;



    WINDOW * win = NULL;

    win = subwin(stdscr,winlength, winwidth, winposy, winposx);

    if (win == NULL){
        printf("allocation problem, try to modify the size of your terminal");
        exit(1);
    }


    showMenu(win, winlength, winwidth, winposx, winposy);


    
    endwin();

    return 0;
}