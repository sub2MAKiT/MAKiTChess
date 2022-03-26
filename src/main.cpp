#define OLC_PGE_APPLICATION
#include "chess.h"

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
public:
	bool OnUserCreate() override
	{
        ChessBotH chess;
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
                        printf("%d", selected);
                        selected = true;
                        pieceSelected = i;
                        printf("%d", selected);
                    }
                }
            }
        } else {
            if(GetMouse(0).bPressed)
            {
                printf("?");
                moveCorrect = moveSim(GameState, playerTurn, player1, player2, mX, mY, pieceSelected, true);
                moved = true;
            }
            if(moved)
            {
                printf("\nmoved, %d\n",moveCorrect);
                if(moveCorrect)
                {
                    GameState[pieceSelected].PositionX = mX;
                    GameState[pieceSelected].PositionY = mY;
                    GameState[pieceSelected].Pressed = false;
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
bool moveSim(std::vector<ChessPiece> GameState, bool &playerTurn, Turn player1, Turn player2, int mX, int mY, int pieceSelected, bool saverFromLoop)
{
    std::vector<ChessPiece> GameStateCopy = GameState;
    bool moveCorrect;
    bool move1 = false;
    bool move2 = false;
    bool moveDone = false;
    char correctColour;
    bool correctTurn;
    if(player1.Player == playerTurn)
    {
        correctTurn = true;
        correctColour = 'W';
    } else {
        correctTurn = false;
        correctColour = 'B';
    }
    if(GameState[pieceSelected].Colour == correctColour)
    {
        if(!saverFromLoop)
            printf("\ncheckCheck1 %d %d",mX, mY);
        if(GameState[pieceSelected].Piece == 'P' )
        {
            for(int i = 0; i < GameState.size(); i++)
            {
                if((GameState[i].PositionX == GameState[pieceSelected].PositionX && GameState[i].PositionY == GameState[pieceSelected].PositionY - ((playerTurn + 1) * 2 - 3)) || ( GameState[i].PositionX == GameState[pieceSelected].PositionX && (GameState[pieceSelected].PositionY == abs(((playerTurn + 1) * (playerTurn + 1) * (playerTurn + 1)) - 2 && GameState[i].PositionY == GameState[pieceSelected].PositionY - (((playerTurn + 1) * 2 - 3) * 2)))) || ((((GameState[pieceSelected].PositionY == 6 && GameState[i].PositionY == 4) && GameState[pieceSelected].PositionX == GameState[i].PositionX)&& mY != 5)||(((GameState[pieceSelected].PositionY == 1 && GameState[i].PositionY == 3) && GameState[pieceSelected].PositionX == GameState[i].PositionX)&& mY != 2)))
                    move1 = true;
                if((((mX == GameState[pieceSelected].PositionX + 1 || mX == GameState[pieceSelected].PositionX - 1) && mX == GameState[i].PositionX) && mY == GameState[i].PositionY)&& mY == GameState[pieceSelected].PositionY - ((playerTurn + 1) * 2 - 3))
                    move2 = true;
            }
            //                                if((((((mX == GameState[pieceSelected].PositionX + 1 || mX == GameState[pieceSelected].PositionX - 1) && mX == GameState[i].PositionX) && mY == GameState[i].PositionY) && mY == GameState[pieceSelected].PositionY - (playerTurn + 1) * 2 - 3) ||  ((mX == GameState[pieceSelected].PositionX && ((mY != GameState[i].PositionY || mX != GameState[i].PositionX) && (mY == GameState[pieceSelected].PositionY - ((playerTurn + 1) * 2 - 3) || ( GameState[pieceSelected].PositionY == abs(((playerTurn + 1) * (playerTurn + 1) * (playerTurn + 1)) - 2) && mY == GameState[pieceSelected].PositionY - (((playerTurn + 1) * 2 - 3) * 2)))))))&& (GameState[i].PositionX != GameState[pieceSelected].PositionX || GameState[i].PositionY != GameState[pieceSelected].PositionY - ((playerTurn + 1) * 2 - 3)))
            if(move2 || ((mX == GameState[pieceSelected].PositionX && (!move1 && (mY == GameState[pieceSelected].PositionY - ((playerTurn + 1) * 2 - 3) || ( GameState[pieceSelected].PositionY == abs(((playerTurn + 1) * (playerTurn + 1) * (playerTurn + 1)) - 2) && mY == GameState[pieceSelected].PositionY - (((playerTurn + 1) * 2 - 3) * 2)))))))
            {
                if(!saverFromLoop)
                    printf("\ncheckCheck2");
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                printf("182\n");
                selected = false; 
            }
            
        }
        if(GameState[pieceSelected].Piece == 'R' )
        {
            if(!((mX == GameState[pieceSelected].PositionX && mY == GameState[pieceSelected].PositionY)||!(mX == GameState[pieceSelected].PositionX || mY == GameState[pieceSelected].PositionY)))
                {
                    if(mX > GameState[pieceSelected].PositionX)
                    {
                        for(int a = GameState[pieceSelected].PositionX + 1; a < mX; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == GameState[pieceSelected].PositionY)
                                    move1 = true;
                            }
                        }
                    } else if(mX < GameState[pieceSelected].PositionX) {
                        for(int a = GameState[pieceSelected].PositionX - 1; a > mX; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == GameState[pieceSelected].PositionY)
                                    move1 = true;
                            }
                        }
                    } else if(mY > GameState[pieceSelected].PositionY){
                        for(int a = GameState[pieceSelected].PositionY + 1; a < mY; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == GameState[pieceSelected].PositionX)
                                    move1 = true;
                            }
                        }
                    } else {
                            for(int a = GameState[pieceSelected].PositionY - 1; a > mY; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == GameState[pieceSelected].PositionX)
                                    move1 = true;
                            }
                        }
                    }
                } else {
                    move1 = true;
                }
            if(!move1)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                printf("237\n");
                selected = false; 
            }
            
        }
        if(GameState[pieceSelected].Piece == 'B')
        {
            if(mX != GameState[pieceSelected].PositionX && mY != GameState[pieceSelected].PositionY)
            {
                if(abs(mX - GameState[pieceSelected].PositionX) == abs(mY - GameState[pieceSelected].PositionY))
                {
                    for(int a = 0; a < GameState.size(); a++)
                    {
                        for(int i = (abs(mX  - GameState[pieceSelected].PositionX) - 1) *(abs(mX  - GameState[pieceSelected].PositionX) / (mX  - GameState[pieceSelected].PositionX)); i != 0; i += -1 * (abs(i) / i))
                        {
                            if(GameState[pieceSelected].PositionX + i == GameState[a].PositionX && GameState[pieceSelected].PositionY + abs(i) * (abs(mY - GameState[pieceSelected].PositionY)/(mY - GameState[pieceSelected].PositionY)) == GameState[a].PositionY)
                            {
                                move1 = true;
                            }
                        }
                    }
                } else {
                    move1 = true;
                }
            } else {
                move1 = true;
            }
            if(!move1)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                printf("269\n");
                selected = false; 
            }
        }
        if(GameState[pieceSelected].Piece == 'C')
        {
            for(int i = GameState[pieceSelected].PositionX - 2;i <= GameState[pieceSelected].PositionX + 2; i += 1)
            {
                if(i - GameState[pieceSelected].PositionX != 0)
                {
                    if(mX == i && (mY == GameState[pieceSelected].PositionY + (3 - abs(i - GameState[pieceSelected].PositionX)) || mY == GameState[pieceSelected].PositionY - (3 - abs(i - GameState[pieceSelected].PositionX))))
                        move1 = true;
                }
            }
            if(move1)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                printf("288\n");
                selected = false; 
            }
        }
        if(GameState[pieceSelected].Piece == 'Q')
        {
            if(!((mX == GameState[pieceSelected].PositionX && mY == GameState[pieceSelected].PositionY)||!(mX == GameState[pieceSelected].PositionX || mY == GameState[pieceSelected].PositionY)))
                {
                    if(mX > GameState[pieceSelected].PositionX)
                    {
                        for(int a = GameState[pieceSelected].PositionX + 1; a < mX; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == GameState[pieceSelected].PositionY)
                                    move1 = true;
                            }
                        }
                    } else if(mX < GameState[pieceSelected].PositionX) {
                        for(int a = GameState[pieceSelected].PositionX - 1; a > mX; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == GameState[pieceSelected].PositionY)
                                    move1 = true;
                            }
                        }
                    } else if(mY > GameState[pieceSelected].PositionY){
                        for(int a = GameState[pieceSelected].PositionY + 1; a < mY; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == GameState[pieceSelected].PositionX)
                                    move1 = true;
                            }
                        }
                    } else {
                            for(int a = GameState[pieceSelected].PositionY - 1; a > mY; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == GameState[pieceSelected].PositionX)
                                    move1 = true;
                            }
                        }
                    }
                } else {
                    move1 = true;
                }
            
            if(mX != GameState[pieceSelected].PositionX && mY != GameState[pieceSelected].PositionY)
            {
                if(abs(mX - GameState[pieceSelected].PositionX) == abs(mY - GameState[pieceSelected].PositionY))
                {
                    for(int a = 0; a < GameState.size(); a++)
                    {
                        for(int i = (abs(mX  - GameState[pieceSelected].PositionX) - 1) *(abs(mX  - GameState[pieceSelected].PositionX) / (mX  - GameState[pieceSelected].PositionX)); i != 0; i += -1 * (abs(i) / i))
                        {
                            if(GameState[pieceSelected].PositionX + i == GameState[a].PositionX && GameState[pieceSelected].PositionY + abs(i) * (abs(mY - GameState[pieceSelected].PositionY)/(mY - GameState[pieceSelected].PositionY)) == GameState[a].PositionY)
                            {
                                move2 = true;
                            }
                        }
                    }
                } else {
                    move2 = true;
                }
            } else {
                move2 = true;
            }
            if(!move1 || !move2)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                printf("363\n");
                selected = false; 
            }
        }
        if(GameState[pieceSelected].Piece == 'K')
        {
            if(abs(mX - GameState[pieceSelected].PositionX) <= 1 && abs(mY - GameState[pieceSelected].PositionY) <= 1)
                move1 = true;
            if(move1)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                printf("376\n");
                selected = false;
            }
        }
    }
    if(moveDone)
    {
        moveCorrect = true;
        printf("\nmove done, %d\n",moveCorrect);
        GameStateCopy[pieceSelected].PositionX = mX;
                printf("\nmove done1, %d\n",moveCorrect);
        GameStateCopy[pieceSelected].PositionY = mY;
                printf("\nmove done2, %d\n",moveCorrect);
        for(int i = 0; i < GameStateCopy.size(); i++)
        {
            for(int a = 0; a < GameStateCopy.size(); a++)
            {
                if(a != i)
                {
                    if((GameStateCopy[i].PositionX == GameStateCopy[a].PositionX && GameStateCopy[i].PositionY == GameStateCopy[a].PositionY) && GameStateCopy[i].Colour == GameStateCopy[a].Colour)
                    {                
                        printf("%d",moveCorrect);
                        moveCorrect = false;
                    }
                }
            }
        }
                printf("\nmove done3, %d\n",moveCorrect);
    }
    int kingPos;
            printf("\nmove done4, %d\n",moveCorrect);
    printf("\nmoved before cc, %d\n",moveCorrect);

     for(int i = 0; i < GameStateCopy.size(); i++)
                    {
                        for(int a = 0; a < GameStateCopy.size(); a++)
                        {
                            if(a != i)
                            {
                                if(GameStateCopy[i].PositionX == GameStateCopy[a].PositionX)
                                {
                                    if(GameStateCopy[i].PositionY == GameStateCopy[a].PositionY)
                                    {
                                        if(GameStateCopy[i].Colour == 'B')
                                        {
                                            if(!correctTurn)
                                            {
                                                GameStateCopy.erase(GameStateCopy.begin()+a);
                                            } else {
                                                GameStateCopy.erase(GameStateCopy.begin()+i);
                                            }
                                        } else {
                                            if(correctTurn)
                                            {
                                                GameStateCopy.erase(GameStateCopy.begin()+a);
                                            } else {
                                                GameStateCopy.erase(GameStateCopy.begin()+i);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
    for(int i = 0; i < GameStateCopy.size(); i++)
    {
        if(GameStateCopy[i].Piece == 'K')
        if(GameStateCopy[i].Colour == correctColour)
        kingPos = i;
    }

    if(moveCorrect)
        if(saverFromLoop)
            moveCorrect = CheckCheck(GameStateCopy, playerTurn, player1, player2, GameStateCopy[kingPos].PositionX, GameStateCopy[kingPos].PositionY);
    printf("\nmoved after cc, %d\n",moveCorrect);
    return moveCorrect;
}
bool CheckCheck(std::vector<ChessPiece> GameState, bool playerTurn, Turn player1, Turn player2, int kPX, int kPY)
    {
        // true means no check
        bool PlayerTurn = !playerTurn;
        bool temp = true;
        std::vector<ChessPiece> copyPieces = GameState;
        char colour;
        if(playerTurn == true)
            colour = 'B';
        else
            colour = 'W';
        printf("\nCheckCheck checker");
        printf("\nCheckCheck check for checking %d",temp);
        for(int i = 0; i < copyPieces.size(); i++)
        {
            printf("%d",kPY);
            if(moveSim(copyPieces, PlayerTurn, player1, player2, kPX, kPY, i, false))
            {
                printf("\n%c,%c,%d",copyPieces[i].Colour, copyPieces[i].Piece,i);
                temp = false;
                break;
            }
        }
        printf("\nCheckCheck checking %d\n", temp);
        return temp;
    }
};

int main()
{
	ChessBot demo;
	if (demo.Construct(256, 256, 4, 4))
		demo.Start();

	return 0;
}