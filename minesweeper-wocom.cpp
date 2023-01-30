#include<bits/stdc++.h>
#include <iostream>
using namespace std;


#define MAXSIDE 25
#define MAXMINES 99

int SIDE ; 
int MINES ; 


bool isValid(int row, int col)
{
	return (row >= 0) && (row < SIDE) &&(col >= 0) && (col < SIDE);
}


bool isMine (int row, int col, char board[][MAXSIDE])
{
	if (board[row][col] == '*')
		return (true);
	else
		return (false);
}


void makeMove(int &x, int &y)
{

	cout <<"Enter your move, (row, column) -> ";
	cin >> x >> y;
	return;
}


void printBoard(char myBoard[][MAXSIDE])
{
	int i, j;

	cout << " ";

	for (i=0; i<SIDE; i++)
		cout << i;

	cout << "\n\n";

	for (i=0; i<SIDE; i++)
	{
		cout << i;

		for (j=0; j<SIDE; j++)
			cout << myBoard[i][j];
		cout << "\n";
	}
	return;
}

// baraye shomaresh bombaye atraf
int countAdjacentMines(int row, int col, int mines[][2],
					char realBoard[][MAXSIDE])
{

	int i;
	int count = 0;


	//----------- 1st Neighbour (North) ------------

		if (isValid (row-1, col) == true)
		{
			if (isMine (row-1, col, realBoard) == true)
			count++;
		}

	//----------- 2nd Neighbour (South) ------------

		if (isValid (row+1, col) == true)
		{
			if (isMine (row+1, col, realBoard) == true)
			count++;
		}

	//----------- 3rd Neighbour (East) ------------

		if (isValid (row, col+1) == true)
		{
			if (isMine (row, col+1, realBoard) == true)
			count++;
		}

	//----------- 4th Neighbour (West) ------------

		if (isValid (row, col-1) == true)
		{
			if (isMine (row, col-1, realBoard) == true)
			count++;
		}

	//----------- 5th Neighbour (North-East) ------------

		if (isValid (row-1, col+1) == true)
		{
			if (isMine (row-1, col+1, realBoard) == true)
			count++;
		}

	//----------- 6th Neighbour (North-West) ------------

		if (isValid (row-1, col-1) == true)
		{
			if (isMine (row-1, col-1, realBoard) == true)
			count++;
		}

	//----------- 7th Neighbour (South-East) ------------

		if (isValid (row+1, col+1) == true)
		{
			if (isMine (row+1, col+1, realBoard) == true)
			count++;
		}

	//----------- 8th Neighbour (South-West) ------------

		if (isValid (row+1, col-1) == true)
		{
			if (isMine (row+1, col-1, realBoard) == true)
			count++;
		}

	return (count);
}

// tabee bazgashti baraye ejraye game
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
			int mines[][2], int row, int col, int *movesLeft)
{

	// ghesmat asli tabee bazgashti
	if (myBoard[row][col] != '-')
		return (false);

	int i, j;

	// mine entekhab shode. check mikone va mige bakhti.
	if (realBoard[row][col] == '*')
	{
		myBoard[row][col]='*';

		for (i=0; i<MINES; i++)
			myBoard[mines[i][0]][mines[i][1]]='*';

		printBoard (myBoard);
		cout << "\nYou lost!\n";
		return (true) ;
	}

	else
	{
		// check mikone baraye hesab kardane bombaye atraaf
		int count = countAdjacentMines(row, col, mines, realBoard);
		(*movesLeft)--;

		myBoard[row][col] = count + '0';

		if (!count)
		{
			//----------- 1st Neighbour (North) ------------

			if (isValid (row-1, col) == true)
			{
				if (isMine (row-1, col, realBoard) == false)
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
			}

			//----------- 2nd Neighbour (South) ------------

			if (isValid (row+1, col) == true)
			{
				if (isMine (row+1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
			}

			//----------- 3rd Neighbour (East) ------------

			if (isValid (row, col+1) == true)
			{
				if (isMine (row, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
			}

			//----------- 4th Neighbour (West) ------------

			if (isValid (row, col-1) == true)
			{
				if (isMine (row, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
			}

			//----------- 5th Neighbour (North-East) ------------

			if (isValid (row-1, col+1) == true)
			{
				if (isMine (row-1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
			}

			//----------- 6th Neighbour (North-West) ------------

			if (isValid (row-1, col-1) == true)
			{
				if (isMine (row-1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
			}

			//----------- 7th Neighbour (South-East) ------------

			if (isValid (row+1, col+1) == true)
			{
				if (isMine (row+1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
			}

			//----------- 8th Neighbour (South-West) ------------

			if (isValid (row+1, col-1) == true)
			{
				if (isMine (row+1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
			}
		}

		return (false);
	}
}

// bombaro random pakhsh mikone
void placeMines(int mines[][2], char realBoard[][MAXSIDE])
{
	bool mark[MAXSIDE*MAXSIDE];

	memset (mark, false, sizeof (mark));

	// too in ba estefade az rand() besoorate random barname ro ejra mikone ta hame bomba pakhsh shan
	for (int i=0; i<MINES; )
	{
		int random = rand() % (SIDE*SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		// check mikone age bomb nabashe bomb ezafe mikone
		if (mark[random] == false)
		{
			// Radif bomb
			mines[i][0]= x;
			// sotoon bomb
			mines[i][1] = y;

			// bomb mizare
			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}

	return;
}

// baraye meghdar dehi random avvalie
void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])
{
	// baraye tekrari nashodan random mikone adad ha ro
	srand(time (NULL));

	// hame khoone haro bedoone bomb mikone
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}

	return;
}


// check mikone bomb mizare too ye jaye khali
void replaceMine (int row, int col, char board[][MAXSIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			{
				// avvalin jayi ke khali peyda she bomb mizare unja
				if (board[i][j] != '*')
				{
					board[i][j] = '*';
					board[row][col] = '-';
					return;
				}
			}
	}
	return;
}

// asl bazi
void playMinesweeper ()
{
	
	bool gameOver = false;// avval bazi bayad false bashe chon bazi tamoom nashode


	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE]; // inja dota arraye jadid taarif mikonim

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MAXMINES][2]; // x,y hame bombaro zakhire mikone

	initialise (realBoard, myBoard);

	placeMines (mines, realBoard);


	int currentMoveIndex = 0;
	while (gameOver == false)
	{
		cout << "Current Status of Board : \n";
		printBoard (myBoard);
		makeMove (x, y);

		// baraye inke avvalin khoone ke entekhab mishe bomb nabashe 
		if (currentMoveIndex == 0)
		{
			// age avvalin khoone bomb bashe az unja hazf mishe
			if (isMine (x, y, realBoard) == true)
				replaceMine (x, y, realBoard);
		}

		currentMoveIndex ++;

		gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);

		if ((gameOver == false) && (movesLeft == 0))
		{
			cout << "\nYou won !\n";
			gameOver = true;
		}
	}
	return;
}


int menu()
{	int input_menu;
	cout << "1) Start game \n2) how to play \n3) Exit \n";
	cin >> input_menu;
	if(input_menu==1)
	{
	SIDE = 8;
	MINES = 12;
	playMinesweeper ();

	}
	else if(input_menu==2)
	{
		cout << "a link to tutorial: https://www.wikihow.com/Play-Minesweeper\n";
	}
	else if(input_menu==3)
	{
		exit(0);
	}
	return 0;
	
}

int main()
{

	while(true)
	{
		menu();
	}
	return (0);
}
