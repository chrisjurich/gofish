//
// Created by Chris Jurich  on 1/6/20.
//
#include <memory>
#include <string>
#include <iostream>
#include <iomanip>


#ifndef GOFISH_CARD_H
#define GOFISH_CARD_H

std::string faces[] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
std::string suits[] = {"Hearts", "Clubs", "Diamonds", "Spades"};

class Card{
private:
    int id;
    std::string suit;
    std::string face;
    std::string name;
    bool is_dealt;

public:
    Card(int _id) {
        is_dealt = false;
        id = _id;
        if(_id != -1) {
            suit = suits[id/13];
            face = faces[id%13];
            name = face + " of " + suit;
        } else {
            suit = "NULL_CARD";
            face = "NULL_CARD";
            name = "NULL_CARD";
        }
    }

    ~Card() {
        /* Not sure why this is here*/
    }

    std::string
    inline
    get_face() {
        return face;
    }

    void
    inline
    show() {
        std::cout<<"\n"<<name<< " dealt : "<<std::boolalpha<<is_dealt;
    }

    std::string
    inline
    get_name() {
        return name;
    }

    void
    dealt() {
        is_dealt = true;
    }
};

#endif //GOFISH_CARD_H