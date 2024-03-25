#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



#define WIDTH 80
#define HEIGHT 25
#define FILE_SIZE 100


void menu();
void choice_file(char file[FILE_SIZE], int choice, int matrix[WIDTH][HEIGHT]);
void initializeBoard(int matrix[WIDTH][HEIGHT], char *filename);
void draw(int matrix1[WIDTH][HEIGHT], int matrix2[WIDTH][HEIGHT]);
int alive_cell(int matrix[WIDTH][HEIGHT], int line, int col, int i, int j);
void replace(int matrix2[WIDTH][HEIGHT], int matrix1[WIDTH][HEIGHT]);
int count(int matrix[WIDTH][HEIGHT]);





int main(void)
{
    int choice;
    char file_name[FILE_SIZE];
    int stop = 0;
    int time_mlsec = 500;
    int board1[WIDTH][HEIGHT];
    int board2[WIDTH][HEIGHT];
    
    menu();
    if (scanf("%d", &choice) != 1)
    {
        printf("n/a");
        exit(1);
    }
    
    choice_file(file_name, choice, board1);



    while (stop != 1)
    {
        //char control_speed = getchar();

        if (count(board1) == 0) {
            printf("Все клетки погибли!");
            stop = 1;
        }
        time_mlsec += 1; //change_speed(control_speed, &stop, time_mlsec);

        usleep(time_mlsec * 1000);

        //clear();
        system("clear");

        draw(board1, board2);
        replace(board2, board1);
    }

    return 0;
}

// void input(int matrix[STR][COL])
// {
//     for (int i = 0; i < STR; i++)
//     {
//         for (int j = 0; j < COL; j++)
//         {
//             scanf("%d", &matrix[i][j]);
//         }
//     }
// }

void menu() {
    printf("\n");
    printf("Выбор фигур\n");
    printf("Чтобы выбрать 'Ружье' нажмите - [1]\n");
    printf("Чтобы выбрать 'Поезд' нажмите - [2]\n");
    printf("Чтобы выбрать 'Альпинист' нажмите - [3]\n");
    printf("Чтобы выбрать 'Движжение вперед' нажмите - [4]\n");
    printf("Чтобы выбрать 'Устойчивые фигуры' нажмите - [5]\n");
    printf("Чтобы ввести с помощью клавиатуры нажмите - [6]\n");
    printf("\n");
    // printf("Повышение скорости - [z]\n");
    // printf("Понижение скорости - [a]\n");
    // printf("Для возвращения в меню - [m]\n");
    // printf("Для выхода из игры - [q]\n");
}

void choice_file(char file[FILE_SIZE], int choice, int matrix[WIDTH][HEIGHT])
{
    if (choice >= 1 && choice <= 5)
    {
        sprintf(file, "initial_state%d.txt", choice);
        initializeBoard(matrix, file);
    }
    else if (choice == 6)
    {
        for (int i = 1; i < HEIGHT - 1; i++) {
                  for (int j = 1; j < WIDTH - 1; j++)
                      scanf("%d", &matrix[i][j]);
                }
    }
    else if (choice == 'q') {
        exit(1);
    }
    else
    {
        printf("n/a");
        exit(1);
    }
}

void initializeBoard(int matrix[WIDTH][HEIGHT], char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("n/a");
        exit(1);
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            fscanf(file, " %d", &matrix[i][j]);
        }
    }

    if (ferror(file))
    {
        printf("n/a");
        exit(1);
    }

    fclose(file);
}

void draw(int matrix1[WIDTH][HEIGHT], int matrix2[WIDTH][HEIGHT])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            matrix2[i][j] = alive_cell(matrix1, HEIGHT, WIDTH, i, j);
            if (matrix2[i][j] == 0)
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
        }
        printf("\n");
    }
}

int alive_cell(int matrix[WIDTH][HEIGHT], int line, int col, int i, int j) {
    int alive = 0;
    int alive_around = 0;


    int i_minus = i - 1, j_minus = j - 1, i_plus = i + 1, j_plus = j + 1;

    if (i_minus < 0)
    {
        i_minus = HEIGHT - 1;
    }
    if (j_minus < 0)
    {
        j_minus = WIDTH - 1;
    }
    if (i_plus > HEIGHT - 1)
    {
        i_plus = i_plus % HEIGHT;
    }
    if (j_plus > WIDTH - 1)
    {
        j_plus = j_plus % WIDTH;
    }

    alive_around += matrix[i_minus][j_minus];
    alive_around += matrix[i_minus][j];
    alive_around += matrix[i_minus][j_plus];
    alive_around += matrix[i][j_plus];
    alive_around += matrix[i_plus][j_plus];
    alive_around += matrix[i_plus][j];
    alive_around += matrix[i_plus][j_minus];
    alive_around += matrix[i][j_minus];

    if ((alive_around == 2 || alive_around == 3) && matrix[line][col]) {
        alive = 1;
    } else if (alive_around == 3 && !matrix[line][col]) {
        alive = 1;
    }
    return alive;
}

void replace(int matrix2[WIDTH][HEIGHT], int matrix1[WIDTH][HEIGHT])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            matrix1[i][j] = matrix2[i][j];
        }
    }
}

int count(int matrix[WIDTH][HEIGHT]) {
    int sum = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            sum += matrix[i][j];
        }
    }
    return sum;
}