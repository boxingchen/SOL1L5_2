/* File: lab5_2.c */
/* Alexander Ustyuzhanin, IE SO1 group 1, WS14, 22.11.2014 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define NUMBER_OF_DICE 3
#define WIDTH_OF_DICE 13
#define HIGHT_OF_ONE_DIE 6
#define POSSIBLE_DICE_VALUES 6
#define HIGHT_OF_DISPLAY 6
#define WIDTH_OF_DISPLAY (3*WIDTH_OF_DICE)
#define DELAY 1000 // 1 second delay between throws
void display(char dice[][HIGHT_OF_ONE_DIE][WIDTH_OF_DICE], int three_different_throws[]);
int check_for_triplets(int *);
int check_for_doubles(int *);

int main()
{
	char dice[POSSIBLE_DICE_VALUES][HIGHT_OF_ONE_DIE][WIDTH_OF_DICE] =
	{
		{{" _________ \0"},
		 {"|         |\0"},
		 {"|         |\0"},
		 {"|    O    |\0"},
		 {"|         |\0"},
		 {"|_________|\0"}},
		{{" _________ \0"},
		 {"|         |\0"},
		 {"| O       |\0"},
		 {"|         |\0"},
		 {"|       O |\0"},
		 {"|_________|\0"}},
		{{" _________ \0"},
		 {"|         |\0"},
		 {"| O       |\0"},
		 {"|    O    |\0"},
		 {"|       O |\0"},
		 {"|_________|\0"}},
		{{" _________ \0"},
		 {"|         |\0"},
		 {"| O     O |\0"},
		 {"|         |\0"},
		 {"| O     O |\0"},
		 {"|_________|\0"}},
		{{" _________ \0"},
		 {"|         |\0"},
		 {"| O     O |\0"},
		 {"|    O    |\0"},
		 {"| O     O |\0"},
		 {"|_________|\0"}},
 		{{" _________ \0"},
		 {"|         |\0"},
		 {"| O  O  O |\0"},
		 {"|         |\0"},
		 {"| O  O  O |\0"},
		 {"|_________|\0"}},
	};
	char key = 0;
	int doubles = 0;
	int triplets = 0;
	int three_different_throws[NUMBER_OF_DICE] = {0};
	int one_throw;
	int i = 0;
	time_t seed, ticks;
	seed = time(&ticks);
	srand((unsigned int) seed);
	

	while(key != 'e' && key != 'E')
	{
		// throw three times and display result on screen using display function
		for(i = 0; i < NUMBER_OF_DICE; i++)
		{
			three_different_throws[i] = 1 + rand()%6;
		}

		// count and display number of doubles and triplets
		display(dice, three_different_throws);
		if(check_for_triplets(three_different_throws))
			triplets++;
		else
			if(check_for_doubles(three_different_throws))
				doubles++;
		printf("\n*** doubles %d *** triplets %d ***\n", doubles, triplets);
		
		for(i=0; i < DELAY/10; i++)
		{
			if(kbhit())							// if a keystroke happens
				key = getch();					// write the value of the button
			Sleep(10);							// sleep 10 ms
		}
	}

	printf("\n");
	system("pause");
	return 0;
}

void display(char dice[][HIGHT_OF_ONE_DIE][WIDTH_OF_DICE], int three_different_throws[])
{
	int height, width;
	char screen[HIGHT_OF_DISPLAY][WIDTH_OF_DISPLAY];
	int i, j, k;

	for(j = 0; j < HIGHT_OF_ONE_DIE; j++)
	{
		width = 0;
		for(i = 0; i < NUMBER_OF_DICE; i++)
		{
			for(k = 0; k < WIDTH_OF_DICE; k++)
			{
				screen[j][width] = dice[three_different_throws[i]-1][j][k];
				width++;
			}
		}
	}

	for(height = 0; height < HIGHT_OF_DISPLAY; height++)
	{
		for(width = 0; width < WIDTH_OF_DISPLAY; width++)
		{
			printf("%c", screen[height][width]);
		}
		printf("\n");
	}
}

int check_for_triplets(int *ar)
{
	int isTriple = 0;
	if(ar[0] == ar[1] && ar[1] == ar[2])
		isTriple = 1;
	return isTriple;
}

int check_for_doubles(int *ar)
{
	int isDouble = 0;
	int counter = 0;
	int i, j;

	for(i = 0; i < NUMBER_OF_DICE; i++)
	{
		for(j = 0; j < NUMBER_OF_DICE; j++)
		{
			if(ar[i] == ar[j])
				counter++;
		}
	}

	if(counter == 5)	// 5 matches when comparing a 3-element array to itself means there is a double in there (3 is no doubles, 9 is a triplet)
		isDouble = 1;

	return isDouble;
}