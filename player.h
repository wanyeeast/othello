#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Board * curBoard;
    Side playerside;
    Side oppside;

    int score(Board * board, int i, int j);
   	int minmaxScore(Board * board, Move * move, Side a, Side b);
    int ScoreofBoard(Board * board);
    Move *doMove(Move *opponentsMove, int msLeft);
    Move* BeatsSimplePlayer(Board * board, Move *opponentsMove);
    int minimax(Move* PossibleMove, int depth, Side player, Board * testB, int alpha, int beta);
    int minimax2(Board* board, Side player, int depth, int alpha, int beta);
    Move *BestMoveToDo(Move * PossibleMove, Board * boardTemp);
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
