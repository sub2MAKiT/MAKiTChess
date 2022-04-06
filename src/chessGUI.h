#include "chessAI.h"

class chessGUI {
public:
    bool buttonDrawer(olc::vf2d mouse, std::string name, olc::vf2d position, olc::Decal *decButton, bool backgroundColourBool);
    bool menuDrawer(bool &textureChanging, bool &AIChanging, olc::vf2d mouse, bool &backgroundColourBool, olc::vf2d &piecesScale, Turn &Player1, Turn &Player2, char &piecesMode, std::vector<ChessPiece> Pieces, bool &tempPlayerRealAI, char &tempTypeAI, int &tempDepthAI, olc::Decal *decButton);
};