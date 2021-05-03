/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.ino.cpp
 * Author: bguitton
 *
 * Created on 22 mars 2021, 09:19
 */

#include <cstdlib>
#include<Arduino.h>
#include "Balance.h"
#include <soc/rtc.h>
#include <string.h>
#include <valarray>

#define EEPROM_SIZE 512

using namespace std;

const int LOADCELL_DOUT_PIN = 26;
const int LOADCELL_SCK_PIN = 25;
RTC_DATA_ATTR float offset;
RTC_DATA_ATTR float scale;
/*
 * 
 */

Balance laBalance;

void setup() {

    EEPROM.begin(EEPROM_SIZE);
    Serial.begin(115200);
    Serial.print(" offset: ");
    Serial.println(EEPROM.readDouble(0));
    laBalance.ConfiguerOffset(EEPROM.readDouble(0));
    Serial.print(" scale: ");
    Serial.println(EEPROM.readDouble(10));
    laBalance.ConfiguerScale(EEPROM.readDouble(10));
    while (!Serial.available());
    while (Serial.available()) Serial.read();

}

void loop() {

    int reponse = 0;
    float poidEtalon;

    Serial.println("1 - pour Tarer ");
    Serial.println("2 - pour Etalonner ");
    Serial.println("3 - pour Peser ");
    while (!Serial.available());


    reponse = Serial.read();
    // Serial.println(reponse);
    switch (reponse) {
        case '1':
            Serial.println("vider le plateau et appuyer sur une touche pour tarer ");
            while (!Serial.available());
            while (Serial.available()) Serial.read();
            laBalance.TarerLaBalance();
            Serial.println(laBalance.ObtenirOffset());
            Serial.println("tarage effectuer: \t\t");
            EEPROM.writeDouble(0, laBalance.ObtenirOffset());
            EEPROM.commit();
            break;
        case '2':
            if (laBalance.TarageEffectuer()) {
                Serial.println("Donnez un poids étalon en gramme (ex:400g= 400) et appuyez sur entrer ");
                while (!Serial.available());

                while (Serial.available() == 0) {
                }
                poidEtalon = Serial.parseFloat();

                Serial.println("Posez le poids choisi et  appuyez sur entrer ");
                while (!Serial.available());
                while (Serial.available()) Serial.read();
                Serial.println(poidEtalon); // affiche 4 si l'ont tape 4
                laBalance.EtalonnerLaBalance(poidEtalon);
                Serial.println(laBalance.ObtenirScale());
                EEPROM.writeDouble(10, laBalance.ObtenirScale());
                EEPROM.commit();
            } else {
                Serial.println("Vous devez tarer la balance avant de faire un etalonnage ");
            }
            break;
        case '3':
            Serial.print("masse = ");
            Serial.println(laBalance.Peser());
            
            break;
        case '4':
            Serial.print(" offset: ");
            Serial.println(laBalance.ObtenirOffset());
            Serial.print(" sclae: ");
            Serial.println(laBalance.ObtenirScale());
            break;
        default:
            Serial.println("Veuiller saisir un chiffre entre 1 et 3  ");
            break;
    }
    
    delay(500);
}


