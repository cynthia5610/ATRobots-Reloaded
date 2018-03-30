#include <iostream>
#include <fstream>
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
void init(int ParamCount, char *Paramstr);
char* operand (int n, int m);
char* mnemonic (int n, int m);
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
void prog_error(int n, char* ss);
void init_robot(int n);
void compile(int n, char* filename);
void robot_config(int n);
void create_robot(int n, char* filename);
void parse_param(char * s);

config_rec config;
prog_type code;

void init_missiles(double xx, double yy, double xxv, double yyv, int dir, int s, int blast, bool ob);
void shutdown();



int main(int argc, char *argv[]){

    //move the robot array up by two to account for the negative index
	robot += 2;

    //send the robots & flags
	init(argc, *argv);

    //set number of matches -- currently hard coded
	matches = 2;
	
	//loop variables
	int i, j, k, l, n, w;
	
	//turning off graphics
	graphix = false;
	n = 0;

    //inicialize robots
	init_robot(n);
	
    //if matches > 0, run fights
	if(matches > 0){
		for(i = 0; i < matches; i++){
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
			if(robot[i]->wins == w){
				k++;
			}
			if(robot[i]->wins > w){
				k = 1;
				n = i;
				w = robot[i]->wins;
			}
		}
		cout << "Robot           		Wins   Matches   Kill   Deaths   Shots" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		for(i = 0; i < num_robots; i++){
			cout << argv[i + 1] << 
			setw(24) << robot[i]->wins << 
			setw(8) << robot[i]->trials << 
			setw(8) << robot[i]->kills <<
			setw(8) << robot[i]->deaths <<
			setw(8) << robot[i]->shots_fired << 
			endl;
		}
		cout << endl;

		if(k == 1){
			cout << "Robot #" << n+1 << " " << robot[n]->fn << " wins the bout! (Score: " << w << "/" << matches << ")" << endl;
		}
		else{
			cout << "There is no clear victor!" << endl;
		}
	}
    shutdown();
}

void init(int ParamCount, char *ParamStr)
{
    int i;
    if(debugging_compiler || compile_by_line || show_code)
    {
        cout << "!!! Warning !!! Compiler Debugging enabled !!!" << endl; //flush key; read key;
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
    srand(time(NULL));
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
    cout << "\033[36m" << progname << " " << version << " " << "\033[0m" <<endl;
    cout << "\033[36m" << cnotice1 << "\033[0m" << endl;
    cout << "\033[36m" << cnotice2 << "\033[0m" << endl;
    if(!registered) //ATRFUNC :: Boolean
    {
        cout << "\033[31m" << "Unregistered version" << "\033[0m" << endl;
    }
    else cout << "\033[31m" << "Resgister to: " << reg_name << "\033[0m" << endl;
    
    cout << endl;
    
    delete_compile_report(); //ATR2
    if(ParamCount > 0)
    {
        ParamStr++;
        for(i = 0; i < ParamCount; i++)
        {
            parse_param(ParamStr); //ATR2(ATRFUNC(ATRFUNC(SYSTEM::namespace))) *4
            ParamStr++;
        }
    }
    else prog_error(5," "); //ATR2
    temp_mode = step_mode;
    if(logging_errors)
    {
        for(i = 0; i < num_robots; i++)
        {
            robot[i]->errorlog.open(strcat(base_name(robot[i]->fn), ".ERR'"));
        }
    }
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
        robot[i]->mem_watch = 128;
        reset_hardware(i); //ATR2
        reset_software(i); //ATR2
    }
    if(graphix) setscreen();
    if (graphix && step_mode > 0) init_debug_window();
    if(!graphix)
    {
        //textcolor(7);
         cout << "\033[36m" <<"\r" << "Match " << played << "/" << matches << ", Battle in progress..." << "\033[0m" << endl;
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
			if(robot[i]->armor > 0){
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
				if(robot[i]->mine[k].yield > 0){
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
			if(!robot[0]->is_locked){
				if(!graphix){
					toggle_graphix();
				}
				if(robot[0]->armor > 0){
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

char* operand (int n, int m)
{
    char* s;
    s = cstr(n);
    switch(m & 7)
    {
        case 1: strcpy(s, strcat("@", s)); break;
        case 2: strcpy(s, strcat(":", s)); break;
        case 3: strcpy(s, strcat("$", s)); break;
        case 4: strcpy(s, strcat("!", s)); break;
        default: s = cstr(n); break;
    }
    if((m & 8) > 0)
    {
        strcpy(s,strcat("[",strcat(s,"]"))); //s = "[" + s + "]";
    }
    return s;
}


char* mnemonic (int n, int m)
{
	char* s;
	s = cstr(n);
	if(m == 0)
	{
		switch(n)
		{
			case 0:  strcpy(s, "NOP"); break;
   			case 1:  strcpy(s,"ADD"); break;
   			case 2:  strcpy(s, "SUB"); break;
   			case 3:  strcpy(s, "OR"); break;
 		 	case 4:  strcpy(s, "AND"); break;
   			case 5:  strcpy(s, "XOR"); break;
   			case 6:  strcpy(s, "NOT"); break;
			case 7:  strcpy(s, "MPY"); break;
        	case 8:  strcpy(s, "DIV"); break;
   			case 9:  strcpy(s, "MOD"); break;
      		case 10:  strcpy(s, "RET"); break; 
   			case 11:  strcpy(s, "CALL"); break; 
			case 12:  strcpy(s, "JMP"); break;
   			case 13:  strcpy(s, "JLS"); break;
   			case 14:  strcpy(s, "JGR"); break;
   			case 15:  strcpy(s, "JNE"); break;
			case 16:  strcpy(s, "JE"); break;
   			case 17:  strcpy(s, "SWAP"); break;
   			case 18:  strcpy(s, "DO"); break;
   			case 19:  strcpy(s, "LOOP"); break;
			case 20:  strcpy(s, "CMP"); break;
   			case 21:  strcpy(s, "TEST"); break;
   			case 22:  strcpy(s, "MOV"); break;
   			case 23:  strcpy(s, "LOC"); break;
			case 24:  strcpy(s, "GET"); break;
         	case 25:  strcpy(s, "PUT"); break;
   			case 26:  strcpy(s, "INT"); break;
   			case 27:  strcpy(s, "IPO"); break;
			case 28:  strcpy(s, "OPO"); break;
   			case 29:  strcpy(s, "DELAY"); break;
   			case 30:  strcpy(s, "PUSH"); break;
   			case 31:  strcpy(s, "POP"); break;
			case 32:  strcpy(s, "ERR"); break;
   			case 33:  strcpy(s, "INC"); break;
   			case 34:  strcpy(s, "DEC"); break;
   			case 35:  strcpy(s, "SHL"); break;
			case 36:  strcpy(s, "SHR"); break;
  	 	   	case 37:  strcpy(s, "ROL"); break;
 			case 38:  strcpy(s, "ROR"); break;
         	case 39:  strcpy(s, "JZ"); break;
  			case 40:  strcpy(s, "JNZ"); break;
   			case 41:  strcpy(s, "JGE"); break;
   			case 42:  strcpy(s, "JLE"); break;
  		 	case 43:  strcpy(s, "SAL"); break;
   			case 44:  strcpy(s, "SAR"); break;
   			case 45:  strcpy(s, "NEG"); break;
   			case 46:  strcpy(s, "JTL"); break;
   			default:  strcpy(s, "XXX"); break;
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
	robot[n]->wins = 0;
	robot[n]->trials = 0;
	robot[n]->kills = 0;
	robot[n]->shots_fired = 0;
	robot[n]->match_shots = 0;
	robot[n]->hits = 0;
	robot[n]->damage_total = 0;
	robot[n]->cycles_lived = 0;
	robot[n]->error_count = 0;
	robot[n]->plen = 0;
	robot[n]->max_time = 0;
	robot[n]->speed = 0;
	robot[n]->arc_count = 0;
	robot[n]->sonar_count = 0;
	robot[n]->robot_time_limit = 0;
	robot[n]->scanrange = 1500;
	robot[n]->shotstrength = 1;
	robot[n]->damageadj = 1;
	robot[n]->speedadj = 1;
	robot[n]->mines = 0;

	config.scanner = 5;
	config.weapon = 2;
	config.armor = 2;
	config.engine = 2;
	config.heatsinks = 1;
	config.shield = 0;
	config.mines = 0;

	for(i = 0; i < max_ram; i++){
		robot[n]->ram[i] = 0;
	}

	robot[n]->ram[71] = 768;

	for(i = 0; i < max_code; i++){
		for(k = 0; k < max_op; k++){
			code[i].op[k] = 0;
		}

		reset_hardware(n);
		reset_software(n);
	}	
	
    return;
}

void create_robot(int n, char* filename)
{
	int i, j, k;

	//if(maxavail < sizeof(robot_rec)) - then error
	
	robot[n] = (robot_ptr) malloc(sizeof(robot_rec));
	
	init_robot(n);

	filename = uCase(filename);
	
	if(filename == base_name(filename)){
		if(filename[1] == '?'){
			filename = strcat(filename, locked_ext);
		}
		else{
			filename = strcat(filename, robot_ext);
		}
	}

	if(filename[1] == '?'){
		filename = rstr(filename, (strlen(filename) - 1));
	}

	robot[n]->fn = base_name(filename);
	compile(n, filename);
	robot_config(n);

	k = config.scanner + config.armor + config.weapon + config.engine + config.heatsinks + config.shield + config.mines;
	if(k > max_config_points){
		cout << "ERROR: To many config points" << endl;
	}

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

void init_missiles(double xx, double yy, double xxv, double yyv, int dir, int s, int blast, bool ob)
{
    int i, j, k;
    double m;
    bool sound;
    k = -1;
    //click(); Not Used.. GRAPHICS
    for(i = max_missiles; i >= 0; i--)
    {
        if(missile[i].a == 0)
            k = i;
    }
    if(k >= 0)
    {
        missile[k].source = s;
        missile[k].x = xx;
        missile[k].lx = missile[k].x;
        missile[k].y = yy;
        missile[k].ly = missile[k].y;
        missile[k].rad = 0;
        missile[k].lrad = 0;
        if(ob)
            missile[k].mult = 1.25;
        else
            missile[k].mult = 1;
        if(blast > 0)
        {
            missile[k].max_rad = blast;
            missile[k].a = 2;
        }
        else
        {
            if(s >= 0 && s <= num_robots)
                missile[k].mult = missile[k].mult * (robot[s]->shotstrength);
            m = missile[k].mult;
            if(ob)
                m = m + 0.25;
            missile[k].mspd = missile_spd * missile[k].mult;
            if(insane_missiles)
                missile[k].mspd = 100 + (50 * insanity) * missile[k].mult;
            if(s >= 0 && s <= num_robots)
            {
                //robot[s].heat , round (20 * m) liine 1831
                robot[s]->shots_fired++;
                robot[s]->match_shots++;
            }
            missile[k].a = 1;
            missile[k].hd = dir;
            missile[k].max_rad = mis_radius;
            /**DEBUG
             if(debug_info)
             {
                do
                {
                    cout << "\r" << zero_pad(game_cycle,5) << " F" << s << ": hd= " << hd << "'" << endl;
                }while(keypressed);
                flushkey;
             }
             **/
        }
    }
    //(*The following was to see if teh missile array is big enough*)
            //LINE COMMENT OUT 1842
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
    if(graph_check(n)) // and (step_mode <= 0);
    {
        if(stats_mode == 0)
        {
            //GRAPHICS
        }
        if(logging_errors)
        {
            log_error(n,i,ov);
        }
        robot[n]->error_count++;
    }
    return;
}

void prog_error(int n, char* ss)
{
    char* s;
    const char* test;
    graph_mode(false);
    //textcolor(15);
    cout << "Error #" << n << ": ";
    switch(n)
    {
        case 0: strcpy(s, ss); break;
        case 1: strcpy(s, strcat("Invalid :label - \"", strcat(ss, "\", silly mortal.\n"))); break; // sizeof(s)); s[sizeof(s) - 1] = '\0'; ???
        case 2: strcpy(s, strcat("Undefined identifier - \"", strcat(ss, "\". A typo perhaps?\n"))); break;
        case 3: strcpy(s, strcat("Memory access out of range - \"", strcat(ss, "\""))); break;
        case 4: strcpy(s, "Not enough robots for combat. Maybe we should just drive in circles.\n"); break;
        case 5: strcpy(s, "Robot names and settings must be specified. An empty arena is no fun.\n"); break;
        case 6: strcpy(s, strcat("Config file not found - \"", strcat(ss, "\""))); break;
        case 7: strcpy(s, strcat("Cannot access a config file from a config file - \"", strcat(ss, "\""))); break;
        case 8: strcpy(s, strcat("Robot not found \"", strcat(ss, "\". Perhaps you mistyped it?\n"))); break;
        case 9: strcpy(s, strcat("Insufficient RAM to load robot: \"", strcat(ss, "\"... This is not good.\n"))); break;
        case 10: strcpy(s, strcat("Too many robots! We can only handle ", strcat(cstr(max_robots+1),  "! Blah.. limits are limits.\n"))); break;
        case 11: strcpy(s, strcat("You already have a perfectly good #def for \"", strcat(ss, "\", silly.\n"))); break;
        case 12: strcpy(s, strcat("Variable name too long! (Max:",strcat(cstr(max_var_len),strcat(") \"",strcat(ss, "\""))))); break;
        case 13: strcpy(s, strcat("!Label already defined \"", strcat(ss, "\", silly.\n"))); break;
        case 14: strcpy(s, strcat("Too many variables! (Var Limit: ", strcat(cstr(max_vars), ")\n"))); break;
        case 15: strcpy(s, strcat("Too many !labels! (!Label Limit: ", strcat(cstr(max_labels), ")\n"))); break;
        case 16: strcpy(s, strcat("Robot program too long! Boldly we simplify, simplify along...\n", ss)); break;
        case 17: strcpy(s, strcat("!Label missing error. !Label #", strcat(ss, "."))); break;
        case 18: strcpy(s, strcat("!Label out of range: ", ss)); break;
        case 19: strcpy(s, strcat("!Label not found. ", ss)); break;
        case 20: strcpy(s, strcat("Invalid config option: \"", strcat(ss, "\". Inventing a new device?"))); break;
        case 21: strcpy(s, strcat("Robot is attempting to cheat; Too many config points (", strcat(ss, ")"))); break;
        case 22: strcpy(s, strcat("Insufficient data in data statement: \"", strcat(ss, "\""))); break;
        case 23: strcpy(s, strcat("Too many asterisks: \"", strcat(ss, "\""))); break;
        case 24: strcpy(s, strcat("Invalid step count: \"", strcat(ss, "\". 1-9 are valid conditions."))); break;
        case 25: strcpy(s, strcat("\"", strcat(ss, "\""))); break;
        default: strcpy(s,ss);  break;
    }
    cout << s << endl;
    exit(EXIT_FAILURE);
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

void compile(int n, char* filename)
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

void parse_param(char * s)
{
    ifstream f;
    char * fn;
    char * s1;
    bool found;
    
    found = false;
    //s = uCase(s);

    if(s == NULL) return;
    if(s[1] == '#')
    {
        fn = rstr(s,strlen(s)-1);
        if(fn == base_name(fn)) fn = strcat(fn, config_ext);
        if(!EXIST(fn)) prog_error(6,fn);
        f.open(fn);
        while(!f.eof())
        {
            //getline(f,s1); MUST FIX
            //s1 = uCase(s1);
            if(s1[1] == '#') prog_error(7,s1);
            else parse_param(s1);
        }
        f.close();
        found = true;
    }
    else if(s[1] == '/' || s[1] == '-' || s[1] == '=')
    {
        s1 = rstr(s,strlen(s)-1);
        //Debugging
        if(s1[1] == 'X')
        {
            step_mode = value(rstr(s1,strlen(s)-1));
            found = true;
            if(step_mode == 0) step_mode = 1;
            if(step_mode < 1 || step_mode > 9)
                prog_error(24,rstr(s1,strlen(s1)-1));
        }
        //Debugging end
        if(s1[1] == 'D')
        {
            game_delay = value(rstr(s1,strlen(s1)-1));
            found = true;
        }
        if(s1[1] == 'T')
        {
            time_slice = value(rstr(s1,strlen(s1)-1));
            found = true;
        }
        if(s1[1] == 'L')
        {
            game_limit = value(rstr(s1,strlen(s1)-1))*1000;
            found = true;
        }
        if(s1[1] == 'Q')
        {
            sound_on = false;
            found = true;
        }
        if(s1[1] == 'M')
        {
            matches = value(rstr(s1,strlen(s1)-1));
            found = true;
        }
        if(s1[1] == 'S')
        {
            show_source = false;
            found = true;
        }
        if(s1[1] == 'G')
        {
            no_gfx = true;
            found = true;
        }
        if(s1[1] == 'R')
        {
            report = true;
            found = true;
            if(strlen(s1) > 1)
                report_type = value(rstr(s1,strlen(s1)-1));
        }
        if(s1[1] == 'C')
        {
            compile_only = true;
            found = true;
        }
        if(s1[1] == '^')
        {
            show_cnotice = false;
            found = true;
        }
        if(s1[1] == 'A')
        {
            show_arcs = true;
            found = true;
        }
        if(s1[1] == 'W')
        {
            windoze = false;
            found = true;
        }
        if(s1[1] == '$')
        {
            debug_info = true;
            found = true;
        }
        if(s1[1] == '#')
        {
            maxcode = value(rstr(s1,strlen(s1)-1))-1;
            found = true;
        }
        if(s1[1] == '!')
        {
            insane_missiles = true;
            if(strlen(s1) > 1)
                insanity = value(rstr(s1,strlen(s1)-1));
            found = true;
        }
        if(s1[1] == '@')
        {
            old_shields = true;
            found = true;
        }
        if(s1[1] == 'E')
        {
            logging_errors = true;
            found = true;
        }
        if(insanity < 0)
            insanity = 0;
        if(insanity > 15)
            insanity = 15;
    }
    else if(s[1] == ';') found = true;
    else if(num_robots < max_robots && s != NULL)
    {
        num_robots++;
        create_robot(num_robots,s);
        found = true;
        if(num_robots == max_robots)
            cout << "Maximum number of robots reached." << endl;
    }
    else prog_error(10,"");
    if(!found) prog_error(8,s);
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
 */

void process_keypress(char c)
{
    return;
}

void shutdown()
{
    int i, j, k;
    graph_mode(false);
    if(show_cnotice)
    {
        //textcolor(3)
        cout << endl;
        cout << "\033[31;1;4m" << progname << " " << version << "\033[0m" << endl;
        cout << cnotice1 << endl;
        cout << cnotice2 << endl;
        cout << cnotice3 << endl;
    }
    //textcolor(7);
    if(!registered)
    {
        //textcolor(4);
        cout << "Unregistered version" << endl;
    }
    else
    {
        cout << "Registered to: " << reg_name << endl;
    }
    //textcolor(7);
    /**if(logging_errors) //LOGGING ERRORS
     {
     for(i = 0; i < num_robots; i++)
     {
     cout << "Robot error-log created: ", base_name(robot[i].fn) + ".ERR" << endl;
     close(robot[i].errorlog);
     }
     }**/
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
            if(robot[n]->armor > 0)
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

char* victor_string(int k, int n)
{
    char* s;
    if(k == 1) strcpy(s, strcat("Robot #", strcat(cstr(n+1), strcat(" (", strcat(robot[n]->fn, ") wins!")))));
    if(k == 0) strcpy(s, "Simultaneous destruction, match is a tie.");
    if(k > 1) strcpy(s, "No clear victor, match is a tie.");
    return s;
}

void show_statistics()
{
    int i, j, k, n, sx, sy;
    if(!windoze) return;
    if(graphix)
    {
        //graphics stuff
    }
    else
    {
        //textcolor(15);
        cout << "\r" << space(79) << "\r" << endl;
        cout << "Match " << played << "/" << matches << " results:" << endl;
        cout << endl;
        cout << "Robot            Scored   Wins  Matches  Armor  Kills  Deaths    Shots" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        n = -1; k = 0;
        for(i = 0; i < num_robots; i++)
        {
            if(robot[i]->armor > 0 || robot[i]->won)
            {
                k++;
                n = i;
            }
        }
        for(i = 0; i < num_robots; i++)
        {
            //textcolor(robot_color(i));
            if(k == 1 && n == i)
                j = 1;
            else
                j = 0;
            cout << addfront(cstr(i+1),2) << " - " << addrear(robot[i]->fn,15) << cstr(j) << addfront(cstr(robot[i]->wins),8)
            << addfront(cstr(robot[i]->trials),8) << addfront(cstr(robot[i]->armor)+'%',9) << addfront(cstr(robot[i]->kills),7)
            << addfront(cstr(robot[i]->deaths),8) << addfront(cstr(robot[i]->match_shots),9) << endl;
        }
        //textcolor(15); //white
        cout << endl;
        cout << victor_string(k,n) << endl;
        cout << endl;
        //{writeln('Press any key to continue...'); readkey;}
    }
    return;
}

void write_report()
{
    return;
}

