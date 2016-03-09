#include "player.h"
#include <stdlib.h>
#include <vector>
/* Test by Wayne */
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;


    this->curBoard = new Board();
    this->playerside = side;
    if(side == WHITE)
    {
        this->oppside = BLACK;
    }
    else
    {
        this->oppside = WHITE;
    }

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    std::cerr << "msLeft: " << msLeft << std::endl;
    if(opponentsMove != NULL)
    {
        cerr << "oppside: " << oppside << endl;
        cerr << "opp move: " << (int)opponentsMove << endl;
        this->curBoard->doMove(opponentsMove, this->oppside);
    }
    else
    {
        std::cerr << "opponent didn't have a move" << std::endl;
    }
    // vector<pair> Move
    // std::pair <std::string,double> product1; 
    vector<Move> PossibleMoves = vector<Move>();
    if(curBoard->hasMoves(playerside))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Move move(i, j);
                if (this->curBoard->checkMove(&move, this->playerside))
                {
                    PossibleMoves.push_back(move);
                }
            }
        }
    }

    std::cerr << "possible moves: " << PossibleMoves.size() << std::endl;
    if(PossibleMoves.size() > 0)
    {
        int random = rand() % PossibleMoves.size();
        for(int i = 0; i < (int)PossibleMoves.size(); i++)
        {
            std::cerr << " " << (int)&PossibleMoves[i];
        }
        std::cerr << std::endl;

        // std::cerr << "msLeft: " << msLeft << std::endl;
        // Move * temp =  &PossibleMoves[random];
        // std::cerr << "Move Taken: " << (int)temp << std::endl;
        this->curBoard->doMove(&PossibleMoves[random], this->playerside);
        return &PossibleMoves[random];
    }
    std::cerr << "reach" << std::endl;
    return NULL;
}
