#ifndef AUTHORIZED_CARDS_H
#define AUTHORIZED_CARDS_H

#include <Arduino.h>

struct CardInfo {
    String cardUID;
    String userName;
};

const int numAuthorizedCards = 17; // Specify the number of authorized cards

struct CardInfo authorizedCards[] = {
    {"69f784c2", "Antonio Sant'Ana"}, //16 + "\n"
    {"f94288c1", "Arthur Bandeira "},
    {"c6c2005c", "Arthur Fiorio   "},
    {"897086c2", "Bernardo Canal  "},
    {"f90475c1", "Bruno Rodrigues "},
    {"9ba84e43", "Daudson Andrade "},
    {"1774867b", "Enzo Giacomin   "},
    {"c7a2767b", "Gislaine Nunes  "},
    {"97cf667b", "Guilherme Ramos "},
    {"e5309085", "Lais Decote     "},
    {"87e9817a", "Luca Jacentink  "},
    {"9a0f733c", "Marina Noventa  "},
    {"7786707b", "Matheus Vieira  "},
    {"37026d7b", "Milena Plantickow"}, //16 + "\n"
    {"8742787b", "Patrick Catrinck"},
    {"99db86c1", "Tiara Smarssaro "},
    {"f93a88c1", "Viktor Kamei    "},
};

#endif
