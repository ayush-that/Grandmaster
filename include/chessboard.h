#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QMediaPlayer>
#include <vector>

class ChessBoard : public QWidget {
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();

private:
    void initializeBoard();
    void setupInitialPosition();
    QString getPieceSymbol(char piece);
    QString getPieceSvgPath(char piece);
    
    std::vector<std::vector<QPushButton*>> squares;
    QPushButton* selectedPiece;
    QGridLayout *layout;
    QString currentTurn;

    QMediaPlayer* moveSound;

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidKingMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol);
    char getPieceAt(int row, int col);
    
    std::vector<std::vector<char>> initialPosition = {
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
    };

private slots:
    void squareClicked();
};

#endif