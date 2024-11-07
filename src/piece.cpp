#include "piece.h"
#include <QString>

Piece::Piece() : type(Type::NONE), color(Color::NONE) {}

Piece::Piece(Type type, Color color) : type(type), color(color) {}

QString Piece::getSymbol() const {
    if (type == Type::NONE) return "";

    switch (type) {
        case Type::KING:   return (color == Color::WHITE) ? "♔" : "♚";
        case Type::QUEEN:  return (color == Color::WHITE) ? "♕" : "♛";
        case Type::ROOK:   return (color == Color::WHITE) ? "♖" : "♜";
        case Type::BISHOP: return (color == Color::WHITE) ? "♗" : "♝";
        case Type::KNIGHT: return (color == Color::WHITE) ? "♘" : "♞";
        case Type::PAWN:   return (color == Color::WHITE) ? "♙" : "♟";
        default: return "";
    }
}

Piece::Type Piece::getType() const {
    return type;
}

Piece::Color Piece::getColor() const {
    return color;
}