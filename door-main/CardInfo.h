#ifndef AUTHORIZED_CARDS_H
#define AUTHORIZED_CARDS_H

#include <Arduino.h>

struct CardInfo {
    String cardUID;
    String userName;
};

const int numAuthorizedCards = 2; // Specify the number of authorized cards

CardInfo authorizedCards[] = {
    {"9ba84e43", "Paquetá Mineiro"},
    {"e5309085", "Ger Mancano"}
};

#endif
