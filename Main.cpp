#include <iostream>
#include <conio.h>
using namespace std;

#define CONSOLE_HEIGHT 29
#define CONSOLE_WIDTH 119
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define TECLA_DERECHA 77
#define TECLA_IZQUIERDA 75
#define ESC 27

#define BBACK "\u001b[40m"
#define BBBACK "\u001b[40;1m"
#define BMB "\u001b[45;1m"
#define BLUEBACK "\u001b[44m"
#define BLUE "\u001b[34m"
#define CYNBACK "\u001b[46m"
#define YELLOW "\u001b[33;1m"
#define RESET "\u001b[0m"

void ImprimirPantalla();
void GenerarMapa();
void Inputs();
void Start();
void Logica();

enum MAP_TILES {EMPTY = ' ', WALL = 39, POINT = '.' };
enum USER_INPUTS {NONE, UP, DOWN, RIGHT, LEFT, QUIT};

MAP_TILES ConsoleScreen[CONSOLE_HEIGHT][CONSOLE_WIDTH];

char personaje = 'O';
int personaje_x = 10;
int personaje_y = 5;
int map_points = 0;
int player_points = 0;
USER_INPUTS input = USER_INPUTS::NONE;
bool quit = false;
bool win = false;

int main() {
	
	Start();
	do
	{
		Inputs();
		Logica();
		ImprimirPantalla();
	} while (!quit && !win);

	if (win) cout << CYNBACK << BMB << endl << "FELICIDADES HAS GANADO!!" << RESET << endl;
}

void Start() {
	GenerarMapa();
	ImprimirPantalla();
}

void Inputs() {
	char input_raw;
	input_raw = _getch();

	switch (input_raw)
	{
		case 'W':
		case 'w':
		case TECLA_ARRIBA:
			input = USER_INPUTS::UP;
			break;
		case 'A':
		case 'a':
		case TECLA_IZQUIERDA:
			input = USER_INPUTS::LEFT;
			break;
		case 'S':
		case 's':
		case TECLA_ABAJO:
			input = USER_INPUTS::DOWN;
			break;
		case 'D':
		case 'd':
		case TECLA_DERECHA:
			input = USER_INPUTS::RIGHT;
			break;
		case 'Q':
		case 'q':
		case ESC:
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
	
	personaje_x_new %= CONSOLE_WIDTH;

	if (personaje_x_new < 0) {
		personaje_x_new = CONSOLE_WIDTH - 1;
	}
	personaje_x_new %= CONSOLE_WIDTH;

	if (personaje_y_new < 0) {
		personaje_y_new = CONSOLE_HEIGHT - 1;
	}
	personaje_y_new %= CONSOLE_HEIGHT;

	if (ConsoleScreen[personaje_y_new][personaje_x_new] == MAP_TILES::WALL) {
		personaje_y_new = personaje_y;
		personaje_x_new = personaje_x;
	}
	else if (ConsoleScreen[personaje_y_new][personaje_x_new] == MAP_TILES::POINT) {
		map_points--;
		player_points++;
		ConsoleScreen[personaje_y_new][personaje_x_new] = MAP_TILES::EMPTY;
	}
	personaje_y = personaje_y_new;
	personaje_x = personaje_x_new;

	if (map_points == 0) win = true;
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

	for (int i = 55; i < 65; i++)
	{
		ConsoleScreen[0][i] = MAP_TILES::POINT;
		map_points++;
		ConsoleScreen[CONSOLE_HEIGHT - 1][i] = MAP_TILES::POINT;
		map_points++;
	}
	for (int i = 10; i < 20; i++)
	{
		ConsoleScreen[i][0] = MAP_TILES::POINT;
		map_points++;
		ConsoleScreen[i][CONSOLE_WIDTH - 1] = MAP_TILES::POINT;
		map_points++;
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
			else if (ConsoleScreen[i][j] == MAP_TILES::WALL)
			{
				cout << BLUEBACK << BLUE << (char)ConsoleScreen[i][j] << RESET;
			}
			else if (ConsoleScreen[i][j] == MAP_TILES::EMPTY)
			{
				cout << BBBACK << (char)ConsoleScreen[i][j] << RESET;
			}
			else if (ConsoleScreen[i][j] == MAP_TILES::POINT)
			{
				cout << YELLOW << (char)ConsoleScreen[i][j] << RESET;
			}
			else cout << (char)ConsoleScreen[i][j];
		}
		cout << endl;
	}
	cout << RESET;
	cout << player_points << "/" << map_points << endl;
}
