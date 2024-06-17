#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>

// PieceType enum
enum class PieceType {
    X,
    O
};

// PlayingPiece base class
class PlayingPiece {
public:
    PieceType pieceType;

    PlayingPiece(PieceType type) {
        this->pieceType=type;
    }
    virtual ~PlayingPiece() = default; // Virtual destructor for proper cleanup of derived classes
};

// PlayingPieceO derived class
class PlayingPieceO : public PlayingPiece {
public:
    PlayingPieceO() : PlayingPiece(PieceType::O) {}
};

// PlayingPieceX derived class
class PlayingPieceX : public PlayingPiece {
public:
    PlayingPieceX() : PlayingPiece(PieceType::X) {}
};

// Player class
class Player {
public:
    std::string name;
    PlayingPiece* playingPiece;

    Player(const std::string& name, PlayingPiece* piece) : name(name), playingPiece(piece) {}

    std::string getName() const {
        return name;
    }

    void setName(const std::string& name) {
        this->name = name;
    }

    PlayingPiece* getPlayingPiece() const {
        return playingPiece;
    }

    void setPlayingPiece(PlayingPiece* piece) {
        this->playingPiece = piece;
    }
};

// Board class
class Board {
public:
    int size;
    std::vector<std::vector<PlayingPiece*>> board;
    

    Board(int size) : size(size), board(size, std::vector<PlayingPiece*>(size, nullptr)) {}

    bool addPiece(int row, int column, PlayingPiece* playingPiece) {
        if (board[row][column] != nullptr) {
            return false;
        }
        board[row][column] = playingPiece;
        return true;
    }

    std::vector<std::pair<int, int>> getFreeCells() const {
        std::vector<std::pair<int, int>> freeCells;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == nullptr) {
                    freeCells.emplace_back(i, j);
                }
            }
        }
        return freeCells;
    }

    void printBoard() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] != nullptr) {
                    std::cout << (board[i][j]->pieceType == PieceType::X ? "X" : "O") << "   ";
                } else {
                    std::cout << "    ";
                }
                std::cout << " | ";
            }
            std::cout << std::endl;
        }
    }
};

// TicTacToeGame class
class TicTacToeGame {
public:
    std::deque<Player> players;
    Board gameBoard;

    TicTacToeGame() : gameBoard(3) {}

    void initializeGame() {
        // Creating 2 players
        PlayingPieceX* crossPiece = new PlayingPieceX();
        Player player1("Player1", crossPiece);

        PlayingPieceO* noughtsPiece = new PlayingPieceO();
        Player player2("Player2", noughtsPiece);

        players.push_back(player1);
        players.push_back(player2);
    }

    std::string startGame() {
        bool noWinner = true;
        while (noWinner) {
            // Take out the player whose turn it is and also put the player back in the list
            Player playerTurn = players.front();
            players.pop_front();

            // Get the free space from the board
            gameBoard.printBoard();
            std::vector<std::pair<int, int>> freeSpaces = gameBoard.getFreeCells();
            if (freeSpaces.empty()) {
                noWinner = false;
                continue;
            }

            // Read the user input
            std::cout << "Player:" << playerTurn.name << " Enter row,column: ";
            std::string s;
            std::getline(std::cin, s);
            std::stringstream ss(s);
            std::string item;
            std::vector<int> values;
            while (std::getline(ss, item, ',')) {
                values.push_back(std::stoi(item));
            }
            int inputRow = values[0];
            int inputColumn = values[1];

            // Place the piece
            bool pieceAddedSuccessfully = gameBoard.addPiece(inputRow, inputColumn, playerTurn.getPlayingPiece());
            if (!pieceAddedSuccessfully) {
                // Player cannot insert the piece into this cell, player has to choose another cell
                std::cout << "Incorrect position chosen, try again" << std::endl;
                players.push_front(playerTurn);
                continue;
            }
            players.push_back(playerTurn);

            bool winner = isThereWinner(inputRow, inputColumn, playerTurn.getPlayingPiece()->pieceType);
            if (winner) {
                return playerTurn.name;
            }
        }
        return "tie";
    }

    bool isThereWinner(int row, int column, PieceType pieceType) {
        bool rowMatch = true;
        bool columnMatch = true;
        bool diagonalMatch = true;
        bool antiDiagonalMatch = true;

        // Need to check in row
        for (int i = 0; i < gameBoard.size; ++i) {
            if (gameBoard.board[row][i] == nullptr || gameBoard.board[row][i]->pieceType != pieceType) {
                rowMatch = false;
            }
        }

        // Need to check in column
        for (int i = 0; i < gameBoard.size; ++i) {
            if (gameBoard.board[i][column] == nullptr || gameBoard.board[i][column]->pieceType != pieceType) {
                columnMatch = false;
            }
        }

        // Need to check diagonals
        for (int i = 0, j = 0; i < gameBoard.size; ++i, ++j) {
            if (gameBoard.board[i][j] == nullptr || gameBoard.board[i][j]->pieceType != pieceType) {
                diagonalMatch = false;
            }
        }

        // Need to check anti-diagonals
        for (int i = 0, j = gameBoard.size - 1; i < gameBoard.size; ++i, --j) {
            if (gameBoard.board[i][j] == nullptr || gameBoard.board[i][j]->pieceType != pieceType) {
                antiDiagonalMatch = false;
            }
        }

        return rowMatch || columnMatch || diagonalMatch || antiDiagonalMatch;
    }
};

int main() {
    TicTacToeGame game;
    game.initializeGame();
    std::cout << "Game winner is: " << game.startGame() << std::endl;
    return 0;
}
