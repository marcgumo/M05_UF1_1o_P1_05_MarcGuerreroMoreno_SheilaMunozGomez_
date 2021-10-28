#include <iostream>;
using namespace std;

#define CONSOLE_HEIGHT 29
#define CONSOLE_WIDTH 119

void ImprimirPantalla();
void GenerarMapa();
void Inputs();
void Start();

char consolScreen[CONSOLE_HEIGHT][CONSOLE_WIDTH];
char personaje = 'O';
int personaje_x = 10;
int personaje_y = 5;
bool quit = false;

int main() {
	
	Start();
	do
	{
		Inputs();
		ImprimirPantalla();
	} while (!quit);
}

void Start() {
	GenerarMapa();
	ImprimirPantalla();
}

void Inputs() {
	char input;
	cin >> input;

	switch (input)
	{
		case 'W':
		case 'w':
			personaje_y--;
			break;
		case 'A':
		case 'a':
			personaje_x--;
			break;
		case 'S':
		case 's':
			personaje_y++;
			break;
		case 'D':
		case 'd':
			personaje_x++;
			break;
		case 'Q':
		case 'q':
			quit = true;
			break;
		default:
			break;
	}
}

void GenerarMapa() {
	
	for (int i = 0; i < CONSOLE_HEIGHT; i++)
	{
		for (int j = 0; j < CONSOLE_WIDTH; j++)
		{
			if (i == 0 || i == CONSOLE_HEIGHT-1 || j == 0 || j == CONSOLE_WIDTH-1)
			{
				consolScreen[i][j] = '#';
			}
			else
			{
				consolScreen[i][j] = '-';
			}
		}
		cout << endl;
	}
}

void ImprimirPantalla() {
	
	system("cls");
	
	for (int i = 0; i < CONSOLE_HEIGHT; i++)
	{
		for (int j = 0; j < CONSOLE_WIDTH; j++)
		{
			if (personaje_x == j && personaje_y == i)
			{
				cout << personaje;
			}
			else
			{
				cout << consolScreen[i][j];
			}
		}
		cout << endl;
	}
	
	
	for (size_t i = 0; i < 3; i++)
	{
		cout << endl;
	}
	
}