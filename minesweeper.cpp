#include <iostream>
#include <ctime>
#include <cstdlib>


//decide the size of the minefield
const int SIZE = 15; 
const int MINES = 25; 

int randRange(int low, int high);
void createMinefield(char field[][SIZE], int size, int mines);
bool isMine(char field[][SIZE], int size, int x, int y);
int countNearMines(char field[][SIZE], int size, int x, int y);
void displayField(char field[][SIZE], int size);

int main(){
    // seed random number generator
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);

    char field[SIZE][SIZE];

    //create and display
    createMinefield(field, SIZE, MINES);
    displayField(field, SIZE);

    return 0;
}

int randRange(int low, int high){
    return rand() % (high - low + 1) + low;
}

void createMinefield(char field[][SIZE], int size,int mines){
    //clear the field
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j++) field[i][j] = ' ';
    }

    // place mines
    for (int m = 0; m < mines; m++){
        int x = randRange (0, size - 1);
        int y = randRange (0, size - 1);

        if (field[x][y] == ' '){
            field[x][y] = 'x';
        }
        else{
            m--;
        }
    }
    //fill in numbers
    for (int x = 0; x < size; x++){
        for (int y = 0; y < size; y++){
            if (field[x][y] != 'x'){
            int nearMines = countNearMines(field, size, x, y);
            if (nearMines > 0){
                field[x][y] = '0' + nearMines;
            }
        }
        }
    }

}

bool isMine(char field[][SIZE], int size, int x, int y){
    // false everything outsie field
    if (x < 0) return false;
    if (y < 0) return false;
    if (x >= size) return false;
    if (y >= size) return false;

    if (field[x][y] == 'x') return true;
    return false;
}


int countNearMines(char field[][SIZE], int size, int x, int y){
    int mines = 0; 

    if (isMine(field, size, x - 1, y - 1)) mines++;
    if (isMine(field, size, x - 1, y)) mines++;
    if (isMine(field, size, x - 1, y + 1)) mines++;
    if (isMine(field, size, x, y - 1)) mines++;
    if (isMine(field, size, x, y + 1)) mines++;
    if (isMine(field, size, x + 1, y - 1)) mines++;
    if (isMine(field, size, x + 1, y)) mines++;
    if (isMine(field, size, x + 1, y + 1)) mines++;
    
    return mines;
}

void displayField(char field[][SIZE], int size){
    for (int y = 0; y < size; y++){
        for (int x = 0; x < size; x++){
            std :: cout << field [x][y];
        }

        std::cout << std::endl;
    }
}