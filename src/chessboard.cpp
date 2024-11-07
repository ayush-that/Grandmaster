#include "chessboard.h"
#include <QtDebug>

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent), selectedPiece(nullptr) {
    layout = new QGridLayout(   this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    
    initializeBoard();
    setupInitialPosition();
}

void ChessBoard::initializeBoard() {
    squares.resize(8, std::vector<QPushButton*>(8));
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            QPushButton* square = new QPushButton(this);
            square->setFixedSize(50, 50);
            square->setProperty("row", row);
            square->setProperty("col", col);
            
            QString style = ((row + col) % 2 == 0) 
                ? "background-color: white;" 
                : "background-color: lightgray;";
            style += "font-size: 32px;";
            square->setStyleSheet(style);
            
            connect(square, &QPushButton::clicked, this, &ChessBoard::squareClicked);
            
            squares[row][col] = square;
            layout->addWidget(square, row, col);
        }
    }
}

QString ChessBoard::getPieceSymbol(char piece) {
    switch (piece) {
        case 'K': return "♔";
        case 'Q': return "♕";
        case 'R': return "♖";
        case 'B': return "♗";
        case 'N': return "♘";
        case 'P': return "♙";
        case 'k': return "♚";
        case 'q': return "♛";
        case 'r': return "♜";
        case 'b': return "♝";
        case 'n': return "♞";
        case 'p': return "♟";
        default: return "";
    }
}

void ChessBoard::setupInitialPosition() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            char piece = initialPosition[row][col];
            squares[row][col]->setText(getPieceSymbol(piece));
            
            if (isupper(piece)) {
                squares[row][col]->setStyleSheet(squares[row][col]->styleSheet() + 
                    "color: black;");
            } else if (islower(piece)) {
                squares[row][col]->setStyleSheet(squares[row][col]->styleSheet() + 
                    "color: darkred;");
            }
        }
    }
}

void ChessBoard::squareClicked() {
    QPushButton* square = qobject_cast<QPushButton*>(sender());
    if (!square) return;
    
    if (!selectedPiece && !square->text().isEmpty()) {
        selectedPiece = square;
        square->setStyleSheet(square->styleSheet() + "background-color: yellow;");
    } else if (selectedPiece) {
        square->setText(selectedPiece->text());
        square->setStyleSheet(square->styleSheet() + 
            (selectedPiece->text()[0].unicode() > 9812 ? "color: darkred;" : "color: black;"));
        
        selectedPiece->setText("");
        int row = selectedPiece->property("row").toInt();
        int col = selectedPiece->property("col").toInt();
        QString style = ((row + col) % 2 == 0) 
            ? "background-color: white;" 
            : "background-color: lightgray;";
        style += "font-size: 24px;";
        selectedPiece->setStyleSheet(style);
        
        selectedPiece = nullptr;
    }
}