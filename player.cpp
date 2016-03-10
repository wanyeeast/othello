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
    this->testingMinimax = false;


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
int Player::minmaxScore(Board * board, Move * move, Side a, Side b)
{
    Board * temp = board->copy();
    temp->doMove(move, a);
    return temp->count(a) - temp->count(b);
}
int Player::score(int i, int j)
{
    if((i == 0 || i == 7) && (j == 0 || j == 7))
    {
        return 500;
    }
    else if((i == 0 && (j == 1 || j == 6)) || ((i == 1 && (j == 0 || j == 7))) || ((i == 6 && (j == 0 || j == 7))) || ((i == 7 && (j ==1 || j == 6))))
    {
        return -50;
    }
    else if(j == 0 || i == 0)
    {
        return 50;
    }
    else if((i == 1 || i == 6) && (j == 1 || j == 6))
    {
        return -500;
    }
    else
    {
        return 25;
    }
}


Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    if(testingMinimax == false)
    {
        if(opponentsMove != NULL)
        {
            this->curBoard->doMove(opponentsMove, this->oppside);
        }

        Move * max = new Move(0, 0);
        int maxScore = -500;
        if(curBoard->hasMoves(playerside))
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Move * move = new Move(i, j);
                    if (this->curBoard->checkMove(move, this->playerside))
                    {
                        if(this->score(i, j) > maxScore)
                        {
                            maxScore = this->score(i, j);
                            max = move;
                        }
                        
                    }
                }
            }

            this->curBoard->doMove(max, this->playerside);
            return max;
        }
        return NULL;
    }
    else
    {   
        if(opponentsMove != NULL)
        {
            this->curBoard->doMove(opponentsMove, this->oppside);
        }
        vector<Move*> PossibleMoves = vector<Move*>();
        if(curBoard->hasMoves(playerside))
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Move * move = new Move(i, j);
                    if (this->curBoard->checkMove(move, this->playerside))
                    {
                        PossibleMoves.push_back(move);
                        
                    }
                }
            }
            if(PossibleMoves.size() > 0)
            {
                int minmax = -500;
                Move * bestmove = new Move(0, 0);
                for(int i = 0; i < (int)PossibleMoves.size(); i++)
                { 
                    Board * testboard = this->curBoard->copy();
                    testboard->doMove(PossibleMoves[i], this->playerside);
                    int testoppscore = 0;
                    if(testboard->hasMoves(oppside))
                    {
                        vector<Move*> OtherPossibleMoves = vector<Move*>();
                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                Move * move = new Move(i, j);
                                if (testboard->checkMove(move, this->oppside))
                                {
                                    OtherPossibleMoves.push_back(move);
                                    
                                }
                            }
                        }
                        
                        for(int i = 0; i < (int)OtherPossibleMoves.size(); i++)
                        {
                            int oppscore = minmaxScore(testboard, OtherPossibleMoves[i], oppside, playerside);
                            if(oppscore > testoppscore)
                            {
                                testoppscore = oppscore;
                            }
                             
                        }
                       

                    }
                    if((-1) * testoppscore > minmax)
                    {

                       minmax = (-1) * testoppscore; 
                       bestmove = PossibleMoves[i];
                    }
                    
                }

                this->curBoard->doMove(bestmove, this->playerside);
                return bestmove;
            }
        }   
        return NULL;    
            



    }
}
