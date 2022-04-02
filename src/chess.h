#pragma once
#include "engine/olcPixelGameEngine.h"
#include <vector>

#ifdef DEBUGCHESS
#define DEBUGVALUE printf;
#define DEBUG(x)                                                \
printf_s("\n\033[%dm[%d]" x "\033[0m\n",int((rand() % 6) + 1 + floor(float(((rand() % 2) + 1)*1.5)) * 30),int((rand() % 6) + 1 + floor(float(((rand() % 2) + 1)*1.5)) * 30));
#else
#define DEBUGVALUE(...)
#define DEBUG(x)
#endif

struct ChessPiece {
    char Colour;
    char Piece;
    int PositionX;
    int PositionY;
    olc::Sprite* sprPPieces;
    olc::Decal* decPPieces;
    bool Pressed;
    bool Moved;
};

struct Turn {
    bool Player;
    bool RealPlayer;
};

struct checkCheck{
    int pX;
    int pY;
};

class ChessBotI {
public:
    std::vector<ChessPiece> piecesCreator(std::string pieceName);
    Turn loadPlayer(int player);
    void reloadPiece(ChessPiece &chessPiece);
};