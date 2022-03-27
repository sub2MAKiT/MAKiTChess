#include "engine/olcPixelGameEngine.h"
#include <vector>

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

class ChessBotH {
public:
    std::vector<ChessPiece> piecesCreator();
    Turn loadPlayer(int player);
};