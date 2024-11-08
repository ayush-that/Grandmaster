#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <vector>

class ChessBoard : public QWidget {
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);

private:
    void initializeBoard();
    void setupInitialPosition();
    QString getPieceSymbol(char piece);
    QString getPieceSvgPath(char piece);
    
    std::vector<std::vector<QPushButton*>> squares;
    QPushButton* selectedPiece;
    QGridLayout *layout;
    
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