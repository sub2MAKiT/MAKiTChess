#define OLC_PGE_APPLICATION
#include "chessCheck.h"

class ChessBot : public olc::PixelGameEngine
{
public:
	ChessBot()
	{
		sAppName = "ChessBot";
	}

    olc::Sprite* sprBoard = nullptr;
    olc::Decal* decBoard = nullptr;
    std::vector<ChessPiece> Pieces = {};
    Turn Player1 = {};
    Turn Player2 = {};
    bool playerTurn = true;
    bool selected;
    int pieceSelected;
    int castleRook;
    bool Castle;
    ChessCheck chessC;

public:
	bool OnUserCreate() override
	{
        ChessBotI chess;
        sprBoard = new olc::Sprite("./src/textures/board2.png");
        decBoard = new olc::Decal(sprBoard);
        Pieces = chess.piecesCreator();
        Player1 = chess.loadPlayer(0);
        Player2 = chess.loadPlayer(1);
        selected =  false;
        
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        Clear(olc::BLACK);
        olc::vf2d mouse = {float(GetMouseX()), float(GetMouseY())};
        SetPixelMode(olc::Pixel::ALPHA);
        DrawDecal({0.0f, 0.0f},decBoard, {4.0f, 4.0f});
        for(int i = 0; i < Pieces.size(); i++)
        {

            DrawDecal({float(Pieces[i].PositionX * 32), float(Pieces[i].PositionY * 32)},Pieces[i].decPPieces, {4.0f, 4.0f}, {255,floor(1 /(Pieces[i].Pressed + 1)) * 255,floor(1 /(Pieces[i].Pressed + 1)) * 255});
        }
        SetPixelMode(olc::Pixel::NORMAL);
        gameLoop(Pieces, playerTurn, Player1, Player2, mouse);
		return true;
	}

    void gameLoop(std::vector<ChessPiece> &GameState, bool &playerTurn, Turn player1, Turn player2, olc::vf2d mouse)
    {
        Castle = false;
        int mX = floor(mouse.x / 32);
        int mY = floor(mouse.y / 32);
        char correctColour;
        bool correctTurn;
        bool moveCorrect = false;
        bool move1 = false;
        bool move2 = false;
        bool move3 = false; 
        bool moveDone = false;
        bool moved = false;
        int castleRX;
        int castleKX;
        if(player1.Player == playerTurn)
        {
            correctTurn = true;
            correctColour = 'W';
        } else {
            correctTurn = false;
            correctColour = 'B';
        }
        if(!selected)
        {
            if(GetMouse(0).bPressed)
            {
                for(int i = 0; i < GameState.size(); i++)
                {
                    if((mX == GameState[i].PositionX && mY == GameState[i].PositionY) && GameState[i].Colour == correctColour)
                    {
                        GameState[i].Pressed = true;
                        DEBUGVALUE("%d", selected);
                        selected = true;
                        pieceSelected = i;
                        DEBUGVALUE("%d", selected);
                    }
                }
            }
        } else {
            if(GetMouse(0).bPressed)
            {
                DEBUGVALUE("?");
                moveCorrect = chessC.moveSim(GameState, playerTurn, player1, player2, mX, mY, pieceSelected, true, Castle, selected, castleRook);
                moved = true;
            }
            if(moved)
            {
                DEBUGVALUE("\nmoved, %d\n",moveCorrect);
                if(moveCorrect)
                {
                    if(!Castle)
                    {
                        GameState[pieceSelected].PositionX = mX;
                        GameState[pieceSelected].PositionY = mY;
                        GameState[pieceSelected].Moved = true;
                    } else {
                        castleRX = GameState[castleRook].PositionX;
                        castleKX = GameState[pieceSelected].PositionX;
                        GameState[pieceSelected].PositionX = ((castleRX / 7) * 4) + 2;
                        GameState[castleRook].PositionX = GameState[pieceSelected].PositionX + (abs(4 - GameState[pieceSelected].PositionX)/(4 - GameState[pieceSelected].PositionX));
                        GameState[pieceSelected].Moved = true;
                        GameState[castleRook].Moved = true;
                    }
                    GameState[pieceSelected].Pressed = false;
                    DEBUGVALUE("\nMoved to %d",GameState[pieceSelected].PositionX);
                    DEBUGVALUE("\nMoved to %d\n",GameState[pieceSelected].PositionY);
                    selected = false;
                    if(playerTurn)
                    {
                        playerTurn = false;
                    } else {
                        playerTurn = true;
                    }
                    for(int i = 0; i < GameState.size(); i++)
                    {
                        for(int a = 0; a < GameState.size(); a++)
                        {
                            if(a != i)
                            {
                                if(GameState[i].PositionX == GameState[a].PositionX)
                                {
                                    if(GameState[i].PositionY == GameState[a].PositionY)
                                    {
                                        if(GameState[i].Colour != GameState[a].Colour)
                                        {
                                            if(GameState[i].Colour == 'B')
                                            {
                                                if(!correctTurn)
                                                {
                                                    GameState.erase(GameState.begin()+a);
                                                } else {
                                                    GameState.erase(GameState.begin()+i);
                                                }
                                            } else {
                                                if(correctTurn)
                                                {
                                                    GameState.erase(GameState.begin()+a);
                                                } else {
                                                    GameState.erase(GameState.begin()+i);
                                                }
                                            }
                                        } else {
                                            if(Castle)
                                            {
                                                if(playerTurn)
                                                {
                                                    playerTurn = false;
                                                } else {
                                                    playerTurn = true;
                                                }
                                                GameState[castleRook].PositionX = castleRX;
                                                GameState[pieceSelected].PositionX = castleKX;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    GameState[pieceSelected].Pressed = false;
                    selected = false;
                }
            }
        }
    }
ChessPiece pawnSwapper(std::vector<ChessPiece> GameState, int pieceSelected)
{
    
}
};

int main()
{
	ChessBot demo;
	if (demo.Construct(256, 256, 4, 4))
		demo.Start();

	return 0;
}