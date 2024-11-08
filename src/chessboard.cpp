#include "chessboard.h"
#include <QtDebug>
#include <QIcon>
#include <cctype>

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent), selectedPiece(nullptr) {
    layout = new QGridLayout(this);
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
                ? "background-color: #7c4c3e; font-size: 32px;"
                : "background-color: #512a2a; font-size: 32px;";
            square->setStyleSheet(style);
            
            connect(square, &QPushButton::clicked, this, &ChessBoard::squareClicked);
            
            squares[row][col] = square;
            layout->addWidget(square, row, col);
        }
    }
}

QString ChessBoard::getPieceSvgPath(char piece) {
    switch (piece) {
        case 'K': return ":/assets/pieces/w_king.svg";
        case 'Q': return ":/assets/pieces/w_queen.svg";
        case 'R': return ":/assets/pieces/w_rook.svg";
        case 'B': return ":/assets/pieces/w_bishop.svg";
        case 'N': return ":/assets/pieces/w_knight.svg";
        case 'P': return ":/assets/pieces/w_pawn.svg";
        case 'k': return ":/assets/pieces/b_king.svg";
        case 'q': return ":/assets/pieces/b_queen.svg";
        case 'r': return ":/assets/pieces/b_rook.svg";
        case 'b': return ":/assets/pieces/b_bishop.svg";
        case 'n': return ":/assets/pieces/b_knight.svg";
        case 'p': return ":/assets/pieces/b_pawn.svg";
        default: return "";
    }
}

void ChessBoard::setupInitialPosition() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            char piece = initialPosition[row][col];
            QString svgPath = getPieceSvgPath(piece);
            if (!svgPath.isEmpty()) {
                QIcon icon(svgPath);
                squares[row][col]->setIcon(icon);
                squares[row][col]->setIconSize(QSize(36, 36));

                if (std::isupper(piece)) {
                    squares[row][col]->setProperty("pieceColor", "white");
                } else {
                    squares[row][col]->setProperty("pieceColor", "black");
                }
            } else {
                squares[row][col]->setIcon(QIcon());
                squares[row][col]->setProperty("pieceColor", "none");
            }
        }
    }
}

void ChessBoard::squareClicked() {
    QPushButton* square = qobject_cast<QPushButton*>(sender());
    if (!square) return;

    if (!selectedPiece && !square->icon().isNull()) {
        selectedPiece = square;

        QString pieceColor = square->property("pieceColor").toString();
        QString highlightColor;

        if (pieceColor == "white") {
            highlightColor = "#595959";
        } else if (pieceColor == "black") {
            highlightColor = "#363636";
        } else {
            highlightColor = "#FFD700";
        }

        square->setStyleSheet("background-color: " + highlightColor + "; font-size: 32px; border-radius: 0; padding: 0;");
    } 
    else if (selectedPiece) {
        square->setIcon(selectedPiece->icon());
        square->setIconSize(QSize(36, 36));

        QString movedPieceColor = selectedPiece->property("pieceColor").toString();
        square->setProperty("pieceColor", movedPieceColor);

        selectedPiece->setIcon(QIcon());

        selectedPiece->setProperty("pieceColor", "none");

        int prevRow = selectedPiece->property("row").toInt();
        int prevCol = selectedPiece->property("col").toInt();
        QString originalStyle = ((prevRow + prevCol) % 2 == 0)
            ? "background-color: #7c4c3e; font-size: 32px; border-radius: 0; padding: 0;"
            : "background-color: #512a2a; font-size: 32px; border-radius: 0; padding: 0;";
        selectedPiece->setStyleSheet(originalStyle);

        selectedPiece = nullptr;
    }
}