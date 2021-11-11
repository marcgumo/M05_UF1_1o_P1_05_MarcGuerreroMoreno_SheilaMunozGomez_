#include <iostream>;
using namespace std;

#define CONSOLE_HEIGHT 29
#define CONSOLE_WIDTH 119

void ImprimirPantalla();
void GenerarMapa();
void Inputs();
void Start();
void Logica();

enum MAP_TILES {EMPTY = ' ', WALL = '#', POINT = '.'};
enum USER_INPUTS {NONE, UP, DOWN, RIGHT, LEFT, QUIT};

MAP_TILES ConsoleScreen[CONSOLE_HEIGHT][CONSOLE_WIDTH];

char personaje = 'O';
int personaje_x = 10;
int personaje_y = 5;
USER_INPUTS input = USER_INPUTS::NONE;
bool quit = false;

int main() {
	
	Start();
	do
	{
		Inputs();
		Logica();
		ImprimirPantalla();
	} while (!quit);
}

void Start() {
	GenerarMapa();
	ImprimirPantalla();
}

void Inputs() {
	char input_raw;
	cin >> input_raw;

	switch (input_raw)
	{
		case 'W':
		case 'w':
			input = USER_INPUTS::UP;
			break;
		case 'A':
		case 'a':
			input = USER_INPUTS::LEFT;
			break;
		case 'S':
		case 's':
			input = USER_INPUTS::DOWN;
			break;
		case 'D':
		case 'd':
			input = USER_INPUTS::RIGHT;
			break;
		case 'Q':
		case 'q':
			input = USER_INPUTS::QUIT;
			break;
		default:
			input = USER_INPUTS::NONE;
			break;
	}
}

void Logica() {
	int personaje_y_new = personaje_y;
	int personaje_x_new = personaje_x;
	
	switch (input)
	{
	case UP:
		personaje_y_new--;
		break;
	case DOWN:
		personaje_y_new++;
		break;
	case RIGHT:
		personaje_x_new++;
		break;
	case LEFT:
		personaje_x_new--;
		break;
	case QUIT:
		quit = true;
		break;
	}

	if (ConsoleScreen[personaje_y_new][personaje_x_new] == MAP_TILES::WALL) {
		personaje_y_new = personaje_y;
		personaje_x_new = personaje_x;
	}
	personaje_y = personaje_y_new;
	personaje_x = personaje_x_new;
}

void GenerarMapa() {
	
	for (int i = 0; i < CONSOLE_HEIGHT; i++)
	{
		for (int j = 0; j < CONSOLE_WIDTH; j++)
		{
			if (i == 0 || i == CONSOLE_HEIGHT-1 || j == 0 || j == CONSOLE_WIDTH-1)
			{
				ConsoleScreen[i][j] = MAP_TILES::WALL;
			}
			else
			{
				ConsoleScreen[i][j] = MAP_TILES::EMPTY;
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
				cout << (char)ConsoleScreen[i][j];
			}
		}
		cout << endl;
	}
}