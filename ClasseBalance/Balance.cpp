/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Balance.cpp
 * Author: bguitton
 * 
 * Created on 22 mars 2021, 09:20
 */

#include "Balance.h"
#define TAILLEMAX 11

Balance::Balance(int dout, int sck, int gain) {
    tarage = false;

    leHX711 = new HX711();


    leHX711->begin(dout, sck, gain);



}

Balance::Balance(const Balance& orig) {
}

Balance::~Balance() {
    delete leHX711;
}

float Balance::Peser() {


    float tab[TAILLEMAX];
    float reserve;
    for (int i = 0; i < TAILLEMAX; i++) {
        tab[i] = (leHX711->get_units(1));
    }

    for (int n = 0; n < TAILLEMAX; n++) {
        for (int p = 0; p < TAILLEMAX; p++) {
            if (tab[n] < tab[p]) {
                reserve = tab[n];
                tab[n] = tab[p];
                tab[p] = reserve;
            }
        }
    }

    return tab[5] / 1000;



}

void Balance::TarerLaBalance() {


    leHX711->tare();
    tarage = true;
    offset = leHX711->get_offset();
    


}

float Balance::EtalonnerLaBalance(float poidEtalon) {

    float scale = (leHX711->read_average(10) - leHX711->get_offset()) / (poidEtalon);

    leHX711->set_scale(scale);
    scale = leHX711->get_scale();
    //Serial.println(leHX711->get_offset());

    return leHX711->get_scale();
}

bool Balance::TarageEffectuer() { // vérification si le tarage à été effectuer avant l'étalonage
    return tarage;
}

float Balance::ObtenirOffset() { // récuperation du coef offset
    return leHX711->get_offset();
}

float Balance::ObtenirScale() { // récuperation du coef scale
    return leHX711->get_scale();
}

void Balance::ConfiguerOffset(float _offset) {
    Serial.print(" offset fonction config: ");
    Serial.println(_offset);


    leHX711->set_offset(_offset);
}

void Balance::ConfiguerScale(float _scale) {
    Serial.print(" scale fonction config: ");
    Serial.println(_scale);

    leHX711->set_scale(_scale);
}