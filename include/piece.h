#ifndef PIECE_H
#define PIECE_H

#include <QString>

class Piece {
public:
    enum class Type { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, NONE };
    enum class Color { WHITE, BLACK, NONE };

    Piece();
    Piece(Type type, Color color);

    QString getSymbol() const;
    Type getType() const;
    Color getColor() const;

private:
    Type type;
    Color color;
};

#endif