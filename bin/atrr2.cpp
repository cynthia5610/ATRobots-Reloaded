#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

#include "types.hh"
#include "atrrfunc.hh"
#include "filelib.hh"

using namespace std;

/*
FUNCTION HEADERS
*/

void bout();
void init();
string operand (int n, int m);
string mnemonic (int n, int m);
void process_keypress(char c);
void graph_mode(bool on);
void toggle_graphix();
void do_mine(int n, int m);
void do_missile(int n);
void do_robot(int n);
void draw_robot(int n);
void reset_hardware(int n);
void reset_software(int n);
void setscreen();
void init_debug_window();
bool gameover();
void delete_compile_report();
void write_compile_report();
void prog_error(int n, string ss);
void init_robot(int n);




int main(int argc, char *argv[]){

	robot += 2;
	init();

	matches = 2;
	num_robots = 2;
	
	//loop variables
	int i, j, k, l, n, w;
	
	//turning off graphics
	graphix = false;
	n = 0;
	init_robot(n);
	
	if(matches > 0){
		for(i = 0; i < num_robots; i++){
			bout();
		}
	}

	if(matches > 1){
		cout << endl;
		cout << endl;

		cout << "Bout Complete! (" << matches << " matches)" << endl;

		k = 0;
		w = 0;

		for(i = 0; i < num_robots; i++){
			if(robot[i].wins == w){
				k++;
			}
			if(robot[i].wins > w){
				k = 1;
				n = i;
				w = robot[i].wins;
			}
		}
		cout << "Robot           		Wins   Matches   Kill   Deaths   Shots" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		for(i = 0; i < num_robots; i++){
			cout << argv[i + 1] << 
			setw(24) << robot[i].wins << 
			setw(8) << robot[i].trials << 
			setw(8) << robot[i].kills <<
			setw(8) << robot[i].deaths <<
			setw(8) << robot[i].shots_fired << 
			endl;
		}
		cout << endl;

		if(k == 1){
			cout << "Robot #" << n+1 << robot[n].fn << " wins the bout! (Score: " << w << "/" << matches << ")" << endl;
		}
		else{
			cout << "There is no clear victor!" << endl;
		}
	}
}

void init()
{
    int i;
    if(debugging_compiler || compile_by_line || show_code)
    {        cout << "!!! Warning !!! Compiler Debugging enabled !!!" << endl; //*1
    }
    step_mode = 0;
    logging_errors = false;
    stats_mode = 0;
    insane_missiles = false;
    insanity = 0;
    delay_per_sec = 0;
    windoze = true;
    graphix = false;
    no_gfx = false;
    sound_on = true;
    timing = true;
    matches = 1;
    played = 0;
    old_shields = false;
    quit = false;
    compile_only = false;
    show_arcs = false;
    debug_info = false;
    show_cnotice = true;
    show_source = true;
    report = false;
    kill_count = 0;
    maxcode = max_code;
    //make_tables(); // ATRFUNC;
    srand(time(NULL)); //*2
    num_robots = -1;
    game_limit = 100000;
    game_cycle = 0;
    game_delay = default_delay;
    time_slice = default_slice;
    for(i = 0; i < max_missiles; i++)
    {
        missile[i].a = 0;
        missile[i].source = -1;
        missile[i].x = 0;
        missile[i].y = 0;
        missile[i].lx = 0;
        missile[i].ly = 0;
        missile[i].mult = 1;
    }
    
    registered = false; //ATRFUNC
    reg_name = "Unregistered"; //ATRFUNC/ATRT
    reg_num = 65535; //ATRFUNC/ATRT //$FFFF
    //check_registration(); //ATRFUNC/ATRT
    
    cout << endl;
    cout << progname << " " << version << " " << endl;
    cout << cnotice1 << endl;
    cout << cnotice2 << endl;
    if(!registered) //ATRFUNC :: Boolean
    {
        cout << "Unregistered version" << endl;
    }
    else cout << "Resgister to: " << reg_name << endl;
    
    cout << endl;
    
    delete_compile_report(); //ATR2
    /**if(ParamCount() > 0)
    {
        for(i = 0; i < ParamCount(); i++)
        {
            parse_param(btrim(ucase(ParamStr(i)))); //ATR2(ATRFUNC(ATRFUNC(SYSTEM::namespace))) *4
        }
    }
    else**/ prog_error(5," "); //ATR2
    temp_mode = step_mode;
    /**if(logging_errors)
    {
        for(i = 0; i < num_robots; i++)
        {
            assign(robot[i]->errorlog, base_name(fn)+".ERR"); //base_name FILELIB //Need to see for assign func *5
            rewrite(errorlog); //OPENS file for writing
        }
    }**/
    if(compile_only) write_compile_report(); //ATR2
    if(num_robots < 1) prog_error(4," "); //ATR2
    
    if(!no_gfx) graph_mode(true); //ATR2
    
    //---Fix-ups---//
    if(matches > 100000) matches = 100000;
    if(matches < 1) matches = 1;
    if(game_delay > 1000) game_delay = 1000;
    if(game_delay < 0) game_delay = 0;
    if(time_slice > 100) time_slice = 100;
    if(time_slice < 1) time_slice = 1;
    if(game_limit < 0) game_limit = 0;
    if(game_limit > 100000) game_limit = 100000;
    if(maxcode < 1) maxcode = 1;
    if(maxcode > max_code) maxcode = max_code;
    
    //----avoid floating pointers ----//
    for(i = num_robots+1; i < max_robots+2; i++)
    {
        robot[i] = robot[0];
    }
    robot[-1] = robot[0];
    robot[-2] = robot[0];
    
    if(!graphix)
    {
        //cout << "Freemem: " << memavail << endl; //memavail *6
        cout << endl;
    }
}
void init_bout()
{
    int i, j, k;
    game_cycle = 0;
    for(i = 0; i < max_missiles; i++)
    {
        missile[i].a = 0;
        missile[i].source = -1;
        missile[i].x = 0;
        missile[i].y = 0;
        missile[i].lx = 0;
        missile[i].ly = 0;
        missile[i].mult = 1;
    }
    for(i = 0; i < num_robots; i++)
    {
        robot[i].mem_watch = 128;
        reset_hardware(i); //ATR2
        reset_software(i); //ATR2
    }
    if(graphix) setscreen();
    if (graphix && step_mode > 0) init_debug_window();
    if(!graphix)
    {
        //textcolor(7);
         cout << "\r" << "Match " << played << "/" << matches << ", Battle in progress..." << endl;
         cout << endl;
    }
    // Comment out code Init_bout Line 3406
    return;
}

void bout()
{
	int i, j, k, n;
	char c;
	long timer;

	played++;
	init_bout();
	bout_over = false;

	if(step_mode == 0){
		step_loop = false;
	}
	else{
		step_loop = true;
	}
	step_count = -1;

	if(graphix && (step_mode > 0)){
		for(i = 0; i < num_robots; i++){
			draw_robot(i);
		}
	}

	do{
		game_cycle++;
		for(i = 0; i < num_robots; i++){
			if(robot[i].armor > 0){
				do_robot(i);
			}
		}
		for(i = 0; i < max_missiles; i++){
			if(missile[i].a > 0){
				do_missile(i);
			}
		}
		for(i = 0; i < num_robots; i++){
			for(k = 0; k < max_mines; k++){
				if(robot[i].mine[k].yield > 0){
					do_mine(i, k);
				}
			}
		}
		/*
		if(graphix && timing){
			time_delay(game_delay);
		}
		if(keypressed){
			c = uCase(readkey);
		}
		else{
		//	c = #255;
		}
		*/
		switch(c){
			case 'X':
			if(!robot[0].is_locked){
				if(!graphix){
					toggle_graphix();
				}
				if(robot[0].armor > 0){
					if(temp_mode > 0){
						step_mode = temp_mode;
					}
					else{
						step_mode = 1;
					}
					step_count = -1;
					init_debug_window();
				}
			}
			//ARTIFACT
			case '+': case '=':
			if(game_delay < 100){
				switch(game_delay){
					case 0 ... 4: game_delay = 5;
					break;
					case 5 ... 9: game_delay = 10;
					break;
					case 10 ... 14: game_delay = 15;
					break;
					case 15 ... 19: game_delay = 20;
					break;
					case 20 ... 29: game_delay = 30;
					break;
					case 30 ... 39: game_delay = 40;
					break;
					case 40 ... 49: game_delay = 50;
					break;
					case 50 ... 59: game_delay = 60;
					break;
					case 60 ... 79: game_delay = 75;
					break;
					case 80 ... 100: game_delay = 100;
					break;
				}
			}
			case '-': case '_':
			if(game_delay > 0){
				switch(game_delay){
					case 0 ... 5: game_delay = 0;
					break;
					case 6 ... 10: game_delay = 5;
					break;
					case 11 ... 15: game_delay = 10;
					break;
					case 16 ... 20: game_delay = 15;
					break;
					case 21 ... 30: game_delay = 20;
					break;
					case 31 ... 40: game_delay = 30;
					break;
					case 41 ... 50: game_delay = 40;
					break;
					case 51 ... 60: game_delay = 50;
					break;
					case 61 ... 75: game_delay = 60;
					break;
					case 76 ... 100: game_delay = 75;
					break;
				}
			}
			case 'G': toggle_graphix();
			default: process_keypress(c);
		}
		//flushkey();

		if(game_delay < 0){
			game_delay = 0;
		}
		if(game_delay > 100){
			game_delay = 100;
		}

		switch(game_delay){
			case 0 ... 1: k = 100;
			case 2 ... 5: k = 50;
			case 6 ... 10: k = 25;
			case 11 ... 25: k = 20;
			case 26 ... 40: k = 10;
			case 41 ... 70: k = 5;
			case 71 ... 32787: k = 1;
			default: k = 10;
		}
		
		if(!graphix){
			k = 100;
		}
		
	}while(gameover() || bout_over);

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

int max_shown()
{
    int max;
    switch(stats_mode)
    {
        case 1: max = 12; break;
        case 2: max = 32; break;
        default: max = 6; break;
    }
    return max;
}


/*
----- GRAPHICS FUNCTIONS ----
*/

void graph_mode(bool on)
{
	return;
}

void toggle_graphix()
{
	graph_mode(!graphix);
	if(!graphix)
    {
		cout << "Match " << played << "/" << matches << ", Battle in progress..." << endl;
	}
	return;
}

bool graph_check(int n)
{
    return false; // Set to false to not use graphics
}

void robot_graph(int n)
{
    return;
}

void update_armor(int n)
{
    return;
}

void update_heat(int n)
{
    return;
}

void update_lives(int n)
{
    return;
}

void update_cycle_window()
{
    if(!graphix)
    {
    cout << "\r" << "Match " << played << "/" << matches << ", Cycle: " << zero_pad(game_cycle,9);
    }
    else
    {
        cout << endl;
    }
    return;
}

void setscreen()
{
    return;
}

void draw_robot(int n)
{
    return;
}

void begin_window()
{
    return;
}

/* 
------ ROBOT FUNCTIONS -----
Empty and return void in order to create sitting duck
*/

void do_mine(int n, int m)
{
	return;
}

void do_missile(int n)
{
	return;
}

void do_robot(int n)
{
	return;
}

void init_robot(int n)
{
	int i, j, k, l;
	robot[n].wins = 0;
	robot[n].trials = 0;
	robot[n].kills = 0;
	robot[n].shots_fired = 0;
	robot[n].match_shots = 0;
	robot[n].hits = 0;
	robot[n].damage_total = 0;
	robot[n].cycles_lived = 0;
	robot[n].error_count = 0;
	robot[n].plen = 0;
	robot[n].max_time = 0;
    return;
}

void create_robot(int n, string filename)
{
    return;
}

void init_mine(int n, int detectrange, int size)
{
    return;
}

int count_missiles()
{
    return 0;
}

void init_missiles(float xx, float yy, float xxv, float yyv, int dir, int s, int blast, bool ob)
{
    return;
}

void damage(int n, int d, bool physical)
{
    return;
}

int scan(int n)
{
    return 0;
}

void score_robots()
{
    return;
}

/*
 ------ COMPILE/PARSING/CONFIG FUNCTIONS -----
 Empty and return void
 */

void log_error(int n, int i, string ov)
{
    return;
}

void robot_error(int n, int i, string ov) //Contains graphics
{
    return;
}

void prog_error(int n, string ss)
{
    return;
}

void print_code(int n, int p)
{
    return;
}

void parse1(int n, int p, parsetype s)
{
    return;
}

void check_plen(int plen)
{
    return;
}

void compile(int n, string filename)
{
    return;
}

void robot_config(int n)
{
    return;
}

void reset_software(int n)
{
    return;
}

void reset_hardware(int n)
{
    return;
}

void parse_param(string s)
{
    return;
}

void delete_compile_report()
{
    return;
}

void write_compile_report()
{
    return;
}

int get_from_ram(int n, int i, int j)
{
    return 0;
}

int get_val(int n, int c, int o)
{
    return 0;
}

void put_val(int n, int c, int o, int v)
{
    return;
}

void push(int n, int v)
{
    return;
}

int pop(int n)
{
    return 0;
}

int find_label(int n)
{
    return 0;
}

void com_transmit(int n, int chan, int data)
{
    return;
}

int com_receive(int n)
{
    return 0;
}

int in_port(int n, int p, int time_used)
{
    return 0;
}

void out_port(int n, int p, int v, int time_used)
{
    return;
}

void call_int(int n, int int_num, int time_used)
{
    return;
}

bool invalid_microcode(int n, int ip)
{
    return false;
}

void execute_instruction(int n)
{
    return;
}

/*
 ------ DEBUG FUNCTIONS -----
 Empty and return void
 */

void update_debug_bars()
{
    return;
}

void update_debug_system()
{
    return;
}

void update_debug_registers()
{
    return;
}

void update_debug_flags()
{
    return;
}

void update_debug_memory()
{
    return;
}

void update_debug_code()
{
    return;
}

void update_debug_window()
{
    return;
}

void init_debug_window()
{
    return;
}

void close_debug_window()
{
    return;
}

/*
 ------ OTHER FUNCTIONS -----
 Empty and return void
 */

void process_keypress(char c)
{
    return;
}

void shutdown()
{
    return;
}

bool gameover()
{
    int n, i, j, k, l;
    if((game_cycle >= game_limit) && (game_limit > 0))
        return true;
    if((game_cycle & 31) == 0)
    {
        k = 0;
        for(n = 0; n < num_robots; n++)
        {
            if(robot[n].armor > 0)
                k++;
        }
        if(k <= 1)
            return true;
        else
            return false;
    }
    else
        return false;
    
}

string victor_string(int k, int n)
{
    return " ";
}

void show_statistics()
{
    return;
}

void write_report()
{
    return;
}

