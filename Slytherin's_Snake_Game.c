// C program to build the complete snake game

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

//Global variables declaration
int i, j, life = 3, height = 30, width = 60;
int gameover, score;
int snakex, store_x, snakey, store_y, fruitx, fruity, flag,flag_check;
int tailx[100],taily[100],piece=2,tail2x[100],tail2y[100];

COORD coord = {0,0};

//Takes cursor to the specified coordinate
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//to print on the starting
void first()
{
    system("cls");
    printf("\n\nWelcome to the mini Snake game.(press any key to continue)\n");
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
    getch();
}


// Sets up location for snake and fruit initially
void setup()
{
    gameover = 0;

    // Stores height and width (width along x axis and height along y axis)
    snakex = width / 2;
    snakey = height / 2;
label1:
    fruitx = rand() % 60;
    if (fruitx == 0)
        goto label1;
label2:
    fruity = rand() % 30;
    if (fruity == 0)
        goto label2;
    score = 0;
}

// Draws the border
void Border()
{
    int i;
    system("cls");

    //this loop prints the two horizontal borders i.e top and bottom
    for(i=0;i<=width;i++)
    {
        gotoxy(i, 0);
        printf("%c", 178);
        gotoxy(i, 30);
        printf("%c", 178);
    }
    //this loop prints the two verical borders i.e left and right
    for(i=0;i<=height;i++)
    {
        gotoxy(0, i);
        printf("%c",178);
        gotoxy(60, i);
        printf("%c",178);
    }
}

// Displays snake and food
void Print_snake_and_food()
{ 
    gotoxy(snakex, snakey);
    printf("0");
    for (i=0;i<piece;i++){
gotoxy(tailx[i],taily[i]);
    printf ("o");
    }

    gotoxy(fruitx, fruity);
    printf("%c", 2);
}

// Empties the previous location of snake when its position changes
void Remove_last_position_of_snake()
{
    gotoxy(store_x, store_y);
    printf(" ");

    for (i=1;i<=piece;i++){
        gotoxy(tailx[i],taily[i]);
    printf (" ");
gotoxy(tail2x[i],tail2y[i]);
    printf (" ");
    }


}


// Prints the score below the game zone
void Print_score_and_life()
{
    gotoxy(0, 32);
    printf("SCORE = %d", score);
    printf("\n");
    printf("Press X to quit the game");
    gotoxy(42, 32);
    printf("LIVES REMAINING = %d", life);
}

// Function to take the input
void input()
{
    if(kbhit())
    {
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
                break;
            case 'X':
                gameover = 1;
                break;
        }
    }
}

// Function for the logic behind each movement
void logic()
{
    int i;int prevx,prevy,prev2x,prev2y;
    prevx=tailx[0];
    prevy=taily[0];
    tailx[0]=snakex;
    taily[0]=snakey;
    for ( i = 1; i <=piece; i++)
    {
        prev2x=tailx[i];
        prev2y=taily[i];
        tailx[i]=prevx;
        taily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;
        tail2x[i]=prev2x;
        tail2y[i]=prev2y;
            }
    
    store_x = snakex; //storing the current location of snake
    store_y = snakey;

    for(int i=0;i<40000000;i++); //to delay
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





    switch (flag) {
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
    default:
        break;

    }
    flag_check=flag;

    // If the game is over i.e if snake touches the boundary
    if (snakex <= 0 || snakex >= width || snakey <= 0 || snakey >= height)
    {
        life--;
        snakex = width / 2; //moving snake to the centre after life decreases
        snakey = height / 2;
        getch(); //waits for user to press a key before continuing to play
        if(life == 0)
        {
            gameover = 1;
            Print_score_and_life(); //prints final score and LIFE = 0
        }
    }

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

void record(){
   char plname[20],nplname[20],cha,c;
   int i,j,px;
   FILE *info;
   info=fopen("record.txt","a+");
   getch();
   system("cls");
   printf("Do you want your score to be recorded? (Press 'y' or 'n')");
   if(getch() == 'y' || getch() == 'Y')
   {
       printf("\nEnter your name\n");
       scanf("%[^\n]",plname);
       //************************
       for(j=0;plname[j]!='\0';j++){ //to convert the first letter after space to capital
       nplname[0]=toupper(plname[0]);
       if(plname[j-1]==' '){
       nplname[j]=toupper(plname[j]);
       nplname[j-1]=plname[j-1];}
       else nplname[j]=plname[j];
       }
       nplname[j]='\0';
       //*****************************
       //sdfprintf(info,"\t\t\tPlayers List\n");
       fprintf(info,"Player Name :%s\n",nplname);
        //for date and time

       time_t mytime;
      mytime = time(NULL);
      fprintf(info,"Played Date:%s",ctime(&mytime));//**************************
         fprintf(info,"Score:%d\n",px=score);//write the scores in the file
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
    int m, n;
    //Intro
    setup();
    first();
    loading();
    Border();

    //Until the game is over
    while (!gameover)
    {
        if(store_x != 0) //to not execute this function in the first loop
            Remove_last_position_of_snake();

        Print_snake_and_food();
        Print_score_and_life();
        input();
        logic();
    }
    if(getch())
    {
        gotoxy(1,1);
        printf("GAME OVER");
        gotoxy(1,2);
        printf("Press any key ko continue.");
        getch();
    }
    record();
}
