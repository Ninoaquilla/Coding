#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iomanip>

// Chess piece representation
enum PieceType { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum Color { NONE, WHITE, BLACK };

struct Piece {
    PieceType type;
    Color color;
    Piece(PieceType t = EMPTY, Color c = NONE) : type(t), color(c) {}
};

struct Move {
    int fromRow, fromCol, toRow, toCol;
    Piece promotion;
    Move(int fr, int fc, int tr, int tc, Piece promo = Piece()) :
        fromRow(fr), fromCol(fc), toRow(tr), toCol(tc), promotion(promo) {}
};

class Board {
public:
    Piece board[8][8];
    Color turn;
    std::vector<Move> moveHistory;

    Board() {
        reset();
    }

    void reset() {
        // Set up pieces
        for (int i = 0; i < 8; ++i) {
            board[1][i] = Piece(PAWN, WHITE);
            board[6][i] = Piece(PAWN, BLACK);
        }
        for (int i = 2; i < 6; ++i)
            for (int j = 0; j < 8; ++j)
                board[i][j] = Piece();

        board[0][0] = board[0][7] = Piece(ROOK, WHITE);
        board[0][1] = board[0][6] = Piece(KNIGHT, WHITE);
        board[0][2] = board[0][5] = Piece(BISHOP, WHITE);
        board[0][3] = Piece(QUEEN, WHITE);
        board[0][4] = Piece(KING, WHITE);

        board[7][0] = board[7][7] = Piece(ROOK, BLACK);
        board[7][1] = board[7][6] = Piece(KNIGHT, BLACK);
        board[7][2] = board[7][5] = Piece(BISHOP, BLACK);
        board[7][3] = Piece(QUEEN, BLACK);
        board[7][4] = Piece(KING, BLACK);

        turn = WHITE;
        moveHistory.clear();
    }

    void print() {
        std::cout << "  a b c d e f g h\n";
        for (int i = 7; i >= 0; --i) {
            std::cout << i + 1 << " ";
            for (int j = 0; j < 8; ++j) {
                std::cout << pieceChar(board[i][j]) << " ";
            }
            std::cout << i + 1 << "\n";
        }
        std::cout << "  a b c d e f g h\n";
        std::cout << "Turn: " << (turn == WHITE ? "White" : "Black") << "\n";
    }

    char pieceChar(const Piece& p) {
        if (p.type == EMPTY) return '.';
        char c;
        switch (p.type) {
            case PAWN: c = 'P'; break;
            case KNIGHT: c = 'N'; break;
            case BISHOP: c = 'B'; break;
            case ROOK: c = 'R'; break;
            case QUEEN: c = 'Q'; break;
            case KING: c = 'K'; break;
            default: c = '?';
        }
        if (p.color == BLACK) c = tolower(c);
        return c;
    }

    bool isInside(int r, int c) {
        return r >= 0 && r < 8 && c >= 0 && c < 8;
    }

    bool isOwnPiece(int r, int c, Color color) {
        return isInside(r, c) && board[r][c].color == color;
    }

    bool isOpponentPiece(int r, int c, Color color) {
        return isInside(r, c) && board[r][c].color != color && board[r][c].color != NONE;
    }

    std::vector<Move> generateMoves(Color color) {
        std::vector<Move> moves;
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (board[r][c].color == color) {
                    std::vector<Move> pm = pieceMoves(r, c);
                    moves.insert(moves.end(), pm.begin(), pm.end());
                }
            }
        }
        return moves;
    }

    std::vector<Move> pieceMoves(int r, int c) {
        std::vector<Move> moves;
        Piece p = board[r][c];
        if (p.type == EMPTY) return moves;
        int dr[] = {-1, 1, 0, 0, -1, -1, 1, 1};
        int dc[] = {0, 0, -1, 1, -1, 1, -1, 1};
        switch (p.type) {
            case PAWN: {
                int dir = (p.color == WHITE) ? 1 : -1;
                int startRow = (p.color == WHITE) ? 1 : 6;
                // Forward
                if (isInside(r + dir, c) && board[r + dir][c].type == EMPTY) {
                    moves.push_back(Move(r, c, r + dir, c));
                    // Double move
                    if (r == startRow && board[r + 2 * dir][c].type == EMPTY)
                        moves.push_back(Move(r, c, r + 2 * dir, c));
                }
                // Captures
                for (int dcapt = -1; dcapt <= 1; dcapt += 2) {
                    int nr = r + dir, nc = c + dcapt;
                    if (isInside(nr, nc) && isOpponentPiece(nr, nc, p.color))
                        moves.push_back(Move(r, c, nr, nc));
                }
                break;
            }
            case KNIGHT: {
                int drn[] = {-2, -2, -1, -1, 1, 1, 2, 2};
                int dcn[] = {-1, 1, -2, 2, -2, 2, -1, 1};
                for (int i = 0; i < 8; ++i) {
                    int nr = r + drn[i], nc = c + dcn[i];
                    if (isInside(nr, nc) && !isOwnPiece(nr, nc, p.color))
                        moves.push_back(Move(r, c, nr, nc));
                }
                break;
            }
            case BISHOP: {
                for (int d = 4; d < 8; ++d) {
                    for (int k = 1; k < 8; ++k) {
                        int nr = r + dr[d] * k, nc = c + dc[d] * k;
                        if (!isInside(nr, nc)) break;
                        if (isOwnPiece(nr, nc, p.color)) break;
                        moves.push_back(Move(r, c, nr, nc));
                        if (isOpponentPiece(nr, nc, p.color)) break;
                    }
                }
                break;
            }
            case ROOK: {
                for (int d = 0; d < 4; ++d) {
                    for (int k = 1; k < 8; ++k) {
                        int nr = r + dr[d] * k, nc = c + dc[d] * k;
                        if (!isInside(nr, nc)) break;
                        if (isOwnPiece(nr, nc, p.color)) break;
                        moves.push_back(Move(r, c, nr, nc));
                        if (isOpponentPiece(nr, nc, p.color)) break;
                    }
                }
                break;
            }
            case QUEEN: {
                for (int d = 0; d < 8; ++d) {
                    for (int k = 1; k < 8; ++k) {
                        int nr = r + dr[d] * k, nc = c + dc[d] * k;
                        if (!isInside(nr, nc)) break;
                        if (isOwnPiece(nr, nc, p.color)) break;
                        moves.push_back(Move(r, c, nr, nc));
                        if (isOpponentPiece(nr, nc, p.color)) break;
                    }
                }
                break;
            }
            case KING: {
                for (int d = 0; d < 8; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (isInside(nr, nc) && !isOwnPiece(nr, nc, p.color))
                        moves.push_back(Move(r, c, nr, nc));
                }
                break;
            }
            default: break;
        }
        return moves;
    }

    bool makeMove(const Move& m) {
        Piece& from = board[m.fromRow][m.fromCol];
        Piece& to = board[m.toRow][m.toCol];
        if (from.type == EMPTY || from.color != turn) return false;
        std::vector<Move> legal = generateMoves(turn);
        bool found = false;
        for (auto& mv : legal) {
            if (mv.fromRow == m.fromRow && mv.fromCol == m.fromCol &&
                mv.toRow == m.toRow && mv.toCol == m.toCol) {
                found = true;
                break;
            }
        }
        if (!found) return false;
        to = from;
        from = Piece();
        moveHistory.push_back(m);
        turn = (turn == WHITE) ? BLACK : WHITE;
        return true;
    }

    bool isCheck(Color color) {
        int kr = -1, kc = -1;
        for (int r = 0; r < 8; ++r)
            for (int c = 0; c < 8; ++c)
                if (board[r][c].type == KING && board[r][c].color == color)
                    kr = r, kc = c;
        if (kr == -1) return false;
        Color opp = (color == WHITE) ? BLACK : WHITE;
        std::vector<Move> oppMoves = generateMoves(opp);
        for (auto& m : oppMoves)
            if (m.toRow == kr && m.toCol == kc)
                return true;
        return false;
    }

    bool isCheckmate(Color color) {
        if (!isCheck(color)) return false;
        std::vector<Move> moves = generateMoves(color);
        for (auto& m : moves) {
            Board copy = *this;
            copy.makeMove(m);
            if (!copy.isCheck(color))
                return false;
        }
        return true;
    }

    bool isStalemate(Color color) {
        if (isCheck(color)) return false;
        std::vector<Move> moves = generateMoves(color);
        for (auto& m : moves) {
            Board copy = *this;
            copy.makeMove(m);
            if (!copy.isCheck(color))
                return false;
        }
        return true;
    }

    std::string moveToString(const Move& m) {
        std::string s;
        s += 'a' + m.fromCol;
        s += '1' + m.fromRow;
        s += '-';
        s += 'a' + m.toCol;
        s += '1' + m.toRow;
        return s;
    }

    Move stringToMove(const std::string& s) {
        if (s.size() < 5) return Move(-1, -1, -1, -1);
        int fc = s[0] - 'a', fr = s[1] - '1';
        int tc = s[3] - 'a', tr = s[4] - '1';
        return Move(fr, fc, tr, tc);
    }
};

class ChessGame {
    Board board;
public:
    void run() {
        std::string input;
        while (true) {
            board.print();
            if (board.isCheckmate(board.turn)) {
                std::cout << (board.turn == WHITE ? "White" : "Black") << " is checkmated!\n";
                break;
            }
            if (board.isStalemate(board.turn)) {
                std::cout << "Stalemate!\n";
                break;
            }
            if (board.isCheck(board.turn)) {
                std::cout << (board.turn == WHITE ? "White" : "Black") << " is in check!\n";
            }
            std::cout << "Enter move (e.g. e2-e4), 'q' to quit: ";
            std::getline(std::cin, input);
            if (input == "q") break;
            Move m = board.stringToMove(input);
            if (!board.makeMove(m)) {
                std::cout << "Invalid move!\n";
            }
        }
    }
};

int main() {
    ChessGame game;
    game.run();
    return 0;
}