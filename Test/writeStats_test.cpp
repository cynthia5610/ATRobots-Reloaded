
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include "types.hh"

using namespace std;

void writeStats(string,string,string);
void readStats(string);

void readStats(string robotName){
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
            numScannerVal = stoi(scannerVal),
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
           > 12)/*{
               prog_error(21, robotName.c_str());
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
    */
    robotFile.close();
    return;
}
}

void writeStats(string robotName, string intoken, string value){
    if(intoken == "scanner"){
        intoken = scanner;
    }
    else if(intoken == "weapon"){
        intoken = weapon;
    }
    else if(intoken == "armor"){
        intoken = armor;
    }
    else if(intoken == "engine"){
        intoken = engine;
    }
    else if(intoken == "heatsinks"){
        intoken = heatsinks;
    }
    else if(intoken == "mines"){
        intoken = mines;
    }
    else if(intoken == "shield"){
        intoken = shield;
    }
    ifstream robotFile;
    robotFile.open(robotName.c_str());
    ofstream tempRobotFile (tempFile);
    if(robotFile.is_open()){
        while(getline(robotFile, line)){
            if((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0, pos);
                if(intoken == token){
                    line = line.erase(line.size()-1, line.size()-2);
                    line = line.append(value);
                    tempRobotFile << line << endl;
                }
                else{
                    tempRobotFile << line << endl;
                }
            }
            else{
                tempRobotFile << line << endl;
            }
        }
    }
    else{
        remove(tempFile.c_str());
    }
    robotFile.close();
    tempRobotFile.close();
    remove((robotName.c_str()));
    rename(tempFile.c_str(), robotName.c_str());
    //Error Check
    readStats(robotName);
    return;
}

int main()
{
   
writeStats("CIRCLES.AT2","scanner","3");
writeStats("CIRCLES.AT2","scanner","4");
writeStats("CIRCLES.AT2","scanner","5");
writeStats("CIRCLES.AT2","scanner","6");

cout << " " << endl;

cout << "CIRCLES.AT2 should now have it's scanner set to 5. If it is set to 6 this is an issue and writeStats does not have error catching" << endl;
cout << " " << endl;

readStats("CIRCLES.AT2");

return 0;

}