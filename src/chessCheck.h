#include "chess.h"
class ChessCheck {
public:
    bool moveSim(std::vector<ChessPiece> GameState, bool playerTurn, Turn player1, Turn player2, int mX, int mY, int pieceSelected, bool saverFromLoop, bool &Castle, int &castleRook);
    bool CheckCheck(std::vector<ChessPiece> GameState, bool playerTurn, Turn player1, Turn player2, int kPX, int kPY, bool Castle, int castleRook);
};