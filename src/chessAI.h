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

struct AIMove {
    int mX;
    int mY;
    int pieceSelected;
};

class chessAI {
public:
    AIMove AIMOVE(Turn player, std::vector<ChessPiece> GameState);
    std::vector<ChessBoardsForAI> moveAI(std::vector<ChessPiece> GameState, bool isWhite, int cDepth, int firstID);
    int pointCalculator(std::vector<ChessPiece> GameState, Turn player);
    AIMove movePicker(std::vector<ChessBoardsForAI> ALLMOVES, int Depth, Turn player);
};