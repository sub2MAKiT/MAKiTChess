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
    olc::Sprite* sprPS = nullptr;
    olc::Decal* decPS = nullptr;

    olc::Sprite* sprQ = nullptr;
    olc::Decal* decQ = nullptr;
    olc::Sprite* sprB = nullptr;
    olc::Decal* decB = nullptr;
    olc::Sprite* sprR = nullptr;
    olc::Decal* decR = nullptr;
    olc::Sprite* sprC = nullptr;
    olc::Decal* decC = nullptr;

    std::vector<ChessPiece> Pieces = {};
    Turn Player1 = {};
    Turn Player2 = {};
    bool playerTurn = true;
    bool selected = false;
    int pieceSelected;
    int castleRook;
    bool Castle;
    ChessCheck chessC;
    ChessBotI chessInitiaing;
    int gameEnding = 0;
    bool itIsTimeToMoveForWhite;

public:
	bool OnUserCreate() override
	{
        sprBoard = new olc::Sprite("./src/textures/board2.png");
        decBoard = new olc::Decal(sprBoard);
        sprPS = new olc::Sprite("./src/textures/PS.png");
        decPS = new olc::Decal(sprPS);

        sprB = new olc::Sprite("./src/textures/B/B.png");
        decB = new olc::Decal(sprB);
        sprC = new olc::Sprite("./src/textures/B/C.png");
        decC = new olc::Decal(sprC);
        sprQ = new olc::Sprite("./src/textures/B/Q.png");
        decQ = new olc::Decal(sprQ);
        sprR = new olc::Sprite("./src/textures/B/R.png");
        decR = new olc::Decal(sprR);

        Pieces = chessInitiaing.piecesCreator();
        Player1 = chessInitiaing.loadPlayer(0);
        Player2 = chessInitiaing.loadPlayer(1);
        DEBUG("User Created\n");
        
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
        if(gameEnding == 0)
        {
            DEBUG("\nGameloop");
            gameLoop(Pieces, playerTurn, Player1, Player2, mouse);
        }
        else if(gameEnding == 1)
        {
            printf("{GAME ENDED} - Draw\n");
            Clear(olc::WHITE);
            DrawString({100,128},"DRAW");
        } else if(gameEnding == 2)
        {
            printf("{GAME ENDED} - Won\n");
            DrawString({100,128},itIsTimeToMoveForWhite ? "White Wins":"Black Wins");
            Clear(olc::WHITE);
        }
        SetPixelMode(olc::Pixel::NORMAL);
		return true;
	}

    void gameLoop(std::vector<ChessPiece> &GameState, bool &playerTurn, Turn player1, Turn player2, olc::vf2d mouse)
    {
        Castle = false;
        int mX = floor(mouse.x / 32);
        int mY = floor(mouse.y / 32);
        char correctColour;
        bool WhiteCanMove;
        bool moveCorrect = false;
        bool move1 = false;
        bool move2 = false;
        bool move3 = false; 
        bool moveDone = false;
        bool moved = false;
        int castleRX;
        int castleKX;
        int pawnToChange;
        bool pawnCanChange = false;
        WhiteCanMove = playerTurn;
        bool BlackCanMove = !playerTurn;
        bool isDraw = true;
        for(int i = 0; i < GameState.size(); i++)
        {
                if(GameState[i].Piece == 'P' && (GameState[i].PositionY == 0 || GameState[i].PositionY == 7))
                {
                    pawnCanChange = true;
                    pawnToChange = i;
                }
        }
        if(player1.Player == playerTurn)
        {
            correctColour = 'W';
        } else {
            correctColour = 'B';
        }
        if(pawnCanChange)
        {
            pawnSwapper(GameState,pawnToChange, mX);
        }
        if(!selected && !pawnCanChange)
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
        } else if(selected) {
            if(GetMouse(0).bPressed)
            {
                DEBUGVALUE("?");
                if(!pawnCanChange)
                    moveCorrect = chessC.moveSim(GameState, playerTurn, player1, player2, mX, mY, pieceSelected, true, Castle, castleRook);
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
                    DEBUG("After castle");
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
                                                if(!WhiteCanMove)
                                                {
                                                    GameState.erase(GameState.begin()+a);
                                                } else {
                                                    GameState.erase(GameState.begin()+i);
                                                }
                                            } else {
                                                if(WhiteCanMove)
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
                DEBUG("Finished Gameloop");
            }
            int kingPos;
            for(int i = 0; i < GameState.size();i++)
            {
                if(playerTurn)
                {
                    if(GameState[i].Piece == 'K' && GameState[i].Colour == 'W')
                        kingPos = i;
                } else {
                    if(GameState[i].Piece == 'K' && GameState[i].Colour == 'B')
                        kingPos = i;
                }
            }
            bool Garbage = false;
            bool isNotChecked = true;
            if(!chessC.CheckCheck(GameState, BlackCanMove, player1, player2, GameState[kingPos].PositionX, GameState[kingPos].PositionY, Castle, castleRook))
                isNotChecked = false;
            DEBUG("Before end game check\n");

            for(int i = 0; i < GameState.size(); i++)
            {
                for(int a = 0;a < 8; a++)
                {
                    for(int b = 0;b < 8; b++)
                    {
                        if(chessC.moveSim(GameState, playerTurn, player1, player2, a, b, i, true, Garbage, castleRook))
                            isDraw = false;
                    }
                }
            }

            // ______OPTIONAL CODE... not working, no idea why.
            // for(int i = 0;i < GameState.size(); i++)
            // {
            //     if((GameState[i].Colour == 'W' && WhiteCanMove) || (GameState[i].Colour == 'B' && !WhiteCanMove))
            //     {
            //         printf("\nall good");
            //         if(GameState[i].Piece == 'P')
            //         {
            //             printf("\na pawn");
            //                 chessC.moveSim(GameState, playerTurn, player1, player2, mX,                     mY,                                                    pieceSelected, true, Castle, castleRook);
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX, GameState[i].PositionY - ((WhiteCanMove + 1) * 2 - 3), i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX, GameState[i].PositionY - (((WhiteCanMove + 1) * 2 - 3) * 2), i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + 1, GameState[i].PositionY - ((WhiteCanMove + 1) * 2 - 3), i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - 1, GameState[i].PositionY - ((WhiteCanMove + 1) * 2 - 3), i, true, Garbage, castleRook))
            //                 isDraw = false;
            //         }
            //         if(GameState[i].Piece == 'R')
            //         {
            //             for(int a = 0; a < 8; a++)
            //             {
            //             printf("\nrook loop");
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX, a, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, a, GameState[i].PositionY, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             }
            //         }
            //         if(GameState[i].Piece == 'C')
            //         {
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - 1, GameState[i].PositionY + 2, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + 1, GameState[i].PositionY + 2, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - 1, GameState[i].PositionY - 2, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + 1, GameState[i].PositionY - 2, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - 2, GameState[i].PositionY - 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + 2, GameState[i].PositionY - 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - 2, GameState[i].PositionY + 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + 2, GameState[i].PositionY + 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //         }
            //         if(GameState[i].Piece == 'B')
            //         {
            //             for(int a = 0; a < 8; a++)
            //             {
            //                 if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - a, GameState[i].PositionY - a, i, true, Garbage, castleRook))
            //                     isDraw = false;
            //                 if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + a, GameState[i].PositionY - a, i, true, Garbage, castleRook))
            //                     isDraw = false;
            //                 if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - a, GameState[i].PositionY + a, i, true, Garbage, castleRook))
            //                     isDraw = false;
            //                 if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + a, GameState[i].PositionY + a, i, true, Garbage, castleRook))
            //                     isDraw = false;

            //             }
            //         }
            //         if(GameState[i].Piece == 'Q')
            //         {
            //             for(int a = 0; a < 8; a++)
            //             {
            //                 for(int b = 0; b < 8; b++)
            //                 {
            //                     if(!chessC.moveSim(GameState, playerTurn, player1, player2, a, b, i, true, Garbage, castleRook))
            //                         isDraw = false;
            //                 }
            //             }
            //         }
            //         if(GameState[i].Piece == 'K')
            //         {
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - 1, GameState[i].PositionY - 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - 1, GameState[i].PositionY, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX - 1, GameState[i].PositionY + 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX , GameState[i].PositionY - 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX, GameState[i].PositionY + 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + 1, GameState[i].PositionY - 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + 1, GameState[i].PositionY, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //             if(!chessC.moveSim(GameState, playerTurn, player1, player2, GameState[i].PositionX + 1, GameState[i].PositionY + 1, i, true, Garbage, castleRook))
            //                 isDraw = false;
            //         }
            //         Garbage = false;
            //     }
            //     printf("isDraw: %d",isDraw);
            // }
            DEBUG("After end game check\n");
            if (!isDraw) {
                gameEnding = 0;
            }else if(isDraw && isNotChecked)
            {
                gameEnding = 1;
            } else if(isDraw && !isNotChecked) {
                gameEnding = 2;
            }
            DEBUG("After end game check\n");
            itIsTimeToMoveForWhite = WhiteCanMove;
        }
    }
void pawnSwapper(std::vector<ChessPiece> &GameState, int pieceSelected, int mX)
{
    DrawDecal({48,80},decPS, {0.625f, 0.375f});
    DrawDecal({64,112},decR,{(mX == 2) ? 5.0f : 4.0f,(mX == 2) ? 5.0f : 4.0f}, olc::BLACK);
    DrawDecal({96,112},decC,{(mX == 3) ? 5.0f : 4.0f,(mX == 3) ? 5.0f : 4.0f}, olc::BLACK);
    DrawDecal({128,112},decB,{(mX == 4) ? 5.0f : 4.0f,(mX == 4) ? 5.0f : 4.0f}, olc::BLACK);
    DrawDecal({160,112},decQ,{(mX == 5) ? 5.0f : 4.0f,(mX == 5) ? 5.0f : 4.0f}, olc::BLACK);
    if(GetMouse(0).bPressed)
    {
        if(mX == 2)
            GameState[pieceSelected].Piece = 'R';
        if(mX == 3)
            GameState[pieceSelected].Piece = 'C';
        if(mX == 4)
            GameState[pieceSelected].Piece = 'B';
        if(mX == 5)
            GameState[pieceSelected].Piece = 'Q';
    }
    chessInitiaing.reloadPiece(GameState[pieceSelected]);
}

};

int main()
{
	ChessBot demo;
	if (demo.Construct(256, 256, 4, 4))
		demo.Start();

	return 0;
}