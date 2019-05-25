#include <iostream>
#include <string>
using namespace std;
void printboard(string board[][8])
{
	                for (int i = 0; i < 8; i++)
                {
                        cout << "\t\t" << i << " ";
                        for (int j = 0; j < 8; j++)
                        {
                                cout << board[i][j] << "  ";

                        }
                        cout << endl;
                        if (i == 7)
                        {
                                cout << "\t\t  ";
                                for (int k=0; k < 8; k++)
                                { 
                                        cout << k << "  ";
                                }
                                cout << endl;
                        }
                }
}
void move_piece(string board[][8], string original_board[][8], int svert, int shor, int evert, int ehor)
{
	//Jumping
	if ((board[evert][evert] == "r") || (board[evert][evert] == "R") || (board[evert][evert] == "b") || (board[evert][evert] == "B"))
	{
		if ((svert > evert) && (shor > ehor))
		{
			 string piece = board[svert][shor];
        		 board[evert - 1][ehor - 1] = piece; //moving top left so move the piece in that direction twice to "jump the other piece"
        		 board[svert][shor] = original_board[svert][shor]; // set the jumping piece's position tothe original board position
			 board[evert][ehor] = original_board[evert][ehor]; //set the jumped piece's position to an original board position because he is gone!
			cout << "jump bottom right to top left\n";
		}
		else if ((svert < evert) && (shor < ehor))// top left to bottom right
                {
                         string piece = board[svert][shor];
                         board[evert + 1][ehor + 1] = piece;
                         board[svert][shor] = original_board[svert][shor];
                         board[evert][ehor] = original_board[evert][ehor];
                	cout << "jump top left to bottom right\n";
		}
		else if ((svert > evert) && (shor < ehor)) // bottom left to top right
                {
                         string piece = board[svert][shor];
                         board[evert - 1][ehor + 1] = piece;
                         board[svert][shor] = original_board[svert][shor];
                         board[evert][ehor] = original_board[evert][ehor];
                	cout << "jump bottom left to top right\n";
		}
		else if ((svert < evert) && (shor > ehor)) //top right to bottom left
                {
                         string piece = board[svert][shor];
                         board[evert + 1][ehor - 1] = piece;
                         board[svert][shor] = original_board[svert][shor];
                         board[evert][ehor] = original_board[evert][ehor];
                	cout <<"jump top right to bottom left\n";
		}
	}
	//normal move
	string piece = board[svert][shor];
	board[evert][ehor] = piece;
	board[svert][shor] = original_board[svert][shor];
}
void insert_pieces(string original_board[][8], string board[][8])
{
	  int black;
	  for (int i = 0; i < 8; i++)
	  {
		if ((i + 1) % 2 == 0)
		{
			black = 1;
		}
		else
		{
			black = 0;
		}
		for (int j = 0; j < 8; j++)
		{
			if (black == 1)// ifthe square is blackand it is the first three rows, then the biece is black, last three is red
			{
				if (i < 3)
				{
					board[i][j] = "b";
				}
                                else if (i > 4)
                                {
                                        board[i][j] = "r";
                                }

				else
				{
					board[i][j] = original_board[i][j];
				}
			}
			else if (black == 0)
			{
				board[i][j] = original_board[i][j];
			}
			switch (black)
			{
				case 0:
					black = 1;
					break;
				case 1:
					black = 0;
			}

		}
	}
}
int move_checker(string board[][8], int svert, int shor, int evert, int ehor, string current_player)
{
	if (board[evert][ehor] == "+")// Can't move to red spaces!
	{
		return 1;
	}
	if ((current_player == "red") && (board[svert][shor] == "b"))//you cannot select your opponent's piece
	{
		return 2;
	}
	else if ((current_player == "black") && (board[svert][shor] == "r"))
	{
		return 2;
	}
	if ((current_player == "red") && ((board[evert][ehor] == "r") || (board[evert][ehor] == "R")))//you cannot jump your own players
	{
		return 3;
	}
	else if ((current_player == "black") && ((board[evert][ehor] == "b") || (board[evert][ehor] == "B")))
	{
		return 3;
	}
	//No jumping onto non-empty black spaces!
	if ((board[evert][evert] == "r") || (board[evert][evert] == "R") || (board[evert][evert] == "b") || (board[evert][evert] == "B"))
	{
		if ((svert > evert) && (shor > ehor))
		{
        		if (board[evert - 1][ehor - 1] != "-")
			{
				return 4;
			} 
        	}
		else if ((svert < evert) && (shor < ehor))// top left to bottom right
                {
                          if (board[evert + 1][ehor + 1] != "-") 
                        { 
                                return 4; 
                        } 
                }
		else if ((svert > evert) && (shor < ehor)) // bottom left to top right
                {
                          if (board[evert - 1][ehor + 1] != "-") 
                        { 
                                return 4; 
                        } 
		}
		else if ((svert < evert) && (shor > ehor)) //top right to bottom left
                {
                        if (board[evert + 1][ehor - 1] != "-") 
                        { 
                                return 4; 
                        } 
                }
	}
	//only kings can move backwards!!
	if ((board[svert][evert] == "r") & (svert < evert))
	{
		return 5;
	}
	else if ((board[svert][evert] == "b") & (svert > evert))
	{
		return 5;
	}
}
main()
{
	enum players {
		player_red, player_black
	};
	players current_player = player_red; //red goes first
	int starting_vert = 20;
	int starting_hor;
	int ending_vert;
	int ending_hor;
	int black;
	string original_board[8][8];
	string board[8][8];
	for (int i = 0; i < 8; i++)
	{
		if ((i + 1) % 2 == 0)
		{
			black = 1;
		}
		else
		{
			black = 0;
		}
		for (int j = 0; j < 8; j++)
		{
			if (black == 1)
			{
				original_board[i][j] = "-";
			}
			else if (black == 0)
			{
				original_board[i][j] = "+";
			}
			switch (black)
			{
				case 0:
					black = 1;
					break;
				case 1:
					black = 0;
			}

		}
	}
	insert_pieces(original_board, board);
	while (starting_vert != -1)
	{
		string piece;
		printboard(board);
		cout << "Player ";
		switch(current_player)
		{
			case player_red:
				cout << "red";
				piece = "red";
				break; 
			case player_black:
				cout << "black";
				piece = "black";
				break;
		}
		cout << " choose piece vertical: ";
		cin >> starting_vert;
		cout << "And your starting horizontal: ";
		cin >> starting_hor;
		cout << "Your ending vertical: ";
		cin >> ending_vert;
		cout << "And your ending horizontal: ";
		cin >> ending_hor;
		if (move_checker(board, starting_vert, starting_hor, ending_vert, ending_hor, piece) == 1)
		{
			cout << "You can't move to that space!\n";
			continue;

		}
		else if (move_checker(board, starting_vert, starting_hor, ending_vert, ending_hor, piece) == 2)
		{
			cout << "That is not your player!\n";
			continue;
		}
		else if (move_checker(board, starting_vert, starting_hor, ending_vert, ending_hor, piece) == 3)
                {
                        cout << "You cannot jump your own player!\n";
                        continue;
                }
		else if (move_checker(board, starting_vert, starting_hor, ending_vert, ending_hor, piece) == 4)
                {
                        cout << "You cannot jump there!\n";
                        continue;
                }
		else if (move_checker(board, starting_vert, starting_hor, ending_vert, ending_hor, piece) == 5)
                {
                        cout << "Only kings may move backwards!\n";
                        continue;
                }
		move_piece(board, original_board, starting_vert, starting_hor, ending_vert, ending_hor);
		switch (current_player)
		{
			case player_red:
				current_player = player_black;
				break;
			default:
				current_player = player_red;
		}
	}
return 0;
}
