//
// Created by Chris Jurich  on 1/6/20.
//
#include "card.h"
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <utility>

#ifndef GOFISH_DECK_H
#define GOFISH_DECK_H

class Deck{
private:
    std::vector<std::shared_ptr<Card> > cards;
    int total_dealt;

public:
    Deck() {
        total_dealt = 0;
        for(int i = 0; i<52; ++i) {
           std::shared_ptr<Card> new_card = std::make_shared<Card>(i);
            cards.push_back(new_card);
        }
    }

    void
    inline
    shuffle() {
        srand(time(NULL));
        for(int i = 0; i<52; ++i) {
            int rand_index = rand()%52;
            auto temp = cards.at(rand_index);
            cards.at(rand_index) = cards.at(i);
            cards.at(i) = temp;
        }
    }

    void
    inline
    show() {
        std::cout<<"\nThe contents of the deck are: ";
        for(const auto & c : cards) {
            c->show();
        }
        std::cout<<"\nTotal Cards: "<<cards.size()<<"\n";

    }

    std::pair<std::vector<std::shared_ptr<Card> >, std::vector< std::shared_ptr<Card> > >
    intial_deal() {
        std::vector<std::shared_ptr<Card> > hand_1, hand_2;
        for(int i = 0; i<14; ++i) {
            if(i&1) {
                hand_1.push_back(cards.at(i));
            } else {
                hand_2.push_back(cards.at(i));
            }
            cards.at(i)->dealt();
            ++total_dealt;
        }
        std::pair<std::vector<std::shared_ptr<Card> >, std::vector<std::shared_ptr<Card> > > ans;
        ans.first = hand_1;
        ans.second = hand_2;
        return ans;
    }

    std::shared_ptr<Card>
    deal_top() {
        try {
            ++total_dealt;
            cards.at(total_dealt - 1)->dealt();
            return cards.at(total_dealt - 1);
        } catch(const std::out_of_range&) {
//            std::cout<<"\nThere are no more cards!\n";
//            std::shared_ptr<Card> null_card = std::make_shared<Card>(2);
            int n_c = -1; /* So I guess you have to initialize the value in a different variable? */
            return std::make_shared<Card>(n_c);
        }
    }

};

#endif //GOFISH_DECK_H