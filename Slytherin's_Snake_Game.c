// C program to build the complete snake game

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

//Global variables declaration
int i, j, difficulty_level, pause, life = 3, height = 30, width = 60;
unsigned long int loop_delay;
int gameover, score;
int snakex, store_x, snakey, store_y, fruitx, fruity, flag=0,flag_check;
int tailx[100],taily[100],piece=6,exe;
char str;

COORD coord = {0,0};

//Takes cursor to the specified coordinate
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

// Prints the starting page
void first()
{
    system("cls");
    printf("\n\nWelcome to the mini Snake game.(Press any key to continue)\n");
    getch();
    printf("\n\nChoose the difficulty level:");
    printf("\n\n1. EASY");
    printf("\n2. INTERMEDIATE");
    printf("\n3. HARD\n");
    do{
        printf("\nPress 1 or 2 or 3 and hit ENTER\n");
        scanf("%d", &difficulty_level);
        if(difficulty_level == 1)
            loop_delay = 60500000;
        else if(difficulty_level == 2)
            loop_delay = 40500000;
        else if(difficulty_level == 3)
            loop_delay = 20500000;
        else
            difficulty_level = 0; //not set
        }while(difficulty_level != 1 && difficulty_level != 2 && difficulty_level != 3);
    printf("\n\nINSTRUCTIONS");
    printf("\n\n-> Foods are generated at random places.");
    printf("\n-> Use the arrow keys on your keyboard to control the snake and grab the food.");
    printf("\n-> The length of the snake increases everytime the food is consumed.");
    printf("\n-> You have three lives.");
    printf("\n-> It decreases instantly when the snake's head touches the boundary or its own body.");
    printf("\n-> Game will be over once no more life is left.");
    printf("\n\nPress any key to continue.");
    getch();
}

//loadinggggg
void loading()
{
    int i,j;
    system("cls");
    gotoxy(25, 13);
    printf("Please wait");
    gotoxy(25, 15);
    printf("LOADING.....");
    gotoxy(25, 17);
    for(i=1;i<=20;i++){
    for(j=0;j<=100000000;j++);//to display the character slowly
    printf("%c",177);}
    gotoxy(25, 19);
    printf("Press enter key to continue");
    getch();
}


// Sets up location for snake and fruit initially
void setup()
{
    gameover = 0;
    snakex = width / 2;
    snakey = height / 2;
    for ( i = 0; i <=piece; i++)
    {
        tailx[i]=snakex-i;                //initializing the coordinate of the tails
        taily[i]=snakey;
    }
label1:
    fruitx = rand() % 60;
    if (fruitx == 0)
        goto label1;
label2:
    fruity = rand() % 30;
    if (fruity == 0)
        goto label2;
}

void setup2()
{  
    snakex = width / 2;
    snakey = height / 2;
    flag_check=0;
    flag=0;
    for ( i = 0; i <=piece; i++)
    {
        tailx[i]=snakex-i;                //initializing the coordinate of the tails
        taily[i]=snakey;
    }
}


// Draws the border
void Border()
{
    int i;
    system("cls");

    // prints the two horizontal borders i.e top and bottom
    for(i=0;i<=width;i++)
    {
        gotoxy(i, 0);
        printf("%c", 178);
        gotoxy(i, 30);
        printf("%c", 178);
    }
    // prints the two verical borders i.e left and right
    for(i=0;i<=height;i++)
    {
        gotoxy(0, i);
        printf("%c",178);
        gotoxy(60, i);
        printf("%c",178);
    }
}

// Prints the score below the game zone
void Print_score_and_life()
{
    gotoxy(0, 32);
    printf("SCORE = %d", score);
    printf("\n");
    printf("Press space bar to pause");
    printf("\n");
    printf("Press X to quit the game");
    gotoxy(42, 32);
    printf("LIVES REMAINING = %d", life);
}


// Empties the previous location of snake when its position changes
void Remove_last_position_of_snake()
{
    for (i=0;i<=piece;i++)
    {
        gotoxy(tailx[i],taily[i]);
        printf (" ");
    }
    if(gameover == 1) //to remove food when game is over
    {
        gotoxy(fruitx, fruity);
        printf(" ");
    }
    gotoxy(37,33);
    printf("                         ");    //to remove " Press arrow key to start"
}


// Function to take the input
void input()
{
    if(kbhit())
    {
        pause = 0;
        int k;
        k = getch();
        switch (k)
        {
            case 75:                //Used for LEFT arrow key
                flag = 1;
                break;
            case 80:                //Used for DOWN arrow key
                flag = 2;
                break;
            case 77:                //Used for RIGHT arrow key
                flag = 3;
                break;
            case 72:                //Used for UP arrow key
                flag = 4;
                break;
            case 'x':
                gameover = 1;
                str='n';
                break;
            case 'X':
                gameover = 1;
                str='n';
                break;
            case ' ':
                pause = 1;
                break;
        }
    }
}

// Function for the logic behind each movement
void logic()
{
    while(pause == 1)
    {
        input();
        gotoxy(37,33);
         printf("Press arrow key to resume");
    }
    int prevx,prevy,prev2x,prev2y;
    prevx=tailx[0];
    prevy=taily[0];
    tailx[0]=snakex;
    taily[0]=snakey;
    for ( i = 1; i <= piece; i++)
    {
        prev2x=tailx[i];
        prev2y=taily[i];
        tailx[i]=prevx;
        taily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;
    }

    store_x = snakex; //storing the current location of the head of the snake
    store_y = snakey;

    for(int i=0;i<loop_delay;i++); //to delay according to the difficulty level

    if (flag==1 && flag_check==3)
    {
        flag=3;
    }
    if (flag==2 && flag_check==4)
    {
        flag=4;
    }
    if (flag==3 && flag_check==1)
    {
        flag=1;
    }
    if (flag==4 && flag_check==2)
    {
        flag=2;
    }

    switch (flag)
    {
        case 1:
            snakex--;
            break;
        case 2:
            snakey++;
            break;
        case 3:
            snakex++;
            break;
        case 4:
            snakey--;
            break;
    }

    flag_check=flag;

    // If snake reaches the fruit, update the score
    if (snakex == fruitx && snakey == fruity) {
        gotoxy(fruitx, fruity); //remove food from previous location
        printf(" ");
    
    // After eating the above fruit generate new fruit
    label3:
        fruitx = rand() % 60;
        if (fruitx == 0)
            goto label3;

    label4:
        fruity = rand() % 30;
        if (fruity == 0)
            goto label4;

        score += 10;
        piece++;
    }
}

// Displays snake and food
void Print_snake_and_food()
{
    for (i=0;i<piece;i++){
    gotoxy(tailx[i],taily[i]);
    printf ("o");
    }
    gotoxy(snakex, snakey);
    printf("0");
    gotoxy(fruitx, fruity);
    printf("%c", 2);
    if(flag==0)                 //running this for the first loop as flag =0 in first loop
     {
         Print_score_and_life();
         gotoxy(37,33);
         printf("Press arrow key to start");
        while (1)
        {
            input();
            if (flag==2 || flag==3 || flag==4)  //so that life doesn't decrease if we press 
             break;                             //left arrow key each time the game starts
        }
     }
}

void check2(){
    // If the game is over i.e if snake touches the boundary
    if (snakex <= 0 || snakex >= width || snakey <= 0 || snakey >= height)
    {
        exe=0;
        life--;
        Beep(500,500);
        getch();
          for ( i = 0; i <=piece; i++)
        {
            gotoxy(tailx[i],taily[i]);
            printf(" ");
        }
        
        if(life!=0)
          setup2();
        if(life == 0)
            gameover = 1;
    }
}



void check(){
 if(exe==1)
 {
 for ( i = 1; i <=piece; i++)
    {
        if (snakex==tailx[i] && snakey==taily[i])
        {
            life--;
            Beep(500,500);
            getch();
            for ( i = 0; i <=piece; i++)
            {
              gotoxy(tailx[i],taily[i]);
              printf(" ");
            }
        
           if(life!=0)
           setup2();
        
           if(life == 0)
              gameover = 1;
        }
    }
}
if(gameover == 1)
{
    printf("\a");
    Print_score_and_life();     //prints final score and life
}
}

void record(){
   char plname[20],nplname[20],cha,c;
   int i,j;
   FILE *info;
   info=fopen("record.txt","a+");
   getch();
   system("cls");
   fflush(stdin);
   printf("Do you want your score to be recorded? (Press 'y' or 'n')");
   c = getch();
   if(c == 'y' || c == 'Y')
   {
       printf("\nEnter your name\n");
       scanf("%[^\n]",plname);

       for(j=0;plname[j]!='\0';j++){ //to convert the first letter after space to capital
       nplname[0]=toupper(plname[0]);
       if(plname[j-1]==' '){
       nplname[j]=toupper(plname[j]);
       nplname[j-1]=plname[j-1];}
       else nplname[j]=plname[j];
       }
       nplname[j]='\0';
       fprintf(info,"Player Name : %s\n",nplname);
        //for date and time

        time_t mytime;
        mytime = time(NULL);
        fprintf(info,"Played Date : %s",ctime(&mytime));
        fprintf(info,"Score : %d\n",score);//write the scores in the file
        if(difficulty_level == 1)
            fprintf(info,"Difficulty Level : Easy\n");
        if(difficulty_level == 2)
            fprintf(info,"Difficulty Level : Intermediate\n");
        if(difficulty_level == 3)
            fprintf(info,"Difficulty Level : Hard\n");
       for(i=0;i<=50;i++)
       fprintf(info,"%c",'_');
       fprintf(info,"\n");
       fclose(info);
    }
    printf("\nDo you want to see the past records? (Press 'y' or 'n')\n");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do{
           putchar(c=getc(info));
        }while(c!=EOF);
    }
         fclose(info);
}

// Driver Code
void main()
{
    //Intro
    srand(time(0)); //to generate foods at different locations in every instant of the game
    setup();
    first();
    loading();
    label5:
    Border();

    //Until the game is over
    while (!gameover)
    {exe=1;
        Remove_last_position_of_snake();
        gotoxy(0,0); 
        printf("%c", 178);
        Print_snake_and_food();
        Print_score_and_life();
        input();
        logic();
        check2();
        check();
    }
        Remove_last_position_of_snake();
        gotoxy(1,1);
        label7:
        gotoxy(1,1);
        printf("Do you want to play again?(y/n)");
str=getch();
if(str=='y' || str=='Y'){
    life=3;
    piece=6;
    score=0;
    gameover=0;
        flag_check=0;
    flag=0;
    setup();
     system("cls");
    printf("\n\nChoose the difficulty level:");
    printf("\n\n1. EASY");
    printf("\n2. INTERMEDIATE");
    printf("\n3. HARD\n");
    do{
        printf("\nPress 1 or 2 or 3 and hit ENTER\n");
        scanf("%d", &difficulty_level);
        if(difficulty_level == 1)
            loop_delay = 60500000;
        else if(difficulty_level == 2)
            loop_delay = 40500000;
        else if(difficulty_level == 3)
            loop_delay = 20500000;
        else
            difficulty_level = 0; //not set
        }while(difficulty_level != 1 && difficulty_level != 2 && difficulty_level != 3);
    goto label5;
}
    else if(str=='n' || str=='N'){
    goto label6;
}
else{
    gotoxy(1,2);
    printf("Either enter y or n.");
    goto label7;
}
        label6:
        gotoxy(1,3);
        printf("GAME OVER");
        gotoxy(1,4);
        printf("Press any key to continue.");
        getch();
    record();
}
//
