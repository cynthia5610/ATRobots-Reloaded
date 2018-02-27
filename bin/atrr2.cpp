#include <iostream>
#include <string>

#include "types.hh"
#include "atrrfunc.hh"

using namespace std;

int main(int argc, char *argv[]){
	//loop variables
	int i, j, k, l, n, w;
	if(matches > 0){
		for(i = 0; i < num_robots; i++){
			bout;
		}
	}

	if(matches > 1){
		cout << endl;
		cout << endl;

		cout << "Bout Complete! (" << matches << " matches)" << endl;

		k = 0;
		w = 0;

		for(i = 0; i < num_robots; i++){
			//with robot[i]^ do
			if(wins = w){
				k++;
			}
			if(wins > w){
				k = 1;
				n = i;
				w = wins;
			}
			cout << "Robot           Wins  Matches  Kills  Deaths    Shots" << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
	}
}

string operand (int n, int m)
{
    string s;
    s = cstr(n);
    switch(m & 7)
    {
        case 1: s = "@" + s; break;
        case 2: s = ":" + s; break;
        case 3: s = "$" + s; break;
        case 4: s = "!" + s; break;
        default: s = cstr(n); break;
    }
    if((m & 8) > 0)
    {
        s = "[" + s + "]";
    }
    return s;
}


string mnemonic (int n, int m)
{
	string s;
	s = cstr(n);
	if(m == 0)
	{
		switch(n)
		{
			case 0:  s = "NOP"; break;
   			case 1:  s = "ADD"; break;
   			case 2:  s = "SUB"; break;
   			case 3:  s = "OR"; break;
 		 	case 4:  s = "AND"; break;
   			case 5:  s = "XOR"; break;
   			case 6:  s = "NOT"; break;
			case 7:  s = "MPY"; break;
        	case 8:  s = "DIV"; break;
   			case 9:  s = "MOD"; break;
      		case 10:  s = "RET"; break; 
   			case 11:  s = "CALL"; break; 
			case 12:  s = "JMP"; break;
   			case 13:  s = "JLS"; break;
   			case 14:  s = "JGR"; break;
   			case 15:  s = "JNE"; break;
			case 16:  s = "JE"; break;
   			case 17:  s = "SWAP"; break;
   			case 18:  s = "DO"; break;
   			case 19:  s = "LOOP"; break;
			case 20:  s = "CMP"; break;
   			case 21:  s = "TEST"; break;
   			case 22:  s = "MOV"; break;
   			case 23:  s = "LOC"; break;
			case 24:  s = "GET"; break;
         	case 25:  s = "PUT"; break;
   			case 26:  s = "INT"; break;
   			case 27:  s = "IPO"; break;
			case 28:  s = "OPO"; break;
   			case 29:  s = "DELAY"; break;
   			case 30:  s = "PUSH"; break;
   			case 31:  s = "POP"; break;
			case 32:  s = "ERR"; break;
   			case 33:  s = "INC"; break;
   			case 34:  s = "DEC"; break;
   			case 35:  s = "SHL"; break;
			case 36:  s = "SHR"; break;
  	 	   	case 37:  s = "ROL"; break;
 			case 38:  s = "ROR"; break;
         	case 39:  s = "JZ"; break;
  			case 40:  s = "JNZ"; break;
   			case 41:  s = "JGE"; break;
   			case 42:  s = "JLE"; break;
  		 	case 43:  s = "SAL"; break;
   			case 44:  s = "SAR"; break;
   			case 45:  s = "NEG"; break;
   			case 46:  s = "JTL"; break;
   			default:  s = "XXX"; break;
		}
	}
	else
	{
		s = operand(n,m);
	}
	return s;
}

void log_errors(string ov, int n, int i){

}
