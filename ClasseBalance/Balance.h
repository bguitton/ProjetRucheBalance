/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Balance.h
 * Author: bguitton
 *
 * Created on 22 mars 2021, 09:20
 */

#ifndef BALANCE_H
#define BALANCE_H
#include "HX711.h"
#include<Arduino.h>
#include <soc/rtc.h>
#include <EEPROM.h>
class Balance {
public:
    Balance(int dout = 26, int sck = 25, int gain = 64);
    Balance(const Balance& orig);
    virtual ~Balance();
    void TarerLaBalance();
    float EtalonnerLaBalance(float poidEtalon);
    float ObtenirScale();
    float ObtenirOffset();
    void ConfiguerOffset(float _offset);
    void ConfiguerScale(float _scale);
    float Peser();
    bool TarageEffectuer();
  
private:

    HX711 *leHX711;
    bool tarage;
    float masse;
    float offset;
    float scale;
    int dout;
    int sck;


};

#endif /* BALANCE_H */

