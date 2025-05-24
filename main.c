#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAWN_MOVES 4
#define ROOK_MOVES 14
#define BISHOP_MOVES 13
#define KNIGHT_MOVES 8
#define QUEEN_MOVES 27
#define KING_MOVES 10
#define TOTAL_MOVES (KING_MOVES + QUEEN_MOVES + (ROOK_MOVES * 2) + (BISHOP_MOVES * 2) + (KNIGHT_MOVES * 2) + (PAWN_MOVES * 8))

#define GET_SPACE_BY_DISTANCE(Y, X) game->board[current_space->y + Y][current_space->x + X]            

typedef enum {
    PAWN = 'P',
    ROOK = 'R',
    KNIGHT = 'N',
    BISHOP = 'B',
    QUEEN = 'Q',
    KING = 'K'
} PieceType;

const char WHITE = 'w';
const char BLACK = 'b';
const char BOTH = 'o';

const char HUMAN = 'h';
const char COMPUTER = 'c';

const char NO = 'n';
const char YES = 'y';

const char QUIT = 'q';
const char SKIP = 's';

const char CHECK = 'c';
const char CHECKMATE = 'm';
const char STALEMATE = 't';

typedef struct {
    PieceType type;
    char color;
    char moves;
} Piece;

typedef struct {
    char x, y;
    Piece* piece;
    char color;
} Space;

void free_space(Space* s) {
    if (s == NULL) return;
    //free(s->piece); don't free pieces here, they are freed in the free_player function
    free(s);
}

void free_space_copy(Space* s) {
    if (s == NULL) return;
    if (s->piece != NULL) {
        free(s->piece);
        s->piece = NULL;
    }
}

typedef struct {
    Piece* pieces[16];
    char color;
    char control_type;
} Player;

void free_player(Player* p) {
    if (p == NULL) return;

    for (int i = 0; i < 16; i++) {
        if (p->pieces[i] != NULL) {
            free(p->pieces[i]); 
        }
    }
    free(p); //RIGHT HERE IT CRASHES
}

typedef struct Game {
    Space* board[8][8];
    Player* players1;
    Player* players2;
    char turn;
} Game;

void free_game(Game* g) {
    if (g == NULL) return;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (g->board[i][j] != NULL) {
                free_space(g->board[i][j]);
            }
        }
    }
    
    if (g->players1 != NULL) {
        free_player(g->players1);
    }
    
    if (g->players2 != NULL) {
        free_player(g->players2);
    }
    
    free(g);
}

Game* create_game(char players) {
    Game* game = (Game*)malloc(sizeof(Game));
    if (game == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    game->turn = WHITE;

    Player* p1 = (Player*)malloc(sizeof(Player));
    p1->color = WHITE;
    p1->control_type = players > 0 ? HUMAN : COMPUTER;
    Piece* wP1 = (Piece*)malloc(sizeof(Piece));
    wP1->color = WHITE;
    wP1->type = PAWN;
    wP1->moves = 0;
    p1->pieces[0] = wP1;
    Piece* wP2 = (Piece*)malloc(sizeof(Piece));
    wP2->color = WHITE;
    wP2->type = PAWN;
    wP2->moves = 0;
    p1->pieces[1] = wP2;
    Piece* wP3 = (Piece*)malloc(sizeof(Piece));
    wP3->color = WHITE;
    wP3->type = PAWN;
    wP3->moves = 0;
    p1->pieces[2] = wP3;
    Piece* wP4 = (Piece*)malloc(sizeof(Piece));
    wP4->color = WHITE;
    wP4->type = PAWN;
    wP4->moves = 0;
    p1->pieces[3] = wP4;
    Piece* wP5 = (Piece*)malloc(sizeof(Piece));
    wP5->color = WHITE;
    wP5->type = PAWN;
    wP5->moves = 0;
    p1->pieces[4] = wP5;
    Piece* wP6 = (Piece*)malloc(sizeof(Piece));
    wP6->color = WHITE;
    wP6->type = PAWN;
    wP6->moves = 0;
    p1->pieces[5] = wP6;
    Piece* wP7 = (Piece*)malloc(sizeof(Piece));
    wP7->color = WHITE;
    wP7->type = PAWN;
    wP7->moves = 0;
    p1->pieces[6] = wP7;
    Piece* wP8 = (Piece*)malloc(sizeof(Piece));
    wP8->color = WHITE;
    wP8->type = PAWN;
    wP8->moves = 0;
    p1->pieces[7] = wP8;
    Piece* wR1 = (Piece*)malloc(sizeof(Piece));
    wR1->color = WHITE;
    wR1->type = ROOK;
    wR1->moves = 0;
    p1->pieces[8] = wR1;
    Piece* wR2 = (Piece*)malloc(sizeof(Piece));
    wR2->color = WHITE;
    wR2->type = ROOK;
    wR2->moves = 0;
    p1->pieces[9] = wR2;
    Piece* wN1 = (Piece*)malloc(sizeof(Piece));
    wN1->color = WHITE;
    wN1->type = KNIGHT;
    wN1->moves = 0;
    p1->pieces[10] = wN1;
    Piece* wN2 = (Piece*)malloc(sizeof(Piece));
    wN2->color = WHITE;
    wN2->type = KNIGHT;
    wN2->moves = 0;
    p1->pieces[11] = wN2;
    Piece* wB1 = (Piece*)malloc(sizeof(Piece));
    wB1->color = WHITE;
    wB1->type = BISHOP;
    wB1->moves = 0;
    p1->pieces[12] = wB1;
    Piece* wB2 = (Piece*)malloc(sizeof(Piece));
    wB2->color = WHITE;
    wB2->type = BISHOP;
    wB2->moves = 0;
    p1->pieces[13] = wB2;
    Piece* wQ = (Piece*)malloc(sizeof(Piece));
    wQ->color = WHITE;
    wQ->type = QUEEN;
    wQ->moves = 0;
    p1->pieces[14] = wQ;
    Piece* wK = (Piece*)malloc(sizeof(Piece));
    wK->color = WHITE;
    wK->type = KING;
    wK->moves = 0;
    p1->pieces[15] = wK;

    Player* p2 = (Player*)malloc(sizeof(Player));
    p2->color = BLACK;
    p2->control_type = players > 1 ? HUMAN : COMPUTER;
    Piece* bP1 = (Piece*)malloc(sizeof(Piece));
    bP1->color = BLACK;
    bP1->type = PAWN;
    bP1->moves = 0;
    p2->pieces[0] = bP1;
    Piece* bP2 = (Piece*)malloc(sizeof(Piece));
    bP2->color = BLACK;
    bP2->type = PAWN;
    bP2->moves = 0;
    p2->pieces[1] = bP2;
    Piece* bP3 = (Piece*)malloc(sizeof(Piece));
    bP3->color = BLACK;
    bP3->type = PAWN;
    bP3->moves = 0;
    p2->pieces[2] = bP3;
    Piece* bP4 = (Piece*)malloc(sizeof(Piece));
    bP4->color = BLACK;
    bP4->type = PAWN;
    bP4->moves = 0;
    p2->pieces[3] = bP4;
    Piece* bP5 = (Piece*)malloc(sizeof(Piece));
    bP5->color = BLACK;
    bP5->type = PAWN;
    bP5->moves = 0;
    p2->pieces[4] = bP5;
    Piece* bP6 = (Piece*)malloc(sizeof(Piece));
    bP6->color = BLACK;
    bP6->type = PAWN;
    bP6->moves = 0;
    p2->pieces[5] = bP6;
    Piece* bP7 = (Piece*)malloc(sizeof(Piece));
    bP7->color = BLACK;
    bP7->type = PAWN;
    bP7->moves = 0;
    p2->pieces[6] = bP7;
    Piece* bP8 = (Piece*)malloc(sizeof(Piece));
    bP8->color = BLACK;
    bP8->type = PAWN;
    bP8->moves = 0;
    p2->pieces[7] = bP8;
    Piece* bR1 = (Piece*)malloc(sizeof(Piece));
    bR1->color = BLACK;
    bR1->type = ROOK;
    bR1->moves = 0;
    p2->pieces[8] = bR1;
    Piece* bR2 = (Piece*)malloc(sizeof(Piece));
    bR2->color = BLACK;
    bR2->type = ROOK;
    bR2->moves = 0;
    p2->pieces[9] = bR2;
    Piece* bN1 = (Piece*)malloc(sizeof(Piece));
    bN1->color = BLACK;
    bN1->type = KNIGHT;
    bN1->moves = 0;
    p2->pieces[10] = bN1;
    Piece* bN2 = (Piece*)malloc(sizeof(Piece));
    bN2->color = BLACK;
    bN2->type = KNIGHT;
    bN2->moves = 0;
    p2->pieces[11] = bN2;
    Piece* bB1 = (Piece*)malloc(sizeof(Piece));
    bB1->color = BLACK;
    bB1->type = BISHOP;
    bB1->moves = 0;
    p2->pieces[12] = bB1;
    Piece* bB2 = (Piece*)malloc(sizeof(Piece));
    bB2->color = BLACK;
    bB2->type = BISHOP;
    bB2->moves = 0;
    p2->pieces[13] = bB2;
    Piece* bQ = (Piece*)malloc(sizeof(Piece));
    bQ->color = BLACK;
    bQ->type = QUEEN;
    bQ->moves = 0;
    p2->pieces[14] = bQ;
    Piece* bK = (Piece*)malloc(sizeof(Piece));
    bK->color = BLACK;
    bK->type = KING;
    bK->moves = 0;
    p2->pieces[15] = bK;

    game->players1 = p1;
    game->players2 = p2;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            game->board[i][j] = (Space*)malloc(sizeof(Space));
            if (game->board[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed for board[%d][%d]\n", i, j);
                exit(EXIT_FAILURE);
            }
            game->board[i][j]->x = j;
            game->board[i][j]->y = i;
            game->board[i][j]->piece = NULL;
            game->board[i][j]->color = ((i * 8) + j) % 2 == 0 ? WHITE : BLACK;
        }
    }

    game->board[7][0]->piece = wR1;
    game->board[7][1]->piece = wN1;
    game->board[7][2]->piece = wB1;
    game->board[7][3]->piece = wQ;
    game->board[7][4]->piece = wK;
    game->board[7][5]->piece = wB2;
    game->board[7][6]->piece = wN2;
    game->board[7][7]->piece = wR2;
    game->board[6][0]->piece = wP1;
    game->board[6][1]->piece = wP2;
    game->board[6][2]->piece = wP3;
    game->board[6][3]->piece = wP4;
    game->board[6][4]->piece = wP5;
    game->board[6][5]->piece = wP6;
    game->board[6][6]->piece = wP7;
    game->board[6][7]->piece = wP8;

    game->board[0][0]->piece = bR1;
    game->board[0][1]->piece = bN1;
    game->board[0][2]->piece = bB1;
    game->board[0][3]->piece = bQ;
    game->board[0][4]->piece = bK;
    game->board[0][5]->piece = bB2;
    game->board[0][6]->piece = bN2;
    game->board[0][7]->piece = bR2;
    game->board[1][0]->piece = bP1;
    game->board[1][1]->piece = bP2;
    game->board[1][2]->piece = bP3;
    game->board[1][3]->piece = bP4;
    game->board[1][4]->piece = bP5;
    game->board[1][5]->piece = bP6;
    game->board[1][6]->piece = bP7;
    game->board[1][7]->piece = bP8;

    return game;
}

char* peice_to_string(Piece* p) {
    char* result = (char*)malloc(4);
    result[0] = p->color;
    result[1] = ' ';
    result[2] = p->type;
    result[3] = '\0';
    return result;
}

void print_game(Game* g) {
    printf("      A       B       C       D       E       F       G       H\n");
    printf("  | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |\n");
    printf("1 |       | ##### |       | ##### |       | ##### |       | ##### |\n");
    printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", 
        g->board[0][0]->piece ? peice_to_string(g->board[0][0]->piece) : "   ",
        g->board[0][1]->piece ? peice_to_string(g->board[0][1]->piece) : "   ",
        g->board[0][2]->piece ? peice_to_string(g->board[0][2]->piece) : "   ",
        g->board[0][3]->piece ? peice_to_string(g->board[0][3]->piece) : "   ",
        g->board[0][4]->piece ? peice_to_string(g->board[0][4]->piece) : "   ",
        g->board[0][5]->piece ? peice_to_string(g->board[0][5]->piece) : "   ",
        g->board[0][6]->piece ? peice_to_string(g->board[0][6]->piece) : "   ",
        g->board[0][7]->piece ? peice_to_string(g->board[0][7]->piece) : "   ");
    printf("  | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |\n");
    printf("2 | ##### |       | ##### |       | ##### |       | ##### |       |\n");
    printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", 
        g->board[1][0]->piece ? peice_to_string(g->board[1][0]->piece) : "   ",
        g->board[1][1]->piece ? peice_to_string(g->board[1][1]->piece) : "   ",
        g->board[1][2]->piece ? peice_to_string(g->board[1][2]->piece) : "   ",
        g->board[1][3]->piece ? peice_to_string(g->board[1][3]->piece) : "   ",
        g->board[1][4]->piece ? peice_to_string(g->board[1][4]->piece) : "   ",
        g->board[1][5]->piece ? peice_to_string(g->board[1][5]->piece) : "   ",
        g->board[1][6]->piece ? peice_to_string(g->board[1][6]->piece) : "   ",
        g->board[1][7]->piece ? peice_to_string(g->board[1][7]->piece) : "   ");
    printf("  | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |\n");
    printf("3 |       | ##### |       | ##### |       | ##### |       | ##### |\n");
    printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", 
        g->board[2][0]->piece ? peice_to_string(g->board[2][0]->piece) : "   ",
        g->board[2][1]->piece ? peice_to_string(g->board[2][1]->piece) : "   ",
        g->board[2][2]->piece ? peice_to_string(g->board[2][2]->piece) : "   ",
        g->board[2][3]->piece ? peice_to_string(g->board[2][3]->piece) : "   ",
        g->board[2][4]->piece ? peice_to_string(g->board[2][4]->piece) : "   ",
        g->board[2][5]->piece ? peice_to_string(g->board[2][5]->piece) : "   ",
        g->board[2][6]->piece ? peice_to_string(g->board[2][6]->piece) : "   ",
        g->board[2][7]->piece ? peice_to_string(g->board[2][7]->piece) : "   ");
    printf("  | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |\n");
    printf("4 | ##### |       | ##### |       | ##### |       | ##### |       |\n");
    printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", 
        g->board[3][0]->piece ? peice_to_string(g->board[3][0]->piece) : "   ",
        g->board[3][1]->piece ? peice_to_string(g->board[3][1]->piece) : "   ",
        g->board[3][2]->piece ? peice_to_string(g->board[3][2]->piece) : "   ",
        g->board[3][3]->piece ? peice_to_string(g->board[3][3]->piece) : "   ",
        g->board[3][4]->piece ? peice_to_string(g->board[3][4]->piece) : "   ",
        g->board[3][5]->piece ? peice_to_string(g->board[3][5]->piece) : "   ",
        g->board[3][6]->piece ? peice_to_string(g->board[3][6]->piece) : "   ",
        g->board[3][7]->piece ? peice_to_string(g->board[3][7]->piece) : "   ");
    printf("  | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |\n");
    printf("5 |       | ##### |       | ##### |       | ##### |       | ##### |\n");
    printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", 
        g->board[4][0]->piece ? peice_to_string(g->board[4][0]->piece) : "   ",
        g->board[4][1]->piece ? peice_to_string(g->board[4][1]->piece) : "   ",
        g->board[4][2]->piece ? peice_to_string(g->board[4][2]->piece) : "   ",
        g->board[4][3]->piece ? peice_to_string(g->board[4][3]->piece) : "   ",
        g->board[4][4]->piece ? peice_to_string(g->board[4][4]->piece) : "   ",
        g->board[4][5]->piece ? peice_to_string(g->board[4][5]->piece) : "   ",
        g->board[4][6]->piece ? peice_to_string(g->board[4][6]->piece) : "   ",
        g->board[4][7]->piece ? peice_to_string(g->board[4][7]->piece) : "   ");
    printf("  | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |\n");
    printf("6 | ##### |       | ##### |       | ##### |       | ##### |       |\n");
    printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", 
        g->board[5][0]->piece ? peice_to_string(g->board[5][0]->piece) : "   ",
        g->board[5][1]->piece ? peice_to_string(g->board[5][1]->piece) : "   ",
        g->board[5][2]->piece ? peice_to_string(g->board[5][2]->piece) : "   ",
        g->board[5][3]->piece ? peice_to_string(g->board[5][3]->piece) : "   ",
        g->board[5][4]->piece ? peice_to_string(g->board[5][4]->piece) : "   ",
        g->board[5][5]->piece ? peice_to_string(g->board[5][5]->piece) : "   ",
        g->board[5][6]->piece ? peice_to_string(g->board[5][6]->piece) : "   ",
        g->board[5][7]->piece ? peice_to_string(g->board[5][7]->piece) : "   ");
    printf("  | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |\n");
    printf("7 |       | ##### |       | ##### |       | ##### |       | ##### |\n");
    printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", 
        g->board[6][0]->piece ? peice_to_string(g->board[6][0]->piece) : "   ",
        g->board[6][1]->piece ? peice_to_string(g->board[6][1]->piece) : "   ",
        g->board[6][2]->piece ? peice_to_string(g->board[6][2]->piece) : "   ",
        g->board[6][3]->piece ? peice_to_string(g->board[6][3]->piece) : "   ",
        g->board[6][4]->piece ? peice_to_string(g->board[6][4]->piece) : "   ",
        g->board[6][5]->piece ? peice_to_string(g->board[6][5]->piece) : "   ",
        g->board[6][6]->piece ? peice_to_string(g->board[6][6]->piece) : "   ",
        g->board[6][7]->piece ? peice_to_string(g->board[6][7]->piece) : "   ");
    printf("  | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |\n");
    printf("8 | ##### |       | ##### |       | ##### |       | ##### |       |\n");
    printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", 
        g->board[7][0]->piece ? peice_to_string(g->board[7][0]->piece) : "   ",
        g->board[7][1]->piece ? peice_to_string(g->board[7][1]->piece) : "   ",
        g->board[7][2]->piece ? peice_to_string(g->board[7][2]->piece) : "   ",
        g->board[7][3]->piece ? peice_to_string(g->board[7][3]->piece) : "   ",
        g->board[7][4]->piece ? peice_to_string(g->board[7][4]->piece) : "   ",
        g->board[7][5]->piece ? peice_to_string(g->board[7][5]->piece) : "   ",
        g->board[7][6]->piece ? peice_to_string(g->board[7][6]->piece) : "   ",
        g->board[7][7]->piece ? peice_to_string(g->board[7][7]->piece) : "   ");
    printf("  | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |\n");
}

void get_pawn_possibilities(Game* game, Space* current_space, char turn, Space* possibilities[], int* count) {
    if (turn == WHITE) {
        if (current_space->piece->moves == 0 && GET_SPACE_BY_DISTANCE(-1, 0)->piece == NULL && GET_SPACE_BY_DISTANCE(-2, 0)->piece == NULL) {
            // moves forward 2 spaces
            possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(-2, 0);
        }
        if ((int)current_space->y - 1 >= 0 && GET_SPACE_BY_DISTANCE(-1, 0)->piece == NULL) {
            // moves forward 1 space
            possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(-1, 0);
        }
        if ((int)current_space->y - 1 >= 0 && (int)current_space->x - 1 >= 0 && GET_SPACE_BY_DISTANCE(-1, -1)->piece != NULL && GET_SPACE_BY_DISTANCE(-1, -1)->piece->color != turn) {
            // eats opponent's piece left
            possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(-1, -1);
        } 
        if ((int)current_space->y - 1 >= 0 && GET_SPACE_BY_DISTANCE(-1, 1)->piece != NULL && GET_SPACE_BY_DISTANCE(-1, 1)->piece->color != turn) {
            // eats opponent's piece right
            possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(-1, 1);
        }
    } else {
        if (current_space->piece->moves == 0 && GET_SPACE_BY_DISTANCE(1, 0)->piece == NULL && GET_SPACE_BY_DISTANCE(2, 0)->piece == NULL) {
            // moves forward 2 spaces
            possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(2, 0);
        }
        if (GET_SPACE_BY_DISTANCE(1, 0)->piece == NULL) {
            // moves forward 1 space
            possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(1, 0);
        }
        if ((int)current_space->x - 1 >= 0 && GET_SPACE_BY_DISTANCE(1, -1)->piece != NULL && GET_SPACE_BY_DISTANCE(1, -1)->piece->color != turn) {
            // eats opponent's piece left
            possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(1, -1);
        } 
        if (GET_SPACE_BY_DISTANCE(1, 1)->piece != NULL && GET_SPACE_BY_DISTANCE(1, 1)->piece->color != turn) {
            // eats opponent's piece right
            possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(1, 1);
        }
    }
}

char valid_pawn_move(Game* game, Space* current_space, Space* target_space) {
    int count = 0;
    Space* possibilities[PAWN_MOVES];
    get_pawn_possibilities(game, current_space, game->turn, possibilities, &count);
    
    for (int i = 0; i < count; i++) {
        if (possibilities[i]->x == target_space->x && possibilities[i]->y == target_space->y) {
            return YES;
        }
    }

    printf("Invalid move for pawn\n");
    return NO;
}

void get_rook_possibilities(Game* game, Space* current_space, char turn, Space* possibilities[], int* count) {
    for (int i = 1; i < 8; i++) { // left
        if ((int)current_space->x - i < 0) break;
        Space* space = GET_SPACE_BY_DISTANCE(0, -i);
        if (space->piece != NULL) {
            if (space->piece->color != turn) {
                possibilities[(*count)++] = space;
            }
            break;
        }
        possibilities[(*count)++] = space;
    }
    for (int i = 1; i < 8; i++) { // right
        if (current_space->x + i > 7) break;
        Space* space = GET_SPACE_BY_DISTANCE(0, i);
        if (space->piece != NULL) {
            if (space->piece->color != turn) {
                possibilities[(*count)++] = space;
            }
            break;
        }
        possibilities[(*count)++] = space;
    }
    for (int i = 1; i < 8; i++) { // up
        if ((int)current_space->y - i < 0) break;
        Space* space = GET_SPACE_BY_DISTANCE(-i, 0);
        if (space->piece != NULL) {
            if (space->piece->color != turn) {
                possibilities[(*count)++] = space;
            }
            break;
        }
        possibilities[(*count)++] = space;
    }
    for (int i = 1; i < 8; i++) { // down
        if (current_space->y + i > 7) break;
        Space* space = GET_SPACE_BY_DISTANCE(i, 0);
        if (space->piece != NULL) {
            if (space->piece->color != turn) {
                possibilities[(*count)++] = space;
            }
            break;
        }
        possibilities[(*count)++] = space;
    }
}

char valid_rook_move(Game* game, Space* current_space, Space* target_space) {
    int count = 0;
    Space* possibilities[ROOK_MOVES];
    get_rook_possibilities(game, current_space, game->turn, possibilities, &count);

    for (int i = 0; i < count; i++) {
        if (possibilities[i]->x == target_space->x && possibilities[i]->y == target_space->y) {
            return YES;
        }
    }

    printf("Invalid move for rook\n");
    return NO;
}

Space* get_knight_possibilities(Game* game, Space* current_space, char turn, Space* possibilities[], int* count) {
    int x_moves[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int y_moves[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (int i = 0; i < 8; i++) {
        int new_x = current_space->x + x_moves[i];
        int new_y = current_space->y + y_moves[i];
        if (new_x >= 0 && new_x <= 7 && new_y >= 0 && new_y <= 7) {
            Space* space = game->board[new_y][new_x];
            if (space->piece != NULL && space->piece->color == turn) {
                continue;
            }
            possibilities[(*count)++] = space;
        }
    }
}

char valid_knight_move(Game* game, Space* current_space, Space* target_space) {
    int count = 0;
    Space* possibilities[KNIGHT_MOVES];
    get_knight_possibilities(game, current_space, game->turn, possibilities, &count);

    for (int i = 0; i < count; i++) {
        if (possibilities[i]->x == target_space->x && possibilities[i]->y == target_space->y) {
            return YES;
        }
    }

    printf("Invalid move for knight\n");
    return NO;
}

Space* get_bishop_possibilities(Game* game, Space* current_space, char turn, Space* possibilities[], int* count) {
    for (int i = 1; i < 8; i++) { // up-left
        if ((int)current_space->x - i < 0 || (int)current_space->y - i < 0) break;
        Space* space = GET_SPACE_BY_DISTANCE(-i, -i);
        if (space->piece != NULL) {
            if (space->piece->color != turn) {
                possibilities[(*count)++] = space;
            }
            break;
        }
        possibilities[(*count)++] = space;
    }
    for (int i = 1; i < 8; i++) { //up-right
        if (current_space->x + i > 7 || (int)current_space->y - i < 0) break;
        Space* space = GET_SPACE_BY_DISTANCE(-i, i);
        if (space->piece != NULL) {
            if (space->piece->color != turn) {
                possibilities[(*count)++] = space;
            }
            break;
        }
        possibilities[(*count)++] = space;
    }
    for (int i = 1; i < 8; i++) { // down-left
        if ((int)current_space->x - i < 0 || current_space->y + i > 7) break;
        Space* space = GET_SPACE_BY_DISTANCE(i, -i);
        if (space->piece != NULL) {
            if (space->piece->color != turn) {
                possibilities[(*count)++] = space;
            }
            break;
        }
        possibilities[(*count)++] = space;
    }
    for (int i = 1; i < 8; i++) { // down-right
        if (current_space->x + i > 7 || current_space->y + i > 7) break;
        Space* space = GET_SPACE_BY_DISTANCE(i, i);
        if (space->piece != NULL) {
            if (space->piece->color != turn) {
                possibilities[(*count)++] = space;
            }
            break;
        }
        possibilities[(*count)++] = space;
    }
}

char valid_bishop_move(Game* game, Space* current_space, Space* target_space) {
    int count = 0;
    Space* possibilities[BISHOP_MOVES];
    get_bishop_possibilities(game, current_space, game->turn, possibilities, &count);

    for (int i = 0; i < count; i++) {
        if (possibilities[i]->x == target_space->x && possibilities[i]->y == target_space->y) {
            return YES;
        }
    }

    printf("Invalid move for bishop\n");
    return NO;
}

Space* get_queen_possibilities(Game* game, Space* current_space, char turn, Space* possibilities[], int* count) {
    get_rook_possibilities(game, current_space, turn, possibilities, count);
    get_bishop_possibilities(game, current_space, turn, possibilities, count);

}

char valid_queen_move(Game* game, Space* current_space, Space* target_space) {
    int count = 0;
    Space* possibilities[QUEEN_MOVES];
    get_queen_possibilities(game, current_space, game->turn, possibilities, &count);

    for (int i = 0; i < count; i++) {
        if (possibilities[i]->x == target_space->x && possibilities[i]->y == target_space->y) {
            return YES;
        }
    }

    printf("Invalid move for queen\n");
    return NO;
}

Space* get_king_possibilities(Game* game, Space* current_space, char turn, Space* possibilities[], int* count) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            if (current_space->x + i < 0 || current_space->x + i > 7 || current_space->y + j < 0 || current_space->y + j > 7) continue;
            Space* space = GET_SPACE_BY_DISTANCE(j, i);
            if (space->piece != NULL) {
                if (space->piece->color != turn) {
                    possibilities[(*count)++] = space;
                }
                break;
            }
            possibilities[(*count)++] = space;
        }
    }

    if ((int)current_space->x - 3 >= 0 && GET_SPACE_BY_DISTANCE(0, -1)->piece == NULL && GET_SPACE_BY_DISTANCE(0, -2)->piece == NULL && GET_SPACE_BY_DISTANCE(0, -3)->piece != NULL && GET_SPACE_BY_DISTANCE(0, -3)->piece->type == ROOK && GET_SPACE_BY_DISTANCE(0, -3)->piece->color == turn && GET_SPACE_BY_DISTANCE(0, -3)->piece->moves == 0) {
        // castling left
        possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(0, -3); // this will switched to -2 in valid_king_move
    }
    if (GET_SPACE_BY_DISTANCE(0, 1)->piece == NULL && GET_SPACE_BY_DISTANCE(0, 2)->piece == NULL && GET_SPACE_BY_DISTANCE(0, 3)->piece != NULL && GET_SPACE_BY_DISTANCE(0, 3)->piece->type == ROOK && GET_SPACE_BY_DISTANCE(0, 3)->piece->color == turn && GET_SPACE_BY_DISTANCE(0, 3)->piece->moves == 0) {
        // castling right
        possibilities[(*count)++] = GET_SPACE_BY_DISTANCE(0, 3); // this will switched to 2 in valid_king_move
    }
}

char valid_king_move(Game* game, Space* current_space, Space* target_space) {
    int count = 0;
    Space* possibilities[KING_MOVES];
    get_king_possibilities(game, current_space, game->turn, possibilities, &count);

    for (int i = 0; i < count; i++) {
        if (possibilities[i]->x == target_space->x && possibilities[i]->y == target_space->y) {
            return YES;
        }
    }
    
    printf("Invalid move for king\n");
    return NO;
}

void get_player_spaces(Game* game, char turn, Space* spaces[], int* count) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game->board[i][j]->piece != NULL) {
                if (game->board[i][j]->piece->color == turn) {
                    spaces[(*count)++] = game->board[i][j];
                }
            }
        }
    }
}

void get_player_possibilities(Game* game, Space* spaces[], int spaces_count, char turn, Space* possibilities[], int* count) {
    for (int i = 0; i < spaces_count; i++) {
        switch (spaces[i]->piece->type) {
            case PAWN: get_pawn_possibilities(game, spaces[i], turn, possibilities, count); break;
            case ROOK: get_rook_possibilities(game, spaces[i], turn, possibilities, count); break; 
            case KNIGHT: get_knight_possibilities(game, spaces[i], turn, possibilities, count); break;
            case BISHOP: get_bishop_possibilities(game, spaces[i], turn, possibilities, count); break;
            case QUEEN: get_queen_possibilities(game, spaces[i], turn, possibilities, count); break;
            case KING: get_king_possibilities(game, spaces[i], turn, possibilities, count); break;
            default: break;
        }
    }
}

char is_in_check(Game* game) {
    Space* white_player_spaces[16];
    int white_player_count = 0;
    get_player_spaces(game, WHITE, white_player_spaces, &white_player_count);
    
    Space* black_player_spaces[16];
    int black_player_count = 0;
    get_player_spaces(game, BLACK, black_player_spaces, &black_player_count);
    
    Space* white_possibilities[TOTAL_MOVES];
    int white_move_count = 0;
    get_player_possibilities(game, white_player_spaces, white_player_count, WHITE, white_possibilities, &white_move_count);

    Space* black_possibilities[TOTAL_MOVES];
    int black_move_count = 0;
    get_player_possibilities(game, black_player_spaces, black_player_count, BLACK, black_possibilities, &black_move_count);

    int returns = 0;
    for (int i = 0; i < white_move_count; i++) {
        if (white_possibilities[i]->piece != NULL && white_possibilities[i]->piece->type == KING && white_possibilities[i]->piece->color == BLACK) {
            returns += 1;
        }
    }

    for (int i = 0; i < black_move_count; i++) {
        if (black_possibilities[i]->piece != NULL && black_possibilities[i]->piece->type == KING && black_possibilities[i]->piece->color == WHITE) {
            returns -= 2;
        }
    }

    if (returns == 1) return BLACK;
    else if (returns == -2) return WHITE;
    else if (returns == -1) return BOTH;

    return 0;
}

void promote_pawn(Game* game, Space* pawn_space) {
    printf("Pawn promotion! Choose a piece (Q, R, B, N): ");
    char choice;
    scanf(" %c", &choice);

    PieceType new_type;
    switch (choice) {
        case 'Q': new_type = QUEEN; break;
        case 'R': new_type = ROOK; break;
        case 'B': new_type = BISHOP; break;
        case 'N': new_type = KNIGHT; break;
        default:
            printf("Invalid choice, defaulting to Queen.\n");
            new_type = QUEEN;
            break;
    }

    pawn_space->piece->type = new_type;
}

char make_move(Game* game, char turn, Space* current_space, Space* target_space) {
    // copy incase the move is invalid
    Space copy_current_space = *current_space;
    Space copy_target_space = *target_space; 
    
    if (current_space->piece != NULL) {
        copy_current_space.piece = (Piece*)malloc(sizeof(Piece));
        if (copy_current_space.piece == NULL) {
            fprintf(stderr, "Memory allocation failed for copy_current_space.piece\n");
            exit(EXIT_FAILURE);
        }
        *(copy_current_space.piece) = *(current_space->piece);
    }

    if (target_space->piece != NULL) {
        copy_target_space.piece = (Piece*)malloc(sizeof(Piece));
        if (copy_target_space.piece == NULL) {
            fprintf(stderr, "Memory allocation failed for copy_target_space.piece\n");
            exit(EXIT_FAILURE);
        }
        *(copy_target_space.piece) = *(target_space->piece);
    }

    current_space->piece->moves++;
    if (target_space->piece != NULL && target_space->piece->type == ROOK && target_space->piece->color == turn && current_space->piece->type == KING) {
        if (target_space->x > current_space->x) {
            // castling right
            game->board[target_space->y][target_space->x - 2]->piece = target_space->piece;
            game->board[target_space->y][target_space->x - 1]->piece = game->board[current_space->y][current_space->x]->piece;
        } else {
            // castling left
            game->board[target_space->y][target_space->x + 2]->piece = target_space->piece;
            game->board[target_space->y][target_space->x + 1]->piece = game->board[current_space->y][current_space->x]->piece;
        }
        game->board[target_space->y][target_space->x]->piece = NULL;
    } else {
        game->board[target_space->y][target_space->x]->piece = game->board[current_space->y][current_space->x]->piece;
    }
    game->board[current_space->y][current_space->x]->piece = NULL;


    char in_check = is_in_check(game);
    if (in_check == turn || in_check == BOTH) {
        printf("You cannot move into check\n");
    
        // Revert the move
        *current_space = copy_current_space;
        *target_space = copy_target_space;
    
        free_space_copy(&copy_current_space);
        free_space_copy(&copy_target_space);
    
        return NO;
    } else {
        free_space_copy(&copy_current_space);
        free_space_copy(&copy_target_space);
    }

    // Check for pawn promotion
    if (target_space->piece != NULL && target_space->piece->type == PAWN) {
        if ((target_space->piece->color == WHITE && target_space->y == 0) ||
            (target_space->piece->color == BLACK && target_space->y == 7)) {
            promote_pawn(game, target_space);
        }
    }

    return YES;
}

// char turn_is_in_checkmate(Game* game, char turn) {
//     Space* player_spaces[16];
//     int player_count = 0;
//     get_player_spaces(game, turn, player_spaces, &player_count);

//     Space* possibilities[TOTAL_MOVES];
//     int move_count = 0;
//     get_player_possibilities(game, player_spaces, player_count, turn, possibilities, &move_count);

//     for (int i = 0; i < player_count; i++) {
//         Space* current_space = player_spaces[i];
//         for (int j = 0; j < move_count; j++) {
//             Space* target_space = possibilities[j];
//             if (make_move(game, turn, current_space, target_space) == YES) {
//                 // Undo the move
//                 make_move(game, turn, target_space, current_space);
//                 return NO; // Not in checkmate
//             }
//         }
//     }

//     return YES; // No valid moves, checkmate
// }

// char is_in_checkmate(Game* game) {
//     char black_checkmate = turn_is_in_checkmate(game, BLACK);
//     char white_checkmate = turn_is_in_checkmate(game, WHITE);
//     if (black_checkmate == YES && white_checkmate == YES) {
//         return STALEMATE;
//     } else if (black_checkmate == YES) {
//         return BLACK;
//     } else if (white_checkmate == YES) {
//         return WHITE;
//     } else {
//         return 0; // Not in checkmate
//     }
// }

char is_game_over(Game* game) {
    char kings = 0;
    char w_pieces = 0;
    char b_pieces = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game->board[i][j]->piece != NULL) {
                if (game->board[i][j]->piece->color == WHITE) {
                    if (game->board[i][j]->piece->type == KING) {
                        kings += 2;
                    }
                    w_pieces++;
                } else {
                    if (game->board[i][j]->piece->type == KING) {
                        kings -= 1;
                    }
                    b_pieces++;
                }
            }
        }
    }

    if (kings == 2) {
        return WHITE;
    } else if (kings == -1) {
        return BLACK;
    } 

    if (w_pieces == 1) {
        return BLACK;
    }
    if (b_pieces == 1) {
        return WHITE;
    }

    //char checkmate = is_in_checkmate(game);
    //if (checkmate) {
    //    return checkmate;
    //}

    // Check for stalemate
    char turn = game->turn;
    Space* player_spaces[16];
    int player_count = 0;
    get_player_spaces(game, turn, player_spaces, &player_count);

    Space* possibilities[TOTAL_MOVES];
    int move_count = 0;
    get_player_possibilities(game, player_spaces, player_count, turn, possibilities, &move_count);

    if (move_count == 0 && is_in_check(game) == 0) {
        return STALEMATE;
    }

    return 0;
}

char next_turn(Game* game) {
    if (game->turn == WHITE) {
        printf("White's turn, ");
        if (game->players1->control_type == COMPUTER) {
            printf("COMPUTER TURN NOT IMPLEMENTED YET\n");
        } else {
            printf("Enter your move (if in checkmate, type `lost`):\n");
        }
    } else {
        printf("Black's turn, ");
        if (game->players2->control_type == COMPUTER) {
            printf("COMPUTER TURN NOT IMPLEMENTED YET\n");
        } else {
            printf("Enter your move (if in checkmate, type `lost`):\n");
        }
    }
    char input[100];
    scanf("%s", input);

    if (input[0] == QUIT) {
        return QUIT; 
    }
    if (input[0] == SKIP) {
        printf("Skipping turn\n");
        return 0;
    }

    if (input[0] == 'l' && input[1] == 'o' && input[2] == 's' && input[3] == 't') {
        return game->turn == WHITE ? BLACK : WHITE;
    }

    char x1 = input[0] - 'A';
    char y1 = input[1] - '1';
    char x2 = input[2] - 'A';
    char y2 = input[3] - '1';

    // check if it's a valid piece
    if (game->board[y1][x1]->piece == NULL) {
        printf("No piece at %c%d\n", x1 + 'A', y1 + 1);
        return next_turn(game);
    } else if (game->board[y1][x1]->piece->color != game->turn) {
        printf("You cannot move your opponent's piece\n");
        return next_turn(game);
    } else if (x1 == x2 && y1 == y2) {
        printf("You cannot move to the same space\n");
        return next_turn(game);
    }
    
    // check if the move is valid
    Space* current_space = game->board[y1][x1];
    Space* target_space = game->board[y2][x2];
    switch (game->board[y1][x1]->piece->type) {
        case PAWN:
            if (valid_pawn_move(game, current_space, target_space) == NO) {
                return next_turn(game);
            }
            break;
        case ROOK:
            if (valid_rook_move(game, current_space, target_space) == NO) {
                return next_turn(game);
            }
            break;
        case KNIGHT:
            if (valid_knight_move(game, current_space, target_space) == NO) {
                return next_turn(game);
            }
            break;
        case BISHOP:
            if (valid_bishop_move(game, current_space, target_space) == NO) {
                return next_turn(game);
            }
            break;
        case QUEEN:
            if (valid_queen_move(game, current_space, target_space) == NO) {
                return next_turn(game);
            }
            break;
        case KING:
            if (valid_king_move(game, current_space, target_space) == NO) {
                return next_turn(game);
            }
            break;
        default:
            printf("Invalid piece type\n");
            return 0;
    }

    if (make_move(game, game->turn, current_space, target_space) == NO) {
        return next_turn(game);
    }
    
    if (is_in_check(game) == (game->turn == BLACK ? WHITE : BLACK)) {
        if (game->turn == WHITE) {
            printf("Black is in check!\n");
        } else {
            printf("White is in check!\n");
        }
    }
    
    return is_game_over(game);
}

int main() {
    Game* game = create_game(2);

    char won = 0;
    while (won == 0)
    {
        print_game(game);
        printf("\n");
        won = next_turn(game);
        game->turn = (game->turn == WHITE) ? BLACK : WHITE;
    }

    print_game(game);
    if (won == WHITE) {
        printf("White wins!\n");
    } else if (won == BLACK) {
        printf("Black wins!\n");
    } else if (won == STALEMATE) {
        printf("Stalemate!\n");
    } else if (won == QUIT) {
        printf("Quit!\n");
    } else {
        printf("Game over!\n");
    }

    free_game(game);
    return 0;
}