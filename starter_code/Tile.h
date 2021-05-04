
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <iostream>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Colour colour;
   Shape  shape;
   Tile(Colour colour, Shape shape);
   ~Tile();
   std::string getTitleDetails();
};

#endif // ASSIGN2_TILE_H
