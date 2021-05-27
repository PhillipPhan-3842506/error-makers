#include "Player.h"

Player::Player(std::string name) {
    this->name = name;
    playerHand = new LinkedList();
}

Player::~Player() {
    delete playerHand;
}

void Player::setisAI(bool b) {
    this->is_ai = b;
}

bool Player::getisAI() {
    return this->is_ai;
}

std::string Player::getPlayerName() {
    return this->name;
}

LinkedList* Player::getPlayerHand() {
    return this->playerHand;
}

int Player::getPlayerScore() {
    return this->score;
}

void Player::setPlayerScore(int scoreToSet) {
    this->score = scoreToSet;
}

void Player::updatePlayerScore(int scoreToAdd) {
    this->score = this->score + scoreToAdd;
}

void Player::addTileToPlayerHand(Tile* tile) {
    this->playerHand->addBack(tile);
}

void Player::removeTileFromPlayerHand(Tile* tileToRemove) {
    this->playerHand->deleteTile(tileToRemove);
}

Tile* Player::getSpecificTile(Tile* tile) {
    Tile* returnTile = nullptr;
    if (getPlayerHand()->getTile(tile)->tile != nullptr) {
        returnTile = getPlayerHand()->getTile(tile)->tile;
    }
    return returnTile;
}