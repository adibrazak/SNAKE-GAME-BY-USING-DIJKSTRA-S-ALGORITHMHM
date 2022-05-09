#include<stdio.h>
#include<Windows.h>
#include<math.h>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<iostream>
#include<conio.h>
#include<exception>

using namespace std;

//=========================== Declaration for user ===========================//
const int width = 79; // window width
const int height = 24; // window height
int h_x, h_y, frogX, frogY, score_u; // snake and frog x and y coordinates
int tailX[100],tailY[100]; // TailX and TailY coordinates.
int nTail; // Length of the tail holder.
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN}; // Direction for snake.
eDirection dir; // variable of eDirection.

//=========================== Declaration for computer ===========================//
const static int TILE_LEFT = 0;
const static int TILE_RIGHT = 1;
const static int TILE_TOP = 2;
const static int TILE_BOTTOM =3;

struct TILE
{
	bool active;
	bool available;
	char symbol;
	POINT point;
	int cost;
	struct TILE *parent;
	struct TILE *sideTile[4];
	HANDLE hConsole;
};

//=========================== Declaration for all ===========================//
int score=0; // Score value holder Initialized to 0
bool gameOver; // Boolean for checking if game over.
HANDLE hConsole;  //text colour


//=========================== open interface ==================================//

void gotoxy(int x, int y) {  //function to move the cursor on the console 
     COORD coord;
     coord.X = x;
     coord.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Cover ()
{
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	SetConsoleTextAttribute(hConsole, 11);  // light blue colour
	
	char title[100][100] = {
		"  @@@@@@ @@    @@@  @@@@@@@@@   @@   @@@ @@@@@@@ ",
		" @@@     @@   @@@@  @@@   @@@   @@@  @@  @@       ",   // array to print the title of the game
		"  @@@@@  @@  @  @@  @@@@@@@@@   @@@@@@@  @@@@@@    ",
		"     @@@ @@@@   @@  @@@   @@@   @@@ @@@  @@        ",
		" @@@@@@  @@@    @@  @@@   @@@   @@   @@@ @@@@@@@   ",
	};

	int length = strlen(title[0]);
	bool stillNotComplete = true;
	int k = 0;    // initialized k to 0
	while (stillNotComplete)
	{
		system("cls");
		stillNotComplete = true;
		for (int i = 0; i < 5; i++) cout << endl;
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++)cout << " ";
			for (int j = 0; j < k; j++){
				cout << title[i][j];
			}
			cout << endl;
			if (i == 4)cout << endl << endl;
		}
		
		k++;
		if (k == length)
		stillNotComplete = false;
	}
	
gotoxy(0,15);
    SetConsoleTextAttribute(hConsole, 268);
	cout <<"                   By using Djigstra's algorithm          \n\n\n"<<endl;
	      	SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<""<<"  "<<'\xC9';
            for (int i=0; i<60; i++) {
                cout<<'\xCD';
            }cout<<'\xBB'<<endl;
            
            // print the names and metric numbers of the group
    SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8		
	cout<<"  "<<'\xCD' ;
	SetConsoleTextAttribute(hConsole, 6);                          //Yellow Color Code=6
	cout <<"\tDone by:  Firdaus Mazlan                  196298";
	SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
	cout<<"       "<<'\xCD'<< endl; 
	cout<<"  "<<'\xCD' ;
	SetConsoleTextAttribute(hConsole, 6);                          //Yellow Color Code=6   
	cout <<"\t          Amjad Alnasrallah               195806";
	SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
	cout<<"       "<<'\xCD'<< endl; 
	cout<<"  "<<'\xCD' ; 
	SetConsoleTextAttribute(hConsole, 6);                          //Yellow Color Code=6
	cout <<"\t          Adib Abd. Razak                 193508" ;
	SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
	cout<<"       "<<'\xCD' << endl; 
	cout<<"  "<<'\xCD' ; 
	SetConsoleTextAttribute(hConsole, 6);                          //Yellow Color Code=6
	cout <<"\t          Najiha Ramlan                   197705";
	SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
	cout<<"       "<<'\xCD' << endl; 
	cout<<"  "<<'\xCD' ; 
	SetConsoleTextAttribute(hConsole, 6);                          //Yellow Color Code=6  
	cout <<"\t          Nurul Haziqah                   196691";
	SetConsoleTextAttribute(hConsole, 8);							 //Dark Gray Color Code=8
	cout<<"       "<<'\xCD' << endl; 
	cout<<"  "<<'\xCD'<<"\t\t\t\t\t\t\t       \xBA" ; 
	SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<"\n"<<"  "<<'\xC8';
            for (int i=0; i<60; i++) {
                cout<<'\xCD';
            }cout<<'\xBC';

	cout<<endl<<endl;
   
	
    cout<<endl<<endl;        
	cout<<"\t               ";
	SetConsoleTextAttribute(hConsole, 480);                           //Yellow Color Code=6
	cout<<"Please ";
	SetConsoleTextAttribute(hConsole, 47);     //Green & White Color Code=47
	cout<<"'ENTER'";
	SetConsoleTextAttribute(hConsole, 480);                           //Yellow Color Code=6
	cout<<" to continue" <<endl;
	getchar();
	system("color 07");

}	
	
int Menu()
{
	char choice;
	SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<""<<"  "<<'\xC9';
            for (int i=0; i<40; i++) {
                cout<<'\xCD';
            }cout<<'\xBB'<<endl;
            
	// user choses if he/she wants to play or simulate the game
    cout<<"  "<<'\xBA' ;
    cout << "                Snake                 ";
	cout<<"  "<<'\xBA'<< endl; 
	cout<<"  "<<'\xBA' ;  
    cout << "  Who is Playing:                     ";
    cout<<"  "<<'\xBA'<< endl; 
	cout<<"  "<<'\xBA' ;  
    cout << " 1- User                              ";
    cout<<"  "<<'\xBA'<< endl; 
	cout<<"  "<<'\xBA' ;  
    cout << " 2- computer                          ";  
    cout<<"  "<<'\xBA'<< endl; 
	cout<<"  "<<'\xBA' ;  
    cout<<"\t\t\t\t\t   \xBA "<< endl; 
	cout<<"  "<<'\xBA'<<"\t\t\t\t\t   \xBA" ; 
	SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<"\n"<<"  "<<'\xC8';
            for (int i=0; i<40; i++) {
                cout<<'\xCD';
            }cout<<'\xBC';

	cout<<endl<<endl;
	cout << "PS. Press q at any time to quit the game" << endl;
	cout << endl << "Enter your choice: ";
	cin >> choice;
	
	return choice;
}

//======================= User's function ==========================//

//----------------- Setup game -----------------//
void Setup()
{
	gameOver = false;
	
	dir = STOP;   // Initial stat of snake is STOP. 
	
	// Set snake to center of window.         
	h_x = width / 2;
	h_y = height / 2;
	// Set position of frog within the bounds of the window.
	frogX = rand() % width;
	frogY = rand() % height;
	
	// Initialize length of tail to 0.
    nTail = 0;
		
}

//---------- Draw and symbols of border,frog,snake ---------//
void draw()
{
	system("cls"); // Clear console window.
	
	// Print upper boundary of the game.
	for(int i=0; i<width+2; i++)
		cout << "#";
	cout<<endl; // Move to next row after upper boundary row.
	
	// Print the map of the game.
	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++){
			
			if(j==0)
				cout<< "#";    // # is the border
			if(i==h_y && j==h_x)
				cout<< "O"; // O is the snake.
			else if(i == frogY && j == frogX)
				cout<< "f";  // f is the frog.
			else
			{
				bool print = false;
				for(int k = 0; k<nTail; k++)		// increment of snake tail
				{
					
					if(tailX[k] == j&& tailY[k] == i)
					{
						cout << "o"; // o is the tail
						print = true;
					}
				}
			    	if(!print)
			       	cout <<" ";
			}
				
			if(j==width-1)
				cout<< "#";
		}
		
		cout<<endl; // Move to next row.
	}
	
	// Print the bottom boundary of the game.
	for( int i=0; i<width+2; i++)
		cout << "#";
	cout<<endl;
	cout<< "Score:" << score <<endl;
}

//----------------- User's input -----------------//
void Input()
{
	if(_kbhit()) // If keyboard is pressed _kbhit() returns true.	
	{
		switch(_getch()) // Get the character pressed.
		{
			case 'a':
				if (dir == RIGHT && nTail!= 0) // if current direction is opposite then just return.
                return;
				dir=LEFT; // Set dir to LEFT.
				break;
			case 'd':
				if (dir == LEFT && nTail!= 0) // if current direction is opposite then just return.
                return;
				dir=RIGHT; // Set dir to RIGHT.
				break;
			case 'w':
				if (dir == DOWN && nTail!= 0) // if current direction is opposite then just return.
                return;
				dir=UP; // Set dir to UP.
				break;
			case 's':
				if (dir == UP && nTail!= 0) // if current direction is opposite then just return.
                return;
				dir=DOWN; // Set dir to DOWN.
				break;
			case 'q': // q for quit game.
				gameOver = true;
				break;
				
		}
	}
}

//------ Movement of User's snake ------//
void Logic()
{
	int prevX = tailX[0]; // Previous tail X coordinate.
	int prevY = tailY[0]; // Previous tail Y coordinate.
	int prev2X, prev2Y;
	tailX[0] = h_x;
	tailY[0] = h_y;
	for(int i=1; i<nTail; i++)
	{
    	prev2X = tailX[i];
	    prev2Y = tailY[i];
	    tailX[i] = prevX;
	    tailY[i] = prevY;
	    prevX = prev2X;
	    prevY = prev2Y;
	}
	// Logic for moving the snake based on the input.
	switch(dir)
	{
	case LEFT:
		h_x--; // Decrease x coordinate of snake;
		break;
	case RIGHT:
		h_x++; // Increase x coordinate of snake;
		break;
	case UP:
		h_y--; // Decrease y coordinate of snake;
		break;
	case DOWN:
		h_y++; // Increase y coordinate of snake;
		break;
	default:
		break;
	}
		
		// If snakes moves out of map bounds then game over.
		if(h_x>width || h_x<0 || h_y>height || h_y<0)
		gameOver = true;
	
	// Make the snake appear from other side
	// if(x>= width) x= 0; else if(x<0) x =width - 1;
	// if(h_y>= height) h_y= 0; else if(h_y<0) h_y =height - 1;
	
	for (int i = 0; i< nTail; i++)
	if(tailX[i] == h_x && tailY[i] == h_y)
		gameOver = true;
	
	if(h_x==frogX && h_y==frogY)
	{
		
		score += 10; //increase score if snake eats frog
		
		// Set new random position of the fruit.
		frogX = rand() % width; 
		frogY = rand() % height;
		nTail++; //increase tail length
	}
}

//======================= Computer's function ==========================//

//------ Sorted coordinate into vector ------//
void insertSortedIntoVector(TILE *t,vector<TILE*>&openList){
	bool val = false;
	for(int i=0;i<openList.size();i++){
		if(openList[i]->cost > t->cost){
			val = true;
			openList.insert(openList.begin()+i,t);
			break;
		}
	}
	if(!val){
		openList.push_back(t);
	}
}

//------ Setup game ------//
void setupBorders(TILE Borders[100][100], vector<POINT> *snakes, POINT frog)
{
	//prints out the empty spaces in the map
	for(int i=0;i<24;i++){
		for(int j=0;j<79;j++){
			Borders[i][j].point.x = j;
			Borders[i][j].point.y = i;
			Borders[i][j].symbol = ' ';
			Borders[i][j].available = true;
			Borders[i][j].parent = NULL;
			Borders[i][j].cost = 999;
			if(i!=0)
				Borders[i][j].sideTile[TILE_TOP] = &Borders[i-1][j];
			else
				Borders[i][j].sideTile[TILE_TOP] = NULL;
			if(i!=23)
				Borders[i][j].sideTile[TILE_BOTTOM] = &Borders[i+1][j];
			else
				Borders[i][j].sideTile[TILE_BOTTOM] = NULL;
			if(j!=0)
				Borders[i][j].sideTile[TILE_LEFT] = &Borders[i][j-1];
			else
				Borders[i][j].sideTile[TILE_LEFT] = NULL;
			if(j!=78)
				Borders[i][j].sideTile[TILE_RIGHT] = &Borders[i][j+1];
			else
				Borders[i][j].sideTile[TILE_RIGHT] = NULL;
		}
	} 
	// prints out the borders of the map
	for(int i=0;i<24;i++)for(int j=0;j<79;j++)if(i==0||i==23||j==0||j==78)Borders[i][j].symbol='#';
	for(int i=0;i<snakes->size();i++)
	{
		// prints out the snake 
		Borders[snakes->at(i).y][snakes->at(i).x].symbol='O';
	} 
	// prints out the frog
	Borders[frog.y][frog.x].symbol = 'f';
}

//------ Generate path for computer's snake ------//
vector<TILE*> generatePath(POINT start, POINT end, TILE outer_border[100][100], bool &found)
{
	vector<TILE*>openList;
	openList.push_back(&outer_border[start.y][start.x]);
	openList[0]->cost = 0;
	
	// Dijkstra’s algorithem finds the shortest path
	while(openList.size()!=0 && found == false){
		for(int i=0;i<4;i++){
			if(openList[0]->sideTile[i]!=NULL)
			{
					
				if ((openList[0]->sideTile[i]->symbol == ' '
					|| (openList[0]->sideTile[i]->point.x==start.x && openList[0]->sideTile[i]->point.y==start.y) 
					|| (openList[0]->sideTile[i]->point.x==end.x && openList[0]->sideTile[i]->point.y==end.y))
					&& openList[0]->sideTile[i]->available)
				{
					
					if(openList[0]->sideTile[i]->cost > openList[0]->cost+1)
					{
						openList[0]->sideTile[i]->cost = openList[0]->cost+1;
						openList[0]->sideTile[i]->parent = openList[0];
						insertSortedIntoVector(openList[0]->sideTile[i], openList);
					}
				}
			}
		}
		if(openList[0]->point.x == end.x && openList[0]->point.y == end.y)
		{
			found = true;
			break;
		}
		openList[0]->available = false;
		openList.erase(openList.begin());
	}
	
	vector<TILE*> backRoad;			
	
	if (found)
	{
		TILE *curr = &outer_border[end.y][end.x];
		while (curr != &outer_border[start.y][start.x])
		{
			backRoad.insert(backRoad.begin(), curr);
			curr = curr->parent;
		}
	}
	return backRoad;
}

//======================= MAIN FUNCTION ==========================//
int main()
{
	int choice;
	char Continue;
	bool x=true;
	Cover ();
	system("cls");
	
	choice = Menu ();
	
	while(!gameOver)
	{	
	
	switch (choice){
		case '1': //user play the game
			Setup();
			while(!gameOver)
			{
				system("color 06"); 			// background set to black and foreground set to yellow
				draw();
				Input();
				Logic();
				system ("cls");
			}
			break;
		case '2': //computer play as simulation
			{	
				system("color 06"); // background set to black and foreground set to yellow
				getchar();
				POINT p;p.x = 5;p.y = 20; //initial point of snake
				score=0;
				vector<POINT>snake;
				snake.push_back(p);
				POINT frog; frog.x = 50; frog.y = 10; //initial point of frog
				int deadLockTrial = 0;
					while(x){
						TILE Borders[100][100];
						setupBorders(Borders,&snake,frog);
						bool found = false;
						vector<TILE*> path = generatePath(snake[0],frog,Borders, found);
						if (found)deadLockTrial = 0;
						for (int i = 0; i < path.size(); i++)
						{
							Borders[path[i]->point.y][path[i]->point.x].symbol = '#';
						}
						if (snake[0].x == frog.x && snake[0].y == frog.y){ 					//if snake eat the frog
							do{
								frog.x = 1 + rand() % 77; frog.y = 1 + rand() % 22; 			//generate new random coordinate of frog
								score += 10; 							//score for eat the frog
							} while (Borders[frog.y][frog.x].symbol != ' ');
				
							POINT nwTail; 
							nwTail.x = snake[snake.size() - 1].x;
							nwTail.y = snake[snake.size() - 1].y;
								snake.push_back(nwTail);
							for (int i = snake.size() - 2; i > 0; i--)
							{
								snake[i].x = snake[i - 1].x;
								snake[i].y = snake[i - 1].y;
							}
							if (path.size()>0)
							{
								snake[0].x = path[0]->point.x;
								snake[0].y = path[0]->point.y;
							}
						}
						else{
							for (int i = snake.size() - 1; i > 0; i--)
							{
								snake[i].x = snake[i - 1].x;
								snake[i].y = snake[i - 1].y;
							}
							if (path.size()>0)
							{
								snake[0].x = path[0]->point.x;
								snake[0].y = path[0]->point.y;
							}
							else{
								vector<POINT>temp;
								for (int i = snake.size()-1; i >= 0; i--){
									temp.push_back(snake[i]);
								}
								snake = temp;
								deadLockTrial++; 
				
								do{
									setupBorders(Borders, &snake, frog);
									generatePath(snake[0], frog, Borders, found);
									if (!found)deadLockTrial++;
									if (deadLockTrial >= 2){
										do{
											frog.x = 1 + rand() % 77; frog.y = 1 + rand() % 22;
										} while (Borders[frog.y][frog.x].symbol != ' ');
									}
					
								} while (!found);
							}
						}
						setupBorders(Borders, &snake, frog);

						char p[100][100];
						for (int i = 0; i < 24; i++)for (int j = 0; j < 79; j++)p[i][j] = Borders[i][j].symbol;
	
						for(int i=0;i<24;i++){
						cout << endl << p[i];
						
						if(_kbhit()) // If keyboard is pressed _kbhit() returns true.	
						{
						switch(getch()) // Get the character pressed.
						{
							case 'q': // if q is pressed gameOver set to True
								x=false;
								break;
							
						}
						}
						}
						
						cout<<"\nSCORE = "<<score<<endl;
						system ("cls");
						
						
					}
				
					
			}
			break;
		}
			
            cout<<"\n  "<<'\xC9';
            for (int i=0; i<70; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBB'<<"\n"<<"  "<<'\xBA';
            for (int i=0; i<70; i++) {
                cout<<" ";
            }
            cout<<'\xBA';
            for (int j=0; j<17; j++) {
                cout<<"\n"<<"  "<<'\xBA';
                for (int i=0; i<70; i++) {
                    cout<<" ";
                }
                cout<<'\xBA';
            }
            cout<<"\n"<<"  "<<'\xC8';
            for (int i=0; i<70; i++) {
                cout<<'\xCD';
            }cout<<'\xBC';
        gotoxy(5,10);
		cout << "\t\t\t\tGame Over." << endl << "\t\tPress any key to play again or n to Quit: " ;
		cin >> Continue;
		if (Continue=='n')
		{
			gameOver=true;
			gotoxy(0,20);
		}
		else
		{
			gameOver=false;
			system("cls");
			choice = Menu ();				
		}
	}
		
	return 0;
}
