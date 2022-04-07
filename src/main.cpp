#define OLC_PGE_APPLICATION
#include "chessGUI.h"

class ChessBot : public olc::PixelGameEngine
{
public:
	ChessBot()
	{
		sAppName = "MAKiTChess";
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
    olc::Sprite* sprButton = nullptr;
    olc::Decal* decButton = nullptr;

    std::vector<ChessPiece> Pieces = {};
    Turn Player1 = {};
    Turn Player2 = {};
    bool playerTurn = true;
    bool selected = false;
    int pieceSelected = 69;
    int castleRook;
    int gameEnding = 0;
    bool startedTheGame = false;
    bool backgroundColourBool = 0;
    bool textureChanging = false;
    bool AIChanging = false;
    olc::vf2d piecesScale = {4.0f,4.0f};
    char piecesMode = 'D';
    int tempDepthAI = 1;
    char tempTypeAI = 'D';
    bool tempPlayerRealAI = true;
    bool menu = true;

    chessCheck ChessC;
    chessBotI chessInitiating;
    chessAI ChessAI;
    chessGUI ChessGUI;

public:
	bool OnUserCreate() override
	{
        sprBoard = new olc::Sprite("./src/textures/board2.png");
        decBoard = new olc::Decal(sprBoard);
        sprPS = new olc::Sprite("./src/textures/PS.png");
        decPS = new olc::Decal(sprPS);
        sprB = new olc::Sprite("./src/textures/PiecesD/B/B.png");
        decB = new olc::Decal(sprB);
        sprC = new olc::Sprite("./src/textures/PiecesD/B/C.png");
        decC = new olc::Decal(sprC);
        sprQ = new olc::Sprite("./src/textures/PiecesD/B/Q.png");
        decQ = new olc::Decal(sprQ);
        sprR = new olc::Sprite("./src/textures/PiecesD/B/R.png");
        decR = new olc::Decal(sprR);
        sprButton = new olc::Sprite("./src/textures/buttonSmall.jpg");
        decButton = new olc::Decal(sprButton);
        Pieces = chessInitiating.piecesCreator("PiecesD");
        Player1 = chessInitiating.loadPlayer(0);
        Player2 = chessInitiating.loadPlayer(1);
        DEBUG("User Created\n");
        
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        olc::vf2d mouse = {float(GetMouseX()), float(GetMouseY())};
        bool PressedStart = false;
        Clear(backgroundColourBool ? olc::WHITE : olc::DARK_BLUE);
        if(menu)
        {
            if(!textureChanging && !AIChanging)
            {
                if(buttonDrawer(mouse,"start",{32,20}, backgroundColourBool))
                    menu = false;
                if(buttonDrawer(mouse,"change background",{32,60}, backgroundColourBool))
                    backgroundColourBool = !backgroundColourBool;
                if(buttonDrawer(mouse,"change texture",{32,100}, backgroundColourBool))
                    textureChanging = true;
                if(buttonDrawer(mouse,"change AI",{32,140}, backgroundColourBool))
                    AIChanging = true;
                

            } else if(textureChanging) {
                DrawDecal({224.0f,0.0f},Pieces[0].decPPieces, piecesScale);
                if(buttonDrawer(mouse,"back",{32,20}, backgroundColourBool))
                    textureChanging = false;
                if(buttonDrawer(mouse,"back",{32,20}, backgroundColourBool))
                    textureChanging = false;
                if(buttonDrawer(mouse,"Default",{32,60}, backgroundColourBool))
                {
                    Pieces.erase(Pieces.begin());
                    Pieces.shrink_to_fit();
                    Pieces = chessInitiating.piecesCreator("PiecesD");
                    piecesScale = {4.0f,4.0f};
                    piecesMode = 'D';
                }
                if(buttonDrawer(mouse,"High Quality",{32,100}, backgroundColourBool))
                {
                    Pieces.erase(Pieces.begin());
                    Pieces.shrink_to_fit();
                    Pieces = chessInitiating.piecesCreator("PiecesHQ");
                    piecesScale = {0.5f,0.5f};
                    piecesMode = 'H';
                }

            } else if(AIChanging) { 
                if(buttonDrawer(mouse,"back",{32,20}, backgroundColourBool))
                    AIChanging = false;
                std::string TempAITypeString = "AI type: ";
                TempAITypeString.push_back(tempTypeAI);
                if(buttonDrawer(mouse,TempAITypeString,{32,60}, backgroundColourBool))
                {
                    if(tempTypeAI == 'A')
                        tempTypeAI = 'B';
                    else if(tempTypeAI == 'S')
                        tempTypeAI = 'A';
                    else if(tempTypeAI == 'D')
                        tempTypeAI = 'S';
                    else if(tempTypeAI == 'B')
                        tempTypeAI = 'D';
                }
                std::string TempAIDepthString;
                TempAIDepthString = "AI depth: " + std::to_string(tempDepthAI);
                if(buttonDrawer(mouse,TempAIDepthString,{32,100}, backgroundColourBool))
                {
                    tempDepthAI++;
                    if(tempDepthAI > 10)
                        tempDepthAI = 1;
                }
                std::string TempAIRealPlayerString;
                if(tempPlayerRealAI)
                    TempAIRealPlayerString = "player real: yes";
                else
                    TempAIRealPlayerString = "player real: no";
                if(buttonDrawer(mouse,TempAIRealPlayerString,{32,140}, backgroundColourBool))
                {
                    tempPlayerRealAI = !tempPlayerRealAI;
                }
                std::string TempAIPlayer1;
                TempAIPlayer1.append("Is real: ");
                TempAIPlayer1.append(Player1.RealPlayer ? "yes" : "no");
                TempAIPlayer1.append("\nDepth: ");
                TempAIPlayer1.append(std::to_string(Player1.AI.depth));
                TempAIPlayer1.append("\nType: ");
                TempAIPlayer1.push_back(Player1.AI.option);
                if(buttonDrawer(mouse,TempAIPlayer1,{2,200}, backgroundColourBool))
                {
                    Player1.RealPlayer = tempPlayerRealAI;
                    Player1.AI.depth = tempDepthAI;
                    Player1.AI.option = tempTypeAI;
                }

                std::string TempAIPlayer2;
                TempAIPlayer2.append("Is real: ");
                TempAIPlayer2.append(Player2.RealPlayer ? "yes" : "no");
                TempAIPlayer2.append("\nDepth: ");
                TempAIPlayer2.append(std::to_string(Player2.AI.depth));
                TempAIPlayer2.append("\nType: ");
                TempAIPlayer2.push_back(Player2.AI.option);
                if(buttonDrawer(mouse,TempAIPlayer2,{128,200}, backgroundColourBool))
                {
                    Player2.RealPlayer = tempPlayerRealAI;
                    Player2.AI.depth = tempDepthAI;
                    Player2.AI.option = tempTypeAI;
                }
            }
        }
        else
        {
            if(gameEnding == 0)
            {
                Clear(olc::BLACK);
                SetPixelMode(olc::Pixel::ALPHA);
                DrawDecal({0.0f, 0.0f},decBoard, {4.0f, 4.0f});
                for(int i = 0; i < Pieces.size(); i++)
                {
                    DrawDecal({float(Pieces[i].PositionX * 32), float(Pieces[i].PositionY * 32)},Pieces[i].decPPieces, piecesScale, {255,floor(1 /(Pieces[i].Pressed + 1)) * 255,floor(1 /(Pieces[i].Pressed + 1)) * 255});
                }
                int mX = floor(mouse.x / 32);
                int mY = floor(mouse.y / 32);
                gameLoop(Pieces, playerTurn, Player1, Player2, mX, mY);
            }
            else if(gameEnding == 1)
            {
                Clear(olc::BLACK);
                DrawString({100,128},"DRAW");
            } else if(gameEnding == 2)
            {
                DrawString({100,128},playerTurn ? "White Wins":"Black Wins");
                Clear(olc::BLACK);
            }
            SetPixelMode(olc::Pixel::NORMAL);
            
        }
		return true;
	}

    void gameLoop(std::vector<ChessPiece> &GameState, bool &playerTurn, Turn player1, Turn player2, int mmX, int mmY)
    {
        GameState.shrink_to_fit();
        Turn ChosenPlayer;
        AIMove AIMove;
        // MovementChecking
        int mX;
        int mY;
        int castleRX;
        int castleKX;
        bool pawnToChange = false;
        bool selectedAPiece = false;
        // GameEnding 
        bool virtualPress = false;
        bool isDraw = true;
        bool isNotChecked = true;
        bool Castle = false;
        int kingPos;


        // Check Which turn it is
        if(playerTurn)
        {
            ChosenPlayer = player1;
        } else {
            ChosenPlayer = player2;
        }


        // Assing the movement
        if(ChosenPlayer.RealPlayer)
        {
            mX = mmX;
            mY = mmY;
        } else {
            AIMove = ChessAI.AIMOVE(ChosenPlayer,GameState);
            selected = true;
            pieceSelected = AIMove.pieceSelected;
            mX = AIMove.mX;
            mY = AIMove.mY;
            virtualPress = true;
        }

        

        // Check if the pawn can change
        for(int i = 0; i < GameState.size(); i++)
        {
            if(GameState[i].Colour == (playerTurn ? 'W' : 'B') && GameState[i].Piece == 'P' && GameState[i].PositionY == abs(playerTurn - 1) * 7)
            {
                pawnToChange = true;
                if(pawnSwapper(GameState,i, (virtualPress ? 5 : int(floor(GetMouseX()/32))),virtualPress))
                    playerTurn = !playerTurn;
            }
        }


        // If the current player is a player (:DDD) then allow them to choose the piece to move
        if(!selected && !pawnToChange)
        {
            if(GetMouse(0).bPressed)
            {
                for(int i = 0; i < GameState.size(); i++)
                {
                    if((mX == GameState[i].PositionX && mY == GameState[i].PositionY) && GameState[i].Colour == (playerTurn ? 'W' : 'B'))// 87 vs 66
                    {
                        GameState[i].Pressed = true;
                        selectedAPiece = true;
                        pieceSelected = i;
                    }
                }
            }
        }else if(selected && !pawnToChange && (virtualPress || GetMouse(0).bPressed)) {

            
            // Check if the move is correct
            if(ChessC.moveSim(GameState, playerTurn, mX, mY, pieceSelected, true, Castle, castleRook))
            {


                // Movement handling
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
                selected = false;
                for(int i = 0; i < GameState.size(); i++)
                {
                    for(int a = 0; a < GameState.size(); a++)
                    {
                        if(a != i)
                        {
                            if(GameState[i].PositionX == GameState[a].PositionX && GameState[i].PositionY == GameState[a].PositionY)
                            {
                                if(GameState[i].Colour != GameState[a].Colour)
                                {
                                    if(GameState[i].Colour == 'B')
                                    {
                                        if(!playerTurn)
                                        {
                                            GameState.erase(GameState.begin()+a);
                                        } else {
                                            GameState.erase(GameState.begin()+i);
                                        }
                                    } else {
                                        if(playerTurn)
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

            if(!pawnToChange)
            {
                for(int i = 0; i < GameState.size(); i++)
                {
                    if(GameState[i].Colour == (playerTurn ? 'W' : 'B') && GameState[i].Piece == 'P' && GameState[i].PositionY == abs(playerTurn - 1) * 7)
                        pawnToChange = true;
                }
                if(!pawnToChange)
                    playerTurn = !playerTurn;
            }
            } else {
                GameState[pieceSelected].Pressed = false;
                selected = false;
            }

        for(int i = 0; i < GameState.size();i++)
        {
            if(GameState[i].Piece == 'K' && GameState[i].Colour == playerTurn ? 'W' : 'B')
            {
                kingPos = i;
                break;
            }
        }

            if(!ChessC.CheckCheck(GameState, !playerTurn, GameState[kingPos].PositionX, GameState[kingPos].PositionY, Castle, castleRook))
                isNotChecked = false;

            for(int i = 0; i < GameState.size(); i++)
            {
                for(int a = 0;a < 8; a++)
                {
                    for(int b = 0;b < 8; b++)
                    {
                        if(mX != 2000)
                            if(ChessC.moveSim(GameState, playerTurn, a, b, i, true, Castle, castleRook))
                                isDraw = false;
                    }
                }
            }
            if(!isDraw) {
                gameEnding = 0;
            }else if(isDraw && isNotChecked)
            {
                gameEnding = 1;
            } else if(isDraw && !isNotChecked) {
                gameEnding = 2;
            }
        }
        if(selectedAPiece)
            selected = true;
    }

bool pawnSwapper(std::vector<ChessPiece> &GameState, int pieceSelected, int mX, bool virtualPress)
{
    DrawDecal({48,80},decPS, {0.625f, 0.375f});
    DrawDecal({64,112},decR,{(mX == 2) ? 5.0f : 4.0f,(mX == 2) ? 5.0f : 4.0f}, olc::BLACK);
    DrawDecal({96,112},decC,{(mX == 3) ? 5.0f : 4.0f,(mX == 3) ? 5.0f : 4.0f}, olc::BLACK);
    DrawDecal({128,112},decB,{(mX == 4) ? 5.0f : 4.0f,(mX == 4) ? 5.0f : 4.0f}, olc::BLACK);
    DrawDecal({160,112},decQ,{(mX == 5) ? 5.0f : 4.0f,(mX == 5) ? 5.0f : 4.0f}, olc::BLACK);
    if(GetMouse(0).bPressed || virtualPress)
    {
        if(mX == 2)
            GameState[pieceSelected].Piece = 'R';
        if(mX == 3)
            GameState[pieceSelected].Piece = 'C';
        if(mX == 4)
            GameState[pieceSelected].Piece = 'B';
        if(mX == 5)
            GameState[pieceSelected].Piece = 'Q';
        chessInitiating.reloadPiece(GameState[pieceSelected], piecesMode);
        if(mX < 6 && mX > 1)
            return true;
    }
    return false;
}

bool buttonDrawer(olc::vf2d mouse, std::string name, olc::vi2d position, bool backgroundColourBool)
 {
    bool PressedStart = false;
    if(mouse.x > position.x && mouse.x < position.x + 32 && mouse.y > position.y && mouse.y < position.y + 16)
        PressedStart = true;
    DrawDecal(position,decButton, {0.125f, 0.125f}, {255,floor(1 /(PressedStart + 1)) * 255,floor(1 /(PressedStart + 1)) * 255});
    DrawString({position.x+ 40,position.y},name,backgroundColourBool ? olc::BLACK : olc::WHITE);

    if(PressedStart && GetMouse(0).bPressed)
        return true;
    return false;
 }

};

int main()
{
	ChessBot demo;
	if (demo.Construct(256, 256, 4, 4))
		demo.Start();

	return 0;
}