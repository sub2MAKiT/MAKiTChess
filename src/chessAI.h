#pragma once
#include "chessCheck.h"

struct ChessBoardsForAI
{
    std::vector<ChessPiece> Board;
    int mX;
    int mY;
    int cDepth;
    int firstId;
    int pieceSelected;
};

struct SmartChessBoardsForAI
{
    ChessBoardsForAI CBFAI;
    int points;
};

struct AIMove {
    int mX;
    int mY;
    int pieceSelected;
};

class chessAI {
public:
    AIMove AIMOVE(Turn player, std::vector<ChessPiece> GameState,std::vector<int> mXQueue,std::vector<int> mYQueue,std::vector<int> PSQueue);
    std::vector<ChessBoardsForAI> moveAI(std::vector<ChessPiece> GameState, bool isWhite, int cDepth, int firstID);
    int pointCalculator(std::vector<ChessPiece> GameState, Turn player);
    AIMove movePicker(std::vector<ChessBoardsForAI> ALLMOVES, int Depth, Turn player,std::vector<int> mXQueue,std::vector<int> mYQueue,std::vector<int> PSQueue);
    int smartPointCalculator(std::vector<ChessPiece> GameState, bool player,std::vector<int> mXQueue,std::vector<int> mYQueue,std::vector<int> PSQueue,int mX, int mY, int pieceSelected);
    int reallySmartExclamationPoint(int value);
};