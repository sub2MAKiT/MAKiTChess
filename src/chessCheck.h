#pragma once
#include "chess.h"

class chessCheck {
public:
    bool moveSim(std::vector<ChessPiece> GameState, bool playerTurn, int mX, int mY, int pieceSelected, bool saverFromLoop, bool &Castle, int &castleRook);
    bool CheckCheck(std::vector<ChessPiece> GameState, bool playerTurn, int kPX, int kPY, bool Castle, int castleRook);
};