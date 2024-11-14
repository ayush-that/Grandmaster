#include "chessboard.h"
#include <QtDebug>
#include <QIcon>
#include <cctype>
#include <QMap>
#include <QMediaPlayer>

QMap<QPushButton*, QString> squareOriginalStyles;

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent), selectedPiece(nullptr), currentTurn("white") {
    layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    moveSound = new QMediaPlayer(this);
    moveSound->setSource(QUrl("qrc:/assets/sounds/move-self.mp3"));
    
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
            
            squareOriginalStyles[square] = style;

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
                squares[row][col]->setProperty("pieceType", QChar(piece)); // Add this line

                if (std::isupper(piece)) {
                    squares[row][col]->setProperty("pieceColor", "white");
                } else {
                    squares[row][col]->setProperty("pieceColor", "black");
                }
            } else {
                squares[row][col]->setIcon(QIcon());
                squares[row][col]->setProperty("pieceColor", "none");
                squares[row][col]->setProperty("pieceType", QChar(' ')); // Add this line
            }
        }
    }
}

char ChessBoard::getPieceAt(int row, int col) {
    QPushButton* square = squares[row][col];
    if (square->icon().isNull()) return ' ';
    
    return square->property("pieceType").toChar().toLatin1();
}

bool ChessBoard::isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
    char piece = getPieceAt(fromRow, fromCol);
    
    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;
    
    QString fromColor = squares[fromRow][fromCol]->property("pieceColor").toString();
    QString toColor = squares[toRow][toCol]->property("pieceColor").toString();
    if (toColor == fromColor) return false;
    
    switch (std::toupper(piece)) {
        case 'P': return isValidPawnMove(fromRow, fromCol, toRow, toCol);
        case 'R': return isValidRookMove(fromRow, fromCol, toRow, toCol);
        case 'N': return isValidKnightMove(fromRow, fromCol, toRow, toCol);
        case 'B': return isValidBishopMove(fromRow, fromCol, toRow, toCol);
        case 'Q': return isValidQueenMove(fromRow, fromCol, toRow, toCol);
        case 'K': return isValidKingMove(fromRow, fromCol, toRow, toCol);
        default: return false;
    }
}

bool ChessBoard::isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol) {
    QString pieceColor = squares[fromRow][fromCol]->property("pieceColor").toString();
    int direction = (pieceColor == "white") ? 1 : -1;
    
    if (fromCol == toCol) {
        if (toRow == fromRow + direction && getPieceAt(toRow, toCol) == ' ') {
            return true;
        }
        if ((pieceColor == "white" && fromRow == 1) || (pieceColor == "black" && fromRow == 6)) {
            if (toRow == fromRow + 2 * direction && 
                getPieceAt(toRow, toCol) == ' ' && 
                getPieceAt(fromRow + direction, toCol) == ' ') {
                return true;
            }
        }
    }
    
    if (toRow == fromRow + direction && abs(toCol - fromCol) == 1) {
        if (squares[toRow][toCol]->property("pieceColor").toString() != "none" &&
            squares[toRow][toCol]->property("pieceColor").toString() != pieceColor) {
            return true;
        }
    }
    
    return false;
}

bool ChessBoard::isValidRookMove(int fromRow, int fromCol, int toRow, int toCol) {
    return (fromRow == toRow || fromCol == toCol) && isPathClear(fromRow, fromCol, toRow, toCol);
}

bool ChessBoard::isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

bool ChessBoard::isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol) {
    return (abs(toRow - fromRow) == abs(toCol - fromCol)) && isPathClear(fromRow, fromCol, toRow, toCol);
}

bool ChessBoard::isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol) {
    return (isValidRookMove(fromRow, fromCol, toRow, toCol) || 
            isValidBishopMove(fromRow, fromCol, toRow, toCol));
}

bool ChessBoard::isValidKingMove(int fromRow, int fromCol, int toRow, int toCol) {
    return abs(toRow - fromRow) <= 1 && abs(toCol - fromCol) <= 1;
}

bool ChessBoard::isPathClear(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDir = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
    int colDir = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;
    
    int row = fromRow + rowDir;
    int col = fromCol + colDir;
    
    while (row != toRow || col != toCol) {
        if (getPieceAt(row, col) != ' ') return false;
        row += rowDir;
        col += colDir;
    }
    
    return true;
}

void ChessBoard::squareClicked() {
    QPushButton* square = qobject_cast<QPushButton*>(sender());
    if (!square) return;

    int clickedRow = square->property("row").toInt();
    int clickedCol = square->property("col").toInt();

    QString pieceColor = square->property("pieceColor").toString();

    if (!selectedPiece && pieceColor != currentTurn) {
        return;
    }

    if (!selectedPiece && !square->icon().isNull()) {
        selectedPiece = square;
        QString highlightColor = (pieceColor == "white") ? "#595959" : "#363636";
        square->setStyleSheet("background-color: " + highlightColor + "; font-size: 32px; border-radius: 0; padding: 0;");
    } 
    else if (selectedPiece) {
        int selectedRow = selectedPiece->property("row").toInt();
        int selectedCol = selectedPiece->property("col").toInt();
        
        if (isValidMove(selectedRow, selectedCol, clickedRow, clickedCol)) {
            square->setIcon(selectedPiece->icon());
            square->setIconSize(QSize(36, 36));
            square->setProperty("pieceType", selectedPiece->property("pieceType"));
            square->setProperty("pieceColor", selectedPiece->property("pieceColor"));
            
            selectedPiece->setIcon(QIcon());
            selectedPiece->setProperty("pieceType", QChar(' '));
            selectedPiece->setProperty("pieceColor", "none");

            moveSound->stop();
            moveSound->play();

            currentTurn = (currentTurn == "black") ? "white" : "black";
        }

        selectedPiece->setStyleSheet(squareOriginalStyles[selectedPiece]);
        selectedPiece = nullptr;
    }
}

ChessBoard::~ChessBoard() {
    delete moveSound;
}