
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
}

Tile::~Tile() {

}

std::string Tile::getTitleDetails() {
    return colour + std::to_string(this->shape);
}
