#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//ALLOCATE MEMORY FOR THE BOARD
char *create_board(){
    char *board = (char *)malloc(9 * sizeof(char));
    for(int i=0; i<9; i++){
        board[i] = ' ';
    }
    return board;
}

//FREE THE BOARD ALLOCATED MEMORY
void destroy_board(char *board){
    free(board);
}

//PRINTS THE BOARD
void show_board(char *board){
    printf(" %c | %c | %c\n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[6], board[7], board[8]);
}

//INSERTS THE PLAY ON THE BOARD
void *insert_board(char *board, int pos){
    static int turn = 0;
    if(turn % 2 == 0){
        board[pos] = 'X';
    }
    else{
        board[pos] = 'O';
    }
    turn++;
}

//VERIFY IF SOMEONE WON
int check_win(char *board){

    //VERIFY COLUMNS
    for(int i = 0; i<3; i++){
        int winX = 0, winO = 0;
        for(int j = i; j < 9; j += 3){
            if(board[j] == 'X')
                winX++;
            if(board[j] == 'O')
                winO++;
        }
        if(winX == 3){
            return 1;
        }
        if(winO == 3){
            return 2;
        }
    }

    //VERIFY ROWS
    for(int i = 0; i<9; i += 3){
        int winX = 0, winO = 0;
        for(int j = i; j < i+3; j++){
            if(board[j] == 'X')
                winX++;
            if(board[j] == 'O')
                winO++;
        }
        if(winX == 3){
            return 1;
        }
        if(winO == 3){
            return 2;
        }
    }
    
    //VERIFY LEFT UPPER TO RIGHT BOTTOM DIAGONAL
    int winXd1 = 0, winOd1 = 0;
    for(int i = 0; i<9; i += 4){
        if(board[i] == 'X')
            winXd1++;
        if(board[i] == 'O')
            winOd1++;

        if(winXd1 == 3){
            return 1;
        }
        if(winOd1 == 3){
            return 2;
        }
    }

    //VERIFY RIGHT UPPER TO LEFT BOTTOM DIAGONAL
    int winXd2 = 0, winOd2 = 0;
    for(int i = 2; i<7; i += 2){
        if(board[i] == 'X')
            winXd2++;
        if(board[i] == 'O')
            winOd2++;
            
        if(winXd2 == 3){
            return 1;
        }
        if(winOd2 == 3){
            return 2;
        }
    }

    return 0;
}

//VALIDATE CHOSEN POSITION
int valid_pos(char *board, int pos){
    if(board[pos] != ' '){
        return 0;
    }
    return 1;

}

int main(){

    printf("========================\n");
    printf(" WELCOME TO TIC TAC TOE\n");
    printf("========================\n");
    printf("Choose an option:\n");

    char loop = 0;
    int option;



    while(loop != 9){

        char *board = create_board();

        printf("[ 1 ] Single player\n");
        printf("[ 2 ] Multi player\n");
        printf("[ q ] Quit\n");
        printf("Your option: ");
        scanf(" %d", &option);

        if(option == 1){

            time_t t;
            srand((unsigned) time(&t));

            printf("\n\n========================\n");
            printf(" SINGLEPLAYER SELECTED\n");

            int currentPlayer = rand() % 2 + 1;
            int pos;

            for (int i = 0; i < 9; i++) {
                int pos;
                printf("========================\n");
                show_board(board);
                if (currentPlayer == 1) {
                    // Vez do jogador
                    printf("Your turn: ");
                    scanf("%d", &pos);

                    while (valid_pos(board, pos) == 0) {
                        printf("Invalid position.\nChoose from 0 to 8: ");
                        scanf("%d", &pos);
                    }
                } else {
                    // Vez do computador
                    printf("Computer's turn...\n");
                    do {
                        
                        pos = rand() % 9;
                    } while (valid_pos(board, pos) == 0);
                    printf("Computer chose position: %d\n", pos);
                }

                insert_board(board, pos);

                int result = check_win(board);
                if (result == 1 || result == 2) {
                    if (currentPlayer == 1) {
                        printf("========================\n");
                        show_board(board);
                        printf("Player Won!\n");
                    } else {
                        printf("========================\n");
                        show_board(board);
                        printf("Computer Won!\n");
                    }
                    printf("========================\n");
                    return 0;
                }

                // Trocar o jogador atual
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
            printf("Draw!");
            return 0;
        }

        if(option == 2){

            int pos;

            printf("========================\n");
            printf(" MULTIPLAYER SELECTED\n");
            printf("========================\n");
            printf("Player 1 will be 'X' and Player 2 will be 'O'\n\n");
            show_board(board);

            for(int i = 0; i<9; i++){
                if(i % 2 ==0 )
                    printf("Player 1 position: ");
                else
                    printf("Player 2 position: ");

                scanf("%d", &pos);
                while(valid_pos(board, pos) == 0){
                    if(pos < 0 || pos > 8){
                        printf("\nInvalid position.\nChoose from 0 to 8: ");
                    }else if(valid_pos(board, pos == 0)){
                        printf("\nPosition already occupied.\nChoose another: ");
                    }
                    scanf("%d", &pos);
                }

                insert_board(board, pos);
                printf("========================\n");
                show_board(board);
                printf("========================\n");
                    
                if(i>=4){
                    int i = check_win(board);
                    if(i == 1){
                        printf("========================\n");
                        show_board(board);
                        printf("Player 1 (X) Won!\n");
                        printf("========================\n");
                        return 0;
                    }
                    if(i == 2){
                        printf("========================\n");
                        show_board(board);
                        printf("Player 2 (0) Won!\n");
                        printf("========================\n");
                        return 0;
                    }
                }
            }
            printf("Draw!");
            return 0;
        }
        destroy_board(board);
    }

}