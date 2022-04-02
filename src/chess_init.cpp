#include "chess.h"

std::vector<ChessPiece> ChessBotI::piecesCreator(std::string pieceName)
{
    std::vector<ChessPiece> FinalPiece;
    for(int i = 0; i < 8; i += 1)
    {
        FinalPiece.push_back({'B','P',i,1, nullptr, nullptr, false, false});
    }
    for(int i = 0; i < 8; i += 1)
    {
        FinalPiece.push_back({'W','P',i,6, nullptr, nullptr, false, false});
    }
    FinalPiece.push_back({'B','R',0,0, nullptr, nullptr, false, false});
    FinalPiece.push_back({'B','R',7,0, nullptr, nullptr, false, false});
    FinalPiece.push_back({'W','R',0,7, nullptr, nullptr, false, false});
    FinalPiece.push_back({'W','R',7,7, nullptr, nullptr, false, false});

    FinalPiece.push_back({'B','C',1,0, nullptr, nullptr, false, false});
    FinalPiece.push_back({'B','C',6,0, nullptr, nullptr, false, false});
    FinalPiece.push_back({'W','C',1,7, nullptr, nullptr, false, false});
    FinalPiece.push_back({'W','C',6,7, nullptr, nullptr, false, false});

    FinalPiece.push_back({'B','B',2,0, nullptr, nullptr, false, false});
    FinalPiece.push_back({'B','B',5,0, nullptr, nullptr, false, false});
    FinalPiece.push_back({'W','B',2,7, nullptr, nullptr, false, false});
    FinalPiece.push_back({'W','B',5,7, nullptr, nullptr, false, false});

    FinalPiece.push_back({'B','K',4,0, nullptr, nullptr, false, false});
    FinalPiece.push_back({'B','Q',3,0, nullptr, nullptr, false, false});
    FinalPiece.push_back({'W','K',4,7, nullptr, nullptr, false, false});
    FinalPiece.push_back({'W','Q',3,7, nullptr, nullptr, false, false});
    for(int i = 0; i < FinalPiece.size(); i++)
    {
        std::string Temp = "./src/textures/";
        Temp.append(pieceName);
        Temp.append("/");
        Temp.push_back(FinalPiece[i].Colour);
        Temp.append("/");
        Temp.push_back(FinalPiece[i].Piece);
        Temp.append(".png");
        FinalPiece[i].sprPPieces = new olc::Sprite(Temp);
        FinalPiece[i].decPPieces = new olc::Decal(FinalPiece[i].sprPPieces);
    }
    return FinalPiece;
}

Turn ChessBotI::loadPlayer(int player)
{
    Turn Temp = {};
    if(player == 0)
    {
        Temp.Player = true;
        Temp.RealPlayer = true;
    }
        if(player == 1)
    {
        Temp.Player = false;
        Temp.RealPlayer = true;
    }
    return Temp;
}

void ChessBotI::reloadPiece(ChessPiece &chessPiece)
{
    std::string Temp = "./src/textures/";
    Temp.push_back(chessPiece.Colour);
    Temp.append("/");
    Temp.push_back(chessPiece.Piece);
    Temp.append(".png");
    chessPiece.sprPPieces = new olc::Sprite(Temp);
    chessPiece.decPPieces = new olc::Decal(chessPiece.sprPPieces);
}