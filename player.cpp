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

int Player::ScoreofBoard(Board * board)
{
	int scoretemp; 
	for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
        	if(board->get(playerside, i, j))
        	{
        		scoretemp += score(board, i, j);
        	}
        	else if(board->get(oppside, i, j))
        	{
        		scoretemp -= score(board, i, j);
        	}
        }
    }
    return scoretemp;
}


int Player::minmaxScore(Board * board, Move * move, Side a, Side b)
{
    Board * temp = board->copy();
    temp->doMove(move, a);
    return temp->count(a) - temp->count(b);
}
int Player::score(Board* board, int i, int j)
{
    if((i == 0 || i == 7) && (j == 0 || j == 7))
    {
        return 5000;
    }
    else if((i == 0 && (j == 1 || j == 6)) || ((i == 1 && (j == 0 || j == 7))) || ((i == 6 && (j == 0 || j == 7))) || ((i == 7 && (j ==1 || j == 6))))
    {
    	if (board->get(playerside, 0, 0))
    	{
    		if((i == 0 && j == 1) || (i == 1 && j == 0))
    		{
    			return 5000;
    		}
    	}
    	else if (board->get(oppside, 0, 0))
    	{
    		if((i == 0 && j == 1) || (i == 1 && j == 0))
    		{
    			return -5000;
    		}
    	}
    	if (board->get(playerside, 7, 7))
    	{
    		if((i == 6 && j == 7) || (i == 7 && j == 6))
    		{
    			return 5000;
    		}
    	}
    	else if (board->get(oppside, 7, 7))
    	{
    		if((i == 6 && j == 7) || (i == 7 && j == 6))
    		{
    			return -5000;
    		}
    	}
    	if (board->get(playerside, 0, 7))
    	{
    		if((i == 0 && j == 6) || (i == 1 && j == 7))
    		{
    			return 5000;
    		}
    	}
    	else if (board->get(oppside, 0, 7))
    	{
    		if((i == 0 && j == 6) || (i == 1 && j == 7))
    		{
    			return -5000;
    		}
    	}
    	if (board->get(playerside, 7, 0))
    	{
    		if((i == 7 && j == 1) || (i == 6 && j == 0))
    		{
    			return 5000;
    		}
    	}
    	else if (board->get(oppside, 7, 0))
    	{
    		if((i == 7 && j == 1) || (i == 6 && j == 0))
    		{
    			return -5000;
    		}
    	}
        return -25;
    }
    else if(j == 0 || i == 0)
    {
        return 100;
    }
    else if((i == 1 || i == 6) && (j == 1 || j == 6))
    {
    	if (board->get(playerside, 0, 0))
    	{
    		if((i == 0 && j == 1) || (i == 1 && j == 0))
    		{
    			return 200;
    		}
    	}
    	else if (board->get(oppside, 0, 0))
    	{
    		if((i == 0 && j == 1) || (i == 1 && j == 0))
    		{
    			return -200;
    		}
    	}
    	if (board->get(playerside, 7, 7))
    	{
    		if((i == 6 && j == 7) || (i == 7 && j == 6))
    		{
    			return 200;
    		}
    	}
    	else if (board->get(oppside, 7, 7))
    	{
    		if((i == 6 && j == 7) || (i == 7 && j == 6))
    		{
    			return -200;
    		}
    	}
    	if (board->get(playerside, 0, 7))
    	{
    		if((i == 0 && j == 6) || (i == 1 && j == 7))
    		{
    			return 200;
    		}
    	}
    	else if (board->get(oppside, 0, 7))
    	{
    		if((i == 0 && j == 6) || (i == 1 && j == 7))
    		{
    			return -200;
    		}
    	}
    	if (board->get(playerside, 7, 0))
    	{
    		if((i == 7 && j == 1) || (i == 6 && j == 0))
    		{
    			return 200;
    		}
    	}
    	else if (board->get(oppside, 7, 0))
    	{
    		if((i == 7 && j == 1) || (i == 6 && j == 0))
    		{
    			return -200;
    		}
    	}
        return -50;
    }
    else
    {
        return 10;
    }
}


int Player::minimax2(Board* board, Side player, int depth, int alpha, int beta)
{
	Side opp2;
	if(player == playerside)
	{
		opp2 = oppside;
	}
	else
	{
		opp2 = playerside;
	}

	if(!board->hasMoves(player) || depth == 0)
	{
        return ScoreofBoard(board);
	}
	vector<Move*> PossibleMoves = vector<Move*>();
	int alpha2 = alpha;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move * move = new Move(i, j);
            if (board->checkMove(move, this->oppside))
            {
                PossibleMoves.push_back(move);
                
            }
            // delete move;
        }
    }
    for(int i = 0; i < (int)PossibleMoves.size(); i++)
    {   
    	Board * testboard3 = board->copy();
    	testboard3->doMove(PossibleMoves[i], player);
    	int score;
        if(i != 0)
        {
        	score = -minimax2(testboard3, opp2, depth - 1, -alpha2 - 1, -alpha);
        	if(alpha < score && score < beta)
        	{
        		score = -minimax2(testboard3, opp2, depth - 1, -beta, -score);
        	}
        }
        else
        {
        	score = -minimax2(testboard3, opp2, depth - 1, -beta, -alpha2);
        }
        // delete testboard3;
        alpha2 = max(alpha2, score);
        // delete PossibleMoves[i];
        if(alpha2 >= beta)
        {
        	break;
        }

    }

    return alpha2;
}








Move *Player::BestMoveToDo(Move * PossibleMove, Board * boardTemp)
{
    Board * testboard1 = boardTemp->copy();
    vector<Move*> PossibleMoves = vector<Move*>();
    if(testboard1->hasMoves(playerside))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Move * move = new Move(i, j);
                if (testboard1->checkMove(move, this->playerside))
                {
                    PossibleMoves.push_back(move);
                    
                }
            }
        }
        int minmax = -50000000;
        Move * bestmove = new Move(0, 0);
        for(int i = 0; i < (int)PossibleMoves.size(); i++)
        {   
        	Board * testboard4 = testboard1->copy();
        	testboard4->doMove(PossibleMoves[i], playerside);
            int score = minimax2(testboard4, playerside, 4, -50000, 50000);
            delete testboard4;
            if(score > minmax)
            {               
                bestmove = PossibleMoves[i];
                minmax = max(minmax, score);
            }
        }
        return bestmove;
        
    }   
    return NULL;    
}



Move* Player::BeatsSimplePlayer(Board * board, Move *opponentsMove)
{
    Move * max = new Move(0, 0);
    int maxScore = -500;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move * move = new Move(i, j);
            if (this->curBoard->checkMove(move, this->playerside))
            {
                if(this->score(board, i, j) > maxScore)
                {
                    maxScore = this->score(board, i, j);
                    max = move;
                }
                
            }
            // delete move;
        }
    }
    return max;
}



Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    if(opponentsMove != NULL)
        {
            this->curBoard->doMove(opponentsMove, this->oppside);
        }
    if(testingMinimax == true)
    {        
        if(curBoard->hasMoves(playerside))
        {
            Move * max = BeatsSimplePlayer(curBoard, opponentsMove);
            this->curBoard->doMove(max, this->playerside);
            return max;
        }
        return NULL;
    }
    else
    {   

        if(curBoard->hasMoves(playerside))
        {
            Move * max = BestMoveToDo(opponentsMove, this->curBoard);
            this->curBoard->doMove(max, this->playerside);
            return max;
        }
        return NULL;

    }
}
