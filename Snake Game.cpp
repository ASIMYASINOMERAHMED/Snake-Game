

#include <iostream>
#include<conio.h>
#include<Windows.h>


using namespace std;
bool GameOver;
int Width;
int Height;
int X, Y, FruitX, FruitY, Score, BlockX, BlockY;
int TailX[100], TailY[100];
int lenTail;    //Length Of The Tail
char HeadSign, FruitSign;
enum enDirection { STOP = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };
enum class enGameMode { Start = 1, color = 2, Settings = 3 };
enum class enColor { blue = 1, green = 2, yellow = 3 };
enum class enSettings { ChangeWidth = 1, ChangeHeight = 2, ChangeHead = 3, ChangeFruit = 4, Back = 5 };
enDirection Dir;
void Start();

void ChooseColor()
{
	cout << "\n****************************************\n";
	cout << "*               SNAKE GAME             *";
	cout << "\n****************************************\n";
	cout << "\n*1.blue                                *\n";
	cout << "\n*2.green                               *\n";
	cout << "\n*3.yellow                              *\n";
	cout << "\n* Choose Your Option?                  *\n";
	cout << "\n****************************************\n";
	int r;
	enColor Color;
	cin >> r;
	Color = (enColor)r;


	if (Color == enColor::blue)
	{
		system("color 9F");
	}
	else if (Color == enColor::green)
	{
		system("color 2F");
	}
	else if (Color == enColor::yellow)
	{
		system("color 6F");
	}
	else
	{
		system("cls");
		cout << "Wrong Choise!\a";
		ChooseColor();
	}

}
int ReadPositiveNumber(string Message)
{
	int Number;
	do
	{
		cout << Message << endl;
		cin >> Number;
	} while (Number <= 0);
	return Number;
}
void Settings()
{
	cout << "\n****************************************\n";
	cout << "*               SNAKE GAME             *";
	cout << "\n****************************************\n";
	cout << "\n*1.Change The Width Of The Game?       *\n";
	cout << "\n*2.Change The Height Of The Game?      *\n";
	cout << "\n*3.Change The Head Of The Snake?       *\n";
	cout << "\n*4.Change The Fruit?                   *\n";
	cout << "\n*5.Back?                               *\n";
	cout << "\n* Choose Your Option?                  *\n";
	cout << "\n****************************************\n";
	int s;
	enSettings Set = enSettings::ChangeWidth;
	cin >> s;
	Set = (enSettings)s;
	if (Set == enSettings::ChangeWidth)
	{
		system("cls");
		Width = ReadPositiveNumber("Enter The Width Of The Game?");
		system("cls");
		Settings();

	}
	else if (Set == enSettings::ChangeHeight)
	{
		system("cls");
		Height = ReadPositiveNumber("Enter The Height Of The Game?");
		system("cls");
		Settings();
	}
	else if (Set == enSettings::ChangeHead)
	{
		system("cls");
		cout << "Enter The Sign For The Head Of Snake?\n";
		cin >> HeadSign;
		system("cls");
		Settings();
	}
	else if (Set == enSettings::ChangeFruit)
	{
		system("cls");
		cout << "Enter The Sign For The Fruit?\n";
		cin >> FruitSign;
		system("cls");
		Settings();
	}
	else if (Set == enSettings::Back)
	{
		system("cls");
		Start();
	}
	else
	{
		system("cls");
		cout << "Wrong Choise!\a";
		Settings();
	}

}
void Start()
{
	cout << "\n****************************************\n";
	cout << "*               SNAKE GAME             *";
	cout << "\n****************************************\n";
	cout << "\n*1.Start                               *\n";
	cout << "\n*2.Color                               *\n";
	cout << "\n*3.Settings                            *\n";
	cout << "\n* Choose Your Option?                  *\n";
	cout << "\n****************************************\n";
	cout << "\n! Note That You Should Fill Settings Option Before You Start The Game!." << endl;
	int c;
	enGameMode mode;
	cin >> c;
	mode = (enGameMode)c;
	if (mode == enGameMode::Start)
	{
		Sleep(0);
	}
	else if (mode == enGameMode::color)
	{
		system("cls");
		ChooseColor();
		system("cls");
		Start();

	}
	else if (mode == enGameMode::Settings)
	{
		system("cls");
		Settings();
		system("cls");
		Start();
	}
	else
	{
		system("cls");
		cout << "Wrong Choise!\a" << endl;
		Start();


	}
}

void SetUp()
{

	GameOver = false;
	Dir = STOP;
	X = Width / 2;
	Y = Height / 2;
	FruitX = rand() % Width;
	FruitY = rand() % Height;
	BlockX = rand() % Width % 10;
	BlockY = rand() % Height % 10;
	Score = 0;



}

void Drow()
{

	system("cls");

	for (int i = 0;i < Width + 4;i++)
		cout << "#";

	cout << endl;

	for (int i = 0;i < Height;i++)
	{
		for (int j = 0;j < Width;j++)
		{
			if (j == 0)
				cout << "##";
			if (i == Y && j == X)
				cout << HeadSign;
			else if (i == FruitY && j == FruitX)
				cout << FruitSign;
			else
			{
				bool print = false;
				for (int K = 0;K < lenTail;K++)
				{

					if (TailX[K] == j && TailY[K] == i)
					{
						cout << "o";
						print = true;
					}

				}
				if (!print)
					cout << " ";
			}

			if (j == Width - 1)
				cout << "##";
		}
		cout << endl;
	}
	for (int i = 0;i < Width + 4;i++)
		cout << "#";
	cout << "\n\nYour Score: " << Score << endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'a':
			Dir = LEFT;
			break;
		case'd':
			Dir = RIGHT;
			break;
		case'w':
			Dir = UP;
			break;
		case's':
			Dir = DOWN;
			break;
		case'x':
			Start();
			break;
		}
	}
}
void Logic()
{
	int prevX = TailX[0];
	int prevY = TailY[0];
	int prev2X, prev2Y;
	TailX[0] = X;
	TailY[0] = Y;
	for (int i = 1;i < lenTail;i++)
	{
		prev2X = TailX[i];
		prev2Y = TailY[i];
		TailX[i] = prevX;
		TailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;


	}
	switch (Dir)
	{

	case LEFT:
		X--;
		break;
	case RIGHT:
		X++;
		break;
	case UP:
		Y--;
		break;
	case DOWN:
		Y++;
		break;
	default:
		break;
	}
	/*if (X > Width || X<0 || Y>Height || Y < 0)
		GameOver = true;*/
	if (X >= Width)
		X = 0;
	else if (X < 0)
		X = Width - 1;

	if (Y >= Height)
		Y = 0;
	else if (Y < 0)
		Y = Height - 1;
	for (int i = 0;i < lenTail;i++)
		if (TailX[i] == X && TailY[i] == Y)
		{
			system("cls");
			system("color 4F");
			char ask;
			cout << "\t\tGAME OVER!\a" << endl;
		
			cout << "\n\t\tYou hit yourself!\a" << endl;
			cout << "\n\t\tDo You Want To Continue? enter x to Continue OR enter any key to break the game" << endl;
			cin >> ask;
			if (ask == 'x')
			{
				system("cls");
				Start();
			}
			else
			{
				GameOver = true;
			}




		}
	if (X == FruitX && Y == FruitY)
	{
		Score += 10;
		FruitX = rand() % Width;
		FruitY = rand() % Height;
		lenTail++;
	}


}

int main()
{
	/*system("color 1F");*/


	Start();
	SetUp();
	while (!GameOver)
	{

		Drow();
		Input();
		Logic();
	}

}
