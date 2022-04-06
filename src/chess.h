#pragma once
#include "engine/olcPixelGameEngine.h"

#ifdef DEBUGCHESS
#define DEBUGVALUE printf;
#define DEBUG(x)                                                \
printf_s("\n\033[%dm[%d]" x "\033[0m\n",int((rand() % 6) + 1 + floor(float(((rand() % 2) + 1)*1.5)) * 30),int((rand() % 6) + 1 + floor(float(((rand() % 2) + 1)*1.5)) * 30));
#else
#define DEBUGVALUE(...)
#define DEBUG(x)
#endif

struct AIInfo {
    int depth;
    char option; // B - basic | D - default | S - smart | A - advanced
};

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
    AIInfo AI;
};

struct checkCheck{
    int pX;
    int pY;
};

class chessBotI {
public:
    std::vector<ChessPiece> piecesCreator(std::string pieceName);
    Turn loadPlayer(int player);
    void reloadPiece(ChessPiece &chessPiece, char mode);
};