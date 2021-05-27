#include "Utils.h"
#include "Board.h"

std::string Utils::colourstring(std::string s) {
    std::string returnString = "";
    if (s[0] == RED) {
        returnString = "\033[91m" + s + "\033[0m";
    }
    else if (s[0] == ORANGE) {
        returnString = "\033[38;2;255;163;0m" + s + "\033[0m";
    }
    else if (s[0] == YELLOW) {
        returnString = "\x1b[38;5;226m" + s + "\x1b[0m";
    }
    else if (s[0] == GREEN) {
        returnString = "\x1b[92m" + s + "\x1b[0m";
    }
    else if (s[0] == BLUE) {
        returnString = "\x1b[94m" + s + "\x1b[0m";
    }
    else if (s[0] == PURPLE) {
        returnString = "\x1b[95m" + s + "\x1b[0m";
    }
    return returnString;
}

std::string Utils::unicodestring(std::string s) {
    std::string returnString = "";
    char shapeAsChar = s[1];
    int shape = shapeAsChar -'0';
    if (shape == CIRCLE) {
        returnString = "\u25CF ";
    }
    else if(shape == STAR_4) {
        returnString = "\u2726 ";    
    }
    else if (shape == DIAMOND) {
        returnString = "\u25C6 ";   
    }
    else if (shape == SQUARE) {
        returnString = "\u25A0 ";  
    }
    else if (shape == STAR_6) {
        returnString = "\u2605 ";  
    }
    else if (shape == CLOVER) {
        returnString = "\u2618 ";  
    }
    return returnString;
}

std::string Utils::unicodecolourstring(std::string s) {
        std::string returnString = "";
    if (s[0] == RED) {
        returnString = "\033[91m" + unicodestring(s) + "\033[0m" + '|';
    }
    else if (s[0] == ORANGE) {
        returnString = "\033[38;2;255;163;0m" + unicodestring(s) + "\033[0m" + '|';
    }
    else if (s[0] == YELLOW) {
        returnString = "\x1b[38;5;226m" + unicodestring(s) + "\x1b[0m" + '|';
    }
    else if (s[0] == GREEN) {
        returnString = "\x1b[92m" + unicodestring(s) + "\x1b[0m" + '|';
    }
    else if (s[0] == BLUE) {
        returnString = "\x1b[94m" + unicodestring(s) + "\x1b[0m" + '|';
    }
    else if (s[0] == PURPLE) {
        returnString = "\x1b[95m" + unicodestring(s) + "\x1b[0m" + '|';
    }
    return returnString;
}