//
// Created by Chris Jurich  on 1/6/20.
//
#include "card.h"
#include "player.h"
#include "deck.h"
#include "colors.h"
#include <memory>
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

#ifndef GOFISH_GAME_H
#define GOFISH_GAME_H

std::unordered_map<std::string, int> converter;

class Game{
private:
    std::shared_ptr<Deck> game_deck;
    std::shared_ptr<Player> p_1;
    std::shared_ptr<Player> p_2;
    std::string winner;
    bool game_continues;

public:
    Game() {

    }

    void
    play() {

        int val = 0;
        for(auto& vals : faces) {
            converter[vals] = val;
            ++val;
        }
        std::cout<<MAGENTA;
        std::cout<<"\n"<<"Welcome to the go fish game!";
        std::cout<<RESET;
        std::cout<<"\nYou will be playing the game against an advanced, computer opponent\nAre you ready?";
        std::cout<<"\nPress";
        std::cout<<GREEN;
        std::cout<<" 1 ";
        std::cout<<RESET;
        std::cout<<"to contiue, any other key to quit:\n";
        int player_choice;
        std::cin>>player_choice;
        if(player_choice != 1 ) {
            return;
        }
        std::string p_name;
        std::cout<<"\nWhat is your name, player?\n";
        std::cin>>p_name;
        std::cout<<"\nYou name is ";
        std::cout<<MAGENTA;
        std::cout<<p_name;
        std::cout<<RESET;
        std::string dummy;
        std::cout<<"\nLet's begin! The computer goes first, but we need to deal out the cards!\nPress any key to continue\n";
        std::cin>>dummy;
        /* Initializing the player objects */
        std::string name_1 = "name_1";
        p_1 = std::make_shared<Player>(name_1);
        p_2 = std::make_shared<Player>(p_name);
        game_continues = true;

        /* Creating and shuffling the deck, then doing the first deal */
        game_deck = std::make_shared<Deck>();
        game_deck->shuffle();
        auto first_cards = game_deck->intial_deal();
        p_1->add_cards(first_cards.first);
        p_2->add_cards(first_cards.second);

        std::cout<<"\nYour hand is as follows";
        p_2->show_hand();
        std::cout<<"\nPress any key to continue\n";

        std::cin>>dummy;

        int total_hands = 0;
        do {
            computer_turn();
            if(game_continues == false) {
                break;
            }
            player_turn();
            ++total_hands;
            if(game_continues == false) {
                break;
            }
        } while(game_continues);

        std::cout<<"\nThanks for playing!";

    }

    void
    computer_turn() {
        /* Seeding the RNG */
        std::cout<<RED;
        std::cout<<"\n\n\n------------------------------------";
        std::cout<<CYAN;
        std::cout<<"\nIT IS THE COMPUTER'S TURN";
        std::cout<<RED;
        std::cout<<"\n------------------------------------";
        std::cout<<CYAN;
        srand(time(NULL));
        std::vector<std::string> card_list = p_1->legal_cards();
        int choice = rand()%(card_list.size() - 1);
        std::cout<<"\nTHE COMPUTER ASKS IF YOU HAVE ANY ";
        std::cout<<MAGENTA;
        std::cout<<card_list.at(choice)<<"\'s";
        auto new_cards = p_2->card_query(card_list.at(choice));
        std::cout<<RED;
        if(new_cards.size() > 0) {
            std::cout<<"\nYou have "<<new_cards.size()<<" "<<card_list.at(choice);
            if(new_cards.size() > 1 || new_cards.size() == 0) {
                std::cout<<"\'s";
            }
            std::cout<<" that you must give to the computer!";

            p_1->add_cards(new_cards);
        } else {
            std::cout<<"\nYou have no "<<card_list.at(choice)<<"\'s, computer must go fish!";
            auto new_card = game_deck->deal_top();
            p_1->add_card(new_card);
        }
        std::cout<<RESET;
        p_1->check_pairs();
        if(p_1->get_pairs() > 6) {
            std::cout<<CYAN;
            std::cout<<"\nTHE COMPUTER HAS "<<p_1->get_pairs()<<" SETS OF CARDS. YOU HAVE LOST!";
            game_continues = false;
        }
    }

    void
    player_turn() {
//        auto score = [] (const std::string& a, const std::string& b) {return converter[a] < converter[b];};
        std::cout<<GREEN;
        std::cout<<"\n\n\n------------------------------------";
        std::cout<<MAGENTA;
        std::cout<<"\nIT IS YOUR TURN";
        std::cout<<GREEN;
        std::cout<<"\n------------------------------------";
        std::cout<<RESET;
        std::cout<<"\nYour current hand is: ";
        p_2->show_hand();
        std::vector<std::string> card_list = p_2->legal_cards();
//        std::sort(card_list.begin(), card_list.end());
        std::cout<<"\nWhich card would you like to ask the computer for?";
        int choice_index = 1, player_choice = 0;
        for(const auto& cards : card_list){
            std::cout<<"\n"<<choice_index<<"....."<<cards;
            ++choice_index;
        }
        std::cout<<"\n";
        bool choice_good = false;
        do {
            std::cin>>player_choice;
            if(player_choice > 0 and player_choice <= card_list.size()) {
                choice_good = true;
            } else {
                std::cout<<"\nError! The choice must be between 1 and "<<card_list.size();
            }
        } while (!choice_good);

        auto new_cards = p_1->card_query(card_list.at(player_choice - 1));

        if(new_cards.size() > 0 ) {
            std::cout<<GREEN;
            std::cout<<"\nThe computer has "<<new_cards.size()<<" "<<card_list.at(player_choice - 1);
            if(new_cards.size() > 1 || new_cards.size() == 0) {
                std::cout<<"\'s";
            }
            std::cout<<" to give to you!";
            p_2->add_cards(new_cards);
            std::cout<<RESET;
        } else {
            std::cout<<GREEN;
            std::cout<<"\nThe computer has no "<<card_list.at(player_choice - 1)<<"\'s, go fish!";
            std::cout<<"\nYou have pulled the ";
            std::cout<<CYAN;
            auto new_card = game_deck->deal_top();
            p_2->add_card(new_card);
            std::cout<<new_card->get_name()<<RESET;
        }
        p_2->check_pairs();
        if(p_2->get_pairs() > 6) {
            std::cout<<GREEN;
            std::cout<<"\nYou have "<<p_2->get_pairs()<<" sets of cards, you win!";
            std::cout<<RESET;
            game_continues = false;
        }
        std::cout<<"\nYour current hand is: ";
        p_2->show_hand();
        std::string dummy;
        std::cout<<"\nPress any key to continue\n";
        std::cin>>dummy;
    }
};

#endif //GOFISH_GAME_H