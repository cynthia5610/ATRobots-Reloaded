#include <iostream>
#include <string>
#include "atrr2.cpp"
#define MACCHIATO_MAIN
#include "Macchiato.h"

using namespace Macchiato;

void readStats(std::string robotName);

void readStats(std::string robotName){
    size_t pos = 0;
    string line;
    string token;

    string endString = "#END";
    string delimiter = "=";

    string scanner = "#CONFIG scanner",
           weapon = "#CONFIG weapon",
           armor = "#CONFIG armor",
           engine = "#CONFIG engine",
           heatsinks = "#CONFIG heatsinks",
           mines = "#CONFIG mines",
           shield = "#CONFIG shield";

    string scannerVal,
           weaponVal,
           armorVal,
           engineVal,
           heatsinksVal,
           minesVal,
           shieldVal;

    ifstream robotFile (robotName);
    if(robotFile.is_open()){
        while(getline(robotFile, line) && line != "#END"){
            if((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0, pos);
                if(token == scanner){
                    scannerVal = line.erase(0, pos + delimiter.length());
                }
                else if(token == weapon){
                    weaponVal = line.erase(0, pos + delimiter.length());
                }
                else if(token == armor){
                    armorVal = line.erase(0, pos + delimiter.length());
                }
                else if(token == engine){
                    engineVal = line.erase(0, pos + delimiter.length());
                }
                else if(token == heatsinks){
                    heatsinksVal = line.erase(0, pos + delimiter.length());
                }
                else if(token == mines){
                    minesVal = line.erase(0, pos + delimiter.length());
                }
                else if(token == shield){
                    shieldVal = line.erase(0, pos + delimiter.length());
                }
            }
        }
        int numScannerVal = stoi(scannerVal),
            numWeaponVal = stoi(weaponVal),
            numEngineVal = stoi(engineVal),
            numArmorVal = stoi(armorVal),
            numHeatsinksval = stoi(heatsinksVal),
            numMinesVal = stoi(minesVal),
            numShieldVal = stoi(shieldVal);
        
        if(numScannerVal +
           numWeaponVal +
           numArmorVal +
           numEngineVal +
           numHeatsinksval +
           numMinesVal +
           numShieldVal
           > 12){
               prog_error(27, "\0");
           }
           
           if(numScannerVal > 5)
           prog_error(28, scanner.c_str());
           if(numWeaponVal > 5)
           prog_error(28, weapon.c_str());
           if(numEngineVal > 5)
           prog_error(28, engine.c_str());
           if(numArmorVal > 5)
           prog_error(28, armor.c_str());
           if(numHeatsinksval > 5)
           prog_error(28, heatsinks.c_str());
           if(numMinesVal > 5)
           prog_error(28, mines.c_str());
           if(numShieldVal > 5)
           prog_error(28, shield.c_str());
    }
    else{
        prog_error(8, "\0");
    }
    robotFile.close();

}
