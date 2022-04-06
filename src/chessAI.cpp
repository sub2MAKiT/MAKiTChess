#include "chessAI.h"

AIMove chessAI::AIMOVE(Turn player, std::vector<ChessPiece> GameState)
{
    AIMove FinalMove;
    chessCheck Check;
    std::vector<ChessBoardsForAI> ALLMOVES;
    ALLMOVES.push_back({GameState,0,0,0,0});

    // printf("STARTED THE AI\n");
    if(player.AI.option = 'B')
    {
        for(int i = 1; i <= player.AI.depth; i++)
        {
            for(int a = 0; a < ALLMOVES.size(); a++)
            {
                std::vector<ChessBoardsForAI> Temp = {};// I'm sorry
                if(ALLMOVES[a].cDepth == i-1)
                {
                    if(i % 2 != 0)
                        Temp = moveAI(ALLMOVES[a].Board,player.Player,i, ALLMOVES[a].firstId);
                    else
                        Temp = moveAI(ALLMOVES[a].Board,!player.Player,i, ALLMOVES[a].firstId);
                    ALLMOVES.insert(ALLMOVES.end(), Temp.begin(), Temp.end());
                }
            }
        }
    }

    
    // printf("SIMULATED THE BOARDS\n");

    FinalMove = movePicker(ALLMOVES,player.AI.depth,player);
    
    // printf("PICKED THE MOVE\n");
    return FinalMove;
}

AIMove chessAI::movePicker(std::vector<ChessBoardsForAI> ALLMOVES,int Depth, Turn player)
{
    AIMove move;
    std::vector<ChessBoardsForAI> lowestMoves = {};
    std::vector<int> points = {};

    for(int i = 0; i < ALLMOVES.size(); i++)
    {
        if(ALLMOVES[i].cDepth == Depth)
            lowestMoves.push_back(ALLMOVES[i]);
    }
    // printf("Pushed ALLMOVES: %d\n",ALLMOVES.size());
    // printf("Pushed lowestMoves: %d\n",lowestMoves.size());
    int winner = 0;
    for(int i = 0; i < lowestMoves.size();i++)
    {
        points.push_back(pointCalculator(lowestMoves[i].Board,player));
        // printf("points Calculated\n");
        if(i != 0)
            if(points[i] > points[winner])
            {
                // printf("winner Changed\n");
                winner = i;
            }
    }
    // printf("Chose The Winner\n");
    for(int i = 0; i < ALLMOVES.size();i++)
    {
        if(ALLMOVES[i].firstId == lowestMoves[winner].firstId)
        {
            move.mX = ALLMOVES[i].mX;
            move.mY = ALLMOVES[i].mY;
            move.pieceSelected = ALLMOVES[i].pieceSelected;
        }
    }
    // printf("Read the winner\n");
    return move;
}

std::vector<ChessBoardsForAI> chessAI::moveAI(std::vector<ChessPiece> GameStateOG, bool isWhite, int cDepth, int firstID)
{
    std::vector<ChessPiece> GameStateFirst = GameStateOG;
    std::vector<ChessBoardsForAI> Chess4d = {};
    chessCheck ChessC;
    bool Castle;
    int CastleInt;
    int castleRX;
    int castleKX;
    std::vector<ChessPiece> GameState = GameStateOG;
    for(int i = 0; i < 8; i++)
    {
        for(int a = 0; a < 8; a++)
        {
            for(int b = 0; b < GameState.size(); b++)
            {
                int moveID;
                GameState = GameStateOG;
                Castle = false;
                CastleInt = 0;
                if(ChessC.moveSim(GameState, isWhite, i, a, b, true, Castle, CastleInt))
                {
                    if(cDepth == 1)
                    {
                        moveID = i * 8 * GameState.size() + a * GameState.size() + b;
                    } else {
                        moveID = firstID;
                    }
                    if(Castle)
                    {
                        castleRX = GameState[CastleInt].PositionX;
                        castleKX = GameState[b].PositionX;
                        GameState[b].PositionX = ((castleRX / 7) * 4) + 2;
                        GameState[CastleInt].PositionX = GameState[b].PositionX + (abs(4 - GameState[b].PositionX)/(4 - GameState[b].PositionX));
                        GameState[b].Moved = true;
                        GameState[CastleInt].Moved = true;
                    } else {
                        GameState[b].PositionX = i;
                        GameState[a].PositionY = a;
                    }
                    for(int d = 0; d < GameState.size(); d++)
                    {
                        if(d != b)
                            if(GameState[b].PositionX == GameState[d].PositionX && GameState[b].PositionY == GameState[d].PositionY)// this should be on the next line, but it didn't work, soo "if(GameState[b].Colour != GameState[d].Colour)"
                                    if(GameState[b].Colour == 'B')
                                    {
                                        if(!isWhite)
                                        {
                                            GameState.erase(GameState.begin()+d);
                                        }
                                    } else {
                                        if(isWhite)
                                            GameState.erase(GameState.begin()+d);
                                    }
                    }
                    // printf("%d. X:%d Y:%d Piece: %d Pieces: %d\n",Chess4d.size(),i,a,b,GameState.size());
                    Chess4d.push_back({GameState, i, a, cDepth, moveID,b});
                }
            }
        }
    }

    return Chess4d;
}

int chessAI::pointCalculator(std::vector<ChessPiece> GameState, Turn player)
{
    char Colour;
    if(player.Player)
        Colour = 'W';
    else
        Colour = 'B';
    int points = 100;
    for(int i = 0; i < GameState.size(); i++)
    {
        if(GameState[i].Colour == Colour)
        {
            if(GameState[i].Piece == 'P')
                points++;
            else if(GameState[i].Piece == 'R')
                points += 5;
            else if(GameState[i].Piece == 'B' || GameState[i].Piece == 'C')
                points += 3;
            else if(GameState[i].Piece == 'Q')
                points += 8;
            else
                points += 1;
        }
        if(GameState[i].Colour != Colour)
        {
            if(GameState[i].Piece == 'P')
                points--;
            else if(GameState[i].Piece == 'R')
                points -= 5;
            else if(GameState[i].Piece == 'B' || GameState[i].Piece == 'C')
                points -= 3;
            else if(GameState[i].Piece == 'Q')
                points -= 8;
            else
                points -= 1;
        }
    }
    // printf("\npoints: %d",points);
    return points;
}