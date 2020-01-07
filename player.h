//
// Created by Chris Jurich  on 1/6/20.
//
#include "card.h"
#include <map>
#include <vector>
#include <string>
#include <memory>


#ifndef GOFISH_PLAYER_H
#define GOFISH_PLAYER_H

class Player{
private:
    std::map<std::string, std::vector<std::shared_ptr<Card> > > hand;
    int sets;
    std::string name;

public:
    Player(std::string _name) {
        name = _name;
        for(const auto & _f : faces) {
            std::vector<std::shared_ptr<Card > > temp;
            hand[_f] = temp;
        }
        sets = 0;
    }

    std::vector<std::string>
    legal_cards() {
        std::vector<std::string> ans;
        for(const auto& names : faces) {
            if(hand[names].size() > 0) {
                ans.push_back(names);
            }
        }

        return ans;
    }

    void
    add_cards(std::vector<std::shared_ptr<Card > >& new_cards) {
        for (auto& cards : new_cards) {
            hand[cards->get_face()].push_back(cards);
        }
    }

    void
    add_card(std::shared_ptr<Card >& new_card) {
        hand[new_card->get_face()].push_back(new_card);
    }

    void
    show_hand() {
//        std::cout<<"\n"<<name<<"'s hand: ";
        std::cout<<"\nFace | Number";
        std::cout<<"\n-------------";
        for(auto& _faces : faces) {
            int card_count = hand[_faces].size();
            if(card_count > 0) {
                std::cout<<"\n"<<_faces;
                if(card_count > 1) {
                    std::cout<<"\'s";
                }
                std::cout<<" : "<<card_count;
            }
        }
        if(name.at(name.size() - 1) == 's' || name.at(name.size() - 1) == 'S') {
            std::cout<<"\n"<<name<<"\' score: "<<sets<<"\n";
        } else {
            std::cout<<"\n"<<name<<"\'s score: "<<sets<<"\n";
        }

    }

    std::vector<std::shared_ptr<Card > >
    card_query(std::string card_face) {
        std::vector<std::shared_ptr<Card> > lost_cards;
        if(hand.find(card_face) != hand.end()) {
            lost_cards = hand[card_face];
            hand[card_face].clear();
        }
        return lost_cards;
    }

    void
    check_pairs() {
        for(auto& types : hand) {
            if(types.second.size() == 4 and types.first != "NULL_CARD") {
                ++sets;
                std::cout<<"\n"<<name<<" has collected all of the "<<types.first<<"\'s";
                types.second.clear();
            }
        }
    }

    int
    get_pairs() {
        return sets;
    }
};

#endif //GOFISH_PLAYER_H