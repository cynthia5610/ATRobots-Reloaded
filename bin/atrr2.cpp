#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <climits> //FOR INT_MAX


#include "types.hh"
#include "atrrfunc.hh"
#include "filelib.hh"

using namespace std;

/*
FUNCTION HEADERS
*/

void bout();
void init(int ParamCount, char **Paramstr);
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
void prog_error(int n, const char* ss);
void init_robot(int n);
void compile(int n, char* filename);
void robot_config(int n);
void create_robot(int n, char* filename);
void parse_param(char * s);
void init_missiles(double xx, double yy, double xxv, double yyv, int dir, int s, int blast, bool ob);
void shutdown();
char* victor_string(int k, int n);



int main(int argc, char *argv[]){

    //move the robot array up by two to account for the negative index
	robot += 2;

    //send the robots & flags
	init(argc, argv);

    //set number of matches -- currently hard coded
	//matches = 2;
	
	//loop variables
	int i, j, k, l, n, w;
	
	//turning off graphics
	graphix = false;
	n = 0;
	
    //if matches > 0, run fights
	if(matches > 0){
		for(i = 0; i < matches; i++){
			bout();
		}
	}

	if(matches > 1){
		cout << endl;
		cout << endl;

        textcolor(15);
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

		for(i = 0; i <= num_robots; i++){
            textcolor(robot_color(i));
			cout << robot[i]->fn << 
			setw(24) << robot[i]->wins << 
			setw(8) << robot[i]->trials << 
			setw(8) << robot[i]->kills <<
			setw(8) << robot[i]->deaths <<
			setw(8) << robot[i]->shots_fired << 
			endl;
		}
		cout << endl;
        textcolor(15);

		if(k == 1){ //this might have to be (k == 1);
			cout << "Robot #" << n+1 << " " << robot[n]->fn << " wins the bout! (Score: " << w << "/" << matches << ")" << endl;
		}
		else{
			cout << "There is no clear victor!" << endl;
		}
	}
    shutdown();
    textcolor(16);
}

void init(int ParamCount, char **ParamStr)
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
    matches = 0;
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
            if(ParamStr[i] == NULL) break;
            parse_param(ParamStr[i]); //ATR2(ATRFUNC(ATRFUNC(SYSTEM::namespace))) *4
        }
    }
    else prog_error(5, "\0"); //ATR2
    if(matches == 0){
        prog_error(25, "\0");
    }
    temp_mode = step_mode;
    if(logging_errors)
    {
        for(i = 0; i < num_robots; i++)
        {
            robot[i]->errorlog.open(strcat(base_name(robot[i]->fn), ".ERR'"));
        }
    }
    if(compile_only) write_compile_report(); //ATR2
    if(num_robots < 1) prog_error(4, "\0"); //ATR2
    
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
        textcolor(7);
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
        case 1: snprintf(s, strlen(s), "@");    //strcpy(s, strcat("@", s)); break;
        case 2: snprintf(s, strlen(s), ":");    //strcpy(s, strcat(":", s)); break;
        case 3: snprintf(s, strlen(s), "$");    //strcpy(s, strcat("$", s)); break;
        case 4: snprintf(s, strlen(s), "!");    //strcpy(s, strcat("!", s)); break;
        default: s = cstr(n); break;
    }
    if((m & 8) > 0)
    {
        snprintf(s, strlen(s), "[");    //s = "[" + s + "]";
        //snprintf(s, strlen(s), (const char *)s);
        snprintf(s, strlen(s), "]");  
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

	robot[n]->config.scanner = 5;
	robot[n]->config.weapon = 2;
	robot[n]->config.armor = 2;
	robot[n]->config.engine = 2;
	robot[n]->config.heatsinks = 1;
	robot[n]->config.shield = 0;
	robot[n]->config.mines = 0;

	for(i = 0; i < max_ram; i++){
		robot[n]->ram[i] = 0;
	}

	robot[n]->ram[71] = 768;

	for(i = 0; i < max_code; i++){
		for(k = 0; k < max_op; k++){
			robot[n]->code[i].op[k] = 0;
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

	k = robot[n]->config.scanner + robot[n]->config.armor + robot[n]->config.weapon + robot[n]->config.engine + robot[n]->config.heatsinks + robot[n]->config.shield + robot[n]->config.mines;
	if(k > max_config_points){
		cout << "ERROR: To many config points" << endl;
	}

    return;
}

void init_mine(int n, int detectrange, int size)
{
    int i, j, k;
    k = -1;
    for(i = 0; i < max_mines; i++)
    {
        if((robot[n]->mine[i].x < 0) || (robot[n]->mine[i].x > 1000) || (robot[n]->mine[i].y < 0) || (robot[n]->mine[i].x > 1000) || ((robot[n]->mine[i].yield <= 0) && (k < 0)))
            k = i;
    }
    if(k>=0)
    {
        robot[n]->mine[k].x = robot[n]->x; //where is the x from? Robot rec? HELP
        robot[n]->mine[k].y = robot[n]->y;
        robot[n]->mine[k].detect = detectrange;
        robot[n]->mine[k].yield = size;
        robot[n]->mine[k].detonate = false;
        //click(); ATRFUNC
    }
    return;
}

int count_missiles()
{
    int i, k;
    k = 0;
    for(i = 0; i < max_missiles; i++)
    {
        if(missile[i].a > 0)
            k++;
    }
    return k;
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
                robot[s]->heat+=round (20 * m);
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
    int i, k, h, dd;
    double m; //REAL
    if(n < 0 || n > num_robots || robot[n]->armor <= 0)
        return;
    if(robot[n]->config.shield < 3)
        robot[n]->shields_up = false;
    h = 0;
    if(robot[n]->shields_up && (!physical))
    {
        dd = d;
        if(old_shields && robot[n]->config.shield > 3)
        {
            d = 0;
            h = 0;
        }
        else
        {
            switch(robot[n]->config.shield)
            {
                case 3: d = round(dd*2/3);
                    if(d <1) d = 1;
                    h = round(dd*2/3);
                    break;
                case 4: h = trunc(dd/2);
                    d = dd-h;
                    break;
                case 5: d = round(dd*1/3);
                    if(d < 1) d = 1;
                    h = round(dd*1/3);
                    if(h < 1) h = 1;
                    break;
            }
        }
    }
    if(d < 0) d = 0;
    if(debug_info)
    {
        //LINE 1879
    }
    if(d > 0)
    {
        d = round(d*robot[n]->damageadj);
        if(d < 1) d = 1;
    }
    robot[n]->armor = robot[n]->armor - d;
    robot[n]->heat = robot[n]->heat + h;
    robot[n]->last_damage = 0;
    if(robot[n]->armor <= 0)
    {
        robot[n]->armor = 0;
        update_armor(n);
        robot[n]->heat = 500;
        update_heat(n);
        robot[n]->armor = 0;
        kill_count++;
        robot[n]->deaths++;
        update_lives(n);
       /** if(graphix && timing)
            time_delay(10); **/ //GRAPHICS
        draw_robot(n);
        robot[n]->heat = 0;
        update_heat(n);
        init_missiles(robot[n]->x,robot[n]->y,0,0,0,n,blast_circle,false);
        if(robot[n]->overburn) m = 1.3;
        else m = 1;
        for(i = 0; i < num_robots; i++)
        {
            if(i!=n && robot[i]->armor > 0)
            {
                k = round(getDistance(robot[n]->x,robot[n]->y,robot[i]->x,robot[i]->y)); //distance ATRFUNC
                if(k < blast_radius)
                    damage(i,round(abs(blast_radius-k)*m),false); //Check the math func
            }
        }
    }
    return;
}

int scan(int n)
{
    double r, d, acc;
    int dir, range, i, j, k, l, nn, xx, yy, sign;
    nn = -1;
    range = INT_MAX;
    if(!(n >= 0 && n <= num_robots)) return 0; //HELP. What do i return?
    //LINE 1921
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

void prog_error(int n, const char* ss)
{
    graph_mode(false);
    textcolor(15);
    cout << "Error #" << n << ": ";
    switch(n)
    {
        case 0: ss = ss; break; 
        case 1: cout <<"Invalid :label - \"" << ss << "\", silly mortal.\n"<< endl; break;
        case 2: cout <<"Undefined identifier - \"" << ss << "\". A typo perhaps?\n"<< endl; break;
        case 3: cout <<"Memory access out of range - \"" << ss << "\""<< endl; break;
        case 4: cout <<"Not enough robots for combat. Maybe we should just drive in circles.\n"<< endl; break;
        case 5: cout <<"Robot names and settings must be specified. An empty arena is no fun.\n"<< endl; break;
        case 6: cout <<"Config file not found - \""<< ss << "\""<< endl; break;
        case 7: cout <<"Cannot access a config file from a config file - \""<< ss <<"\""<< endl; break;
        case 8: cout <<"Robot not found \"" << ss << "\". Perhaps you mistyped it?\n"<< endl; break;
        case 9: cout <<"Insufficient RAM to load robot: \"" << ss << "\"... This is not good.\n"<< endl; break;
        case 10: cout <<"Too many robots! We can only handle " << cstr(max_robots<<1) << "! Blah.. limits are limits.\n"<< endl; break; 
        case 11: cout <<"You already have a perfectly good #def for \"" << ss << "\", silly.\n"<< endl; break;
        case 12: cout <<"Variable name too long! (Max:" << cstr(max_var_len) << ") \"" << ss << "\""<< endl; break;
        case 13: cout <<"!Label already defined \"" << ss << "\", silly.\n"<< endl; break;
        case 14: cout <<"Too many variables! (Var Limit: " << cstr(max_vars) << ")\n"<< endl; break;
        case 15: cout <<"Too many !labels! (!Label Limit: " << cstr(max_labels) << ")\n"<< endl; break;
        case 16: cout <<"Robot program too long! Boldly we simplify, simplify along...\n" << ss<< endl; break;
        case 17: cout <<"!Label missing error. !Label #" << ss << "."<< endl; break;
        case 18: cout <<"!Label out of range: " << ss<< endl; break;
        case 19: cout <<"!Label not found. " << ss<< endl; break;
        case 20: cout <<"Invalid config option: \"" << ss << "\". Inventing a new device?"<< endl; break;
        case 21: cout <<"Robot is attempting to cheat; Too many config points (" << ss << ")"<< endl; break;
        case 22: cout <<"Insufficient data in data statement: \"" << ss << "\""<< endl; break;
        case 23: cout <<"Too many asterisks: \"" << ss << "\""<< endl; break;
        case 24: cout <<"Invalid step count: \"" << ss << "\". 1-9 are valid conditions."<< endl; break;
        case 25: cout <<"Not enough matches set! Usage: /M(number of matches)" << endl; break;
        case 26: cout <<"\"" << ss << "\"" << endl; break;
        default: cout <<ss;  break;
    }
    exit(EXIT_FAILURE);
}

void print_code(int n, int p)
{
    return;
}

void parse1(int n, int p, parsetype s)
{/**
    int i, j ,k, l, opcode, microcode;
    bool found, indirect;
    char * ss;
    
    for(i = 0; i < max_op-1; i++)
    {
        k = 0;
        found = false;
        opcode = 0;
        microcode = 0;
        s[i] = uCase(s[i]); //Got rid of btrim
        indirect = false;
        
        (*
         Microcode:
         0 = instruction, number, constant
         1 = variable, memory access
         2 = :label
         3 = !label (unresolved)
         4 = !label (resolved)
         8h mask = inderect addressing (enclosed in [])
         *)
        
        if(s[i] == '')
        {
            opcode = 0;
            microcode = 0;
            found = true;
        }
        
        if(lstr(s[i],1) == '[' && rstr(s[i],1) == ']'))
        {
            s[i] = copy(s[i],2,length(s[i])-2); // change/check
            indirect = true;
        }
        
        //!labels
        
    }**/
    return;
}

void check_plen(int plen)
{
    return;
}

void compile(int n, char* filename)
{
    char *s;
    char *s1;
    char *s2;
    char *s3;
    char *orig_s;
    char *msg;
    int i, j, k, l, linecount, mask, locktype;
    char c,lc;
    char ss [max_op][16];
    parsetype pp;
    
    //code starts
    lock_pos = 0;
    locktype = 0;
    lock_dat = 0;

    if(!EXIST(filename))
    {
        prog_error(8,filename);
    }
    textcolor(robot_color(n));
    cout << "Compiling robot #" << n + 1 << ": " << filename << endl;
    robot[n]->is_locked = false; 
    textcolor(robot_color(n));                                        
    numvars = 0;
    numlabels = 0;
    for(k = 0; k < max_code; k++)
    {
        for(i = 0; i < max_op; i++)
        {
            robot[n]->code[k].op[i] = 0;
        }
    }
    robot[n]->plen = 0;
    //assign(f,filename);
    //reset(f);
    linecount = 0;

    
    //Main compile loop, while not end of file and not end tag, and under max code limit, continue
    while (!(feof(f)) && (!strcmp(s, "#END")) && (robot[n]->plen <= maxcode))
    {
        //readln(f,s);
        linecount++;
        if(locktype < 3)
        {
            lock_pos = 0;
        }
        if(strcmp(lock_code, "\0"))
        {
            for(i = 1; i < strlen(s); i++)
            {
                lock_pos++;
                if(lock_pos > strlen(lock_code))
                {
                    lock_pos = 1;
                }
                switch(locktype)
                {
                    case '3':
                        s[i] = char((int(s[i])-1) ^ (int(lock_code[lock_pos]) ^ lock_dat)); break;
                    case '2':
                        s[i] = char(int(s[i]) ^ (int(lock_code[lock_pos]) ^ 1)); break;
                    default:
                        s[i] = char(int(s[i]) ^ int(lock_code[lock_pos])); break;
                }
            }
            lock_dat = int(s[i]) & 15;
        }
    }
        //s = btrim(s); TEST
        orig_s = s;
        for(i = 1; i < strlen(s); i++)
        {
            // if (s[i] in [#0..#32,',',#128..#255] )                                                  //check this later
            // {
            //     s[i] = ' ';
            // }
            if (show_source && ((lock_code == NULL) || debugging_compiler))
            {
                //writeln(zero_pad(linecount,3)+':'+zero_pad(plen,3)+' ',s);
            }
            if (debugging_compiler)                                                                  //check this later
            {
                
                // if(readkey == #27)                                                                  //check this later
                // {
                //     exit;
                // }
            }
            k = 0;
            for(i = strlen(s); i > 0; i--)
            {
                if ( s[i] == ';')
                {
                    k = i;
                }
            }
            if (k > 0 )
            {
                s = lstr( s , k - 1);
            }
            //s = btrim(uCase(s));
            for ( i = 0; i < max_op; i++)
            {
                pp[i][0] = '\0';
            }
            if ((strlen(s) > 0) && (s[1] != ';'))
            {
                if(s[1] == '#')
                {
                    s1 = uCase(rstr(s,strlen(s)-1));
                    msg = rstr(orig_s, strlen(orig_s)-5);
                    k = 0;
                    for (i = 1; i <= strlen(s); i++)
                    {
                        if ((k = 0) && (s1[i] = ' '))
                        {
                            k = i;
                        }
                        k--;
                        if (k > 1)
                        {
                            s2 = lstr(s1,k);
                            s3 = uCase(rstr(s1, strlen(s1) - k));
                            k = 0;
                            if (numvars > 0 )
                            {
                                for (i = 1; i <= numvars; i++)
                                {
                                    // if (s3 == varname[i][0])
                                    // {
                                    //     k = i;
                                    // }
                                }
                            }
                        }
                    }
                    if ((strcmp(s2, "DEF")) && (numvars < max_vars))
                    {
                        if (strlen(s3) > max_var_len)
                        {
                            prog_error(12,s3);
                        }
                        else if (k > 0) 
                        {    
                            prog_error(11,s3);
                        }
                        else
                        {
                            numvars++;
                            if (numvars > max_vars)
                            {    
                                prog_error(14, s3);
                            }
                            else 
                            {
                                //varname[numvars][0] = s3;
                                varloc [numvars] = 127 + numvars;
                            }
                        }
                    }
                    else if (strcmp(lstr(s2,4), "LOCK"))
                    {
                        robot[n]->is_locked = true; 
                        if (strlen(s2) > 4)
                        {
                            locktype = value(rstr(s2,strlen(s2)-4));
                        }
                        lock_code = uCase(s3);
                        //writeln('Robot is of LOCKed format from this point forward. [',locktype,']');
                        for (i = 1; i < strlen(lock_code); i++)
                        {   
                            lock_code[i] = char(int(lock_code[i])-65);
                        }
                    }
                    else if (strcmp(s2, "MSG")) 
                    {
                        robot[n]->name = msg;
                    }
                    else if (strcmp(s2, "TIME"))
                    {
                        robot[n]->robot_time_limit = value(s3);
                        if (robot[n]->robot_time_limit < 0) 
                        {
                            robot[n]->robot_time_limit = 0;
                        }
                    }
                    else if (strcmp(s2, "CONFIG"))
                    {
                        if (strcmp(lstr(s3,8), "SCANNER="))
                            robot[n]->config.scanner = value(rstr(s3,strlen(s3)-8));
                        else if (strcmp(lstr(s3,7), "SHIELD="))
                            robot[n]->config.shield=value(rstr(s3,strlen(s3)-7));
                        else if (strcmp(lstr(s3,7), "WEAPON="))
                            robot[n]->config.weapon = value(rstr(s3,strlen(s3)-7));
                        else if (strcmp(lstr(s3,6), "ARMOR="))
                            robot[n]->config.armor = value(rstr(s3,strlen(s3)-6));
                        else if (strcmp(lstr(s3,7), "ENGINE="))
                            robot[n]->config.engine = value(rstr(s3,strlen(s3)-7));
                        else if (strcmp(lstr(s3,10), "HEATSINKS="))
                            robot[n]->config.heatsinks = value(rstr(s3,strlen(s3)-10));
                        else if (strcmp(lstr(s3,6), "MINES="))
                            robot[n]->config.mines = value(rstr(s3,strlen(s3)-6));
                        else 
                            prog_error(20,s3);
                        {
                            if ( robot[n]->config.scanner < 0 )
                                robot[n]->config.scanner = 0; 
                            if ( robot[n]->config.scanner>5 )
                                robot[n]->config.scanner = 5;
                            if ( robot[n]->config.shield < 0 ) 
                                robot[n]->config.shield = 0;   
                            if ( robot[n]->config.shield>5 )
                                robot[n]->config.shield = 5;
                            if ( robot[n]->config.weapon < 0 )
                                robot[n]->config.weapon = 0;   
                            if ( robot[n]->config.weapon>5 )
                                robot[n]->config.weapon = 5;
                            if ( robot[n]->config.armor < 0 )
                                robot[n]->config.armor = 0;     
                            if ( robot[n]->config.armor > 5 ) 
                                robot[n]->config.armor = 5;
                            if ( robot[n]->config.engine < 0 )
                                robot[n]->config.engine = 0;   
                            if ( robot[n]->config.engine > 5 ) 
                                robot[n]->config.engine = 5;
                            if ( robot[n]->config.heatsinks < 0 ) 
                                robot[n]->config.heatsinks = 0; 
                            if ( robot[n]->config.heatsinks > 5 ) 
                                robot[n]->config.heatsinks = 5;
                            if ( robot[n]->config.mines < 0 )
                                robot[n]->config.mines = 0;     
                            if ( robot[n]->config.mines > 5 )
                                robot[n]->config.mines = 5;
                        }
                    }
                    else
                    {
                        //writeln('Warning: unknown directive "'+s2+'"');
                    }
                }
            }
    
            if(s[1] == '*')
            {
                
                check_plen(robot[n]->plen);
                for (i = 0; i < max_op; i++) 
                {
                    pp[i][0] = '\0';
                }
                for (i = 2; i < strlen(s); i++)
                {
                    if (s[i] == '*') 
                    {
                        prog_error(23,s);
                        k = 0; 
                        i = 1; 
                        s1[0] = '\0';
                    }
                    if (strlen(s) <= 2 )
                    {
                        prog_error(22,s);
                    }
                    while ((i < strlen(s) && (k <= max_op)))
                    {
                        i++;
                        if( in(int(s[i]), 33, 41) || in(int(s[1]), 43, 127) )
                            pp[k][0] = pp[k][0] + s[i];
                        
                        else if( (in(int(s[i]), 0, 32) || in(int(s[i]), 128, 255)) && (in(int(s[i-1]), 33, 41) || in(int(s[i-1]), 43, 127)) )
                            k++;
                    }
                    for (i = 0; i < max_op; i++)
                    {
                        //robot[n]->code[robot[n]->plen].op[i] = strtol(pp[i]);
                        robot[n]->plen++;
                    }
                }
            }
            if(s[1] == ':')
            {
                check_plen(robot[n]->plen);
                s1 = rstr(s,strlen(s)-1);
                for (i = 1; i < strlen(s1); i++)
                {
                    // if  (!(s1[i] in ['0'..'9']))
                    // {
                    //     prog_error(1,s);
                    // }
                    // //robot[n]->code[robot[n]->plen].op[0] = strtol(s1);
                    robot[n]->code[robot[n]->plen].op[max_op] = 2;
                    if (show_code)
                    {
                        print_code(n, robot[n]->plen);
                    }
                    robot[n]->plen++;
                }
            }
            if(s[1] == '!')
            {
                
                check_plen(robot[n]->plen);
                s1 = rstr(s,strlen(s)-1);
                k = 0;
                for (i = strlen(s1); i >= 1; i--)
                {
                    // if (s1[i] in [';',#8,#9,#10,' ',','])
                    // {
                    //     k = i;
                    // }
                    if ( k > 0 ) 
                    {
                        s1 = lstr(s1,k-1);
                        k = 0;
                    }
                }
                for (i = 1; i < numlabels; i++)
                {
                    if (labelname[i] == s1) 
                    {
                        if (labelnum[i] >= 0) 
                            prog_error(13, "\0");
                            k = i;
                    }
                    if (k == 0) 
                    {
                        numlabels++;
                        if (numlabels > max_labels) 
                        {    
                            prog_error(15, "\0");
                        }
                        k = numlabels;
                    }
                        //labelname[k] = s1;
                        labelnum [k] = robot[n]->plen;
                }
            }
            else
            {
                check_plen(robot[n]->plen);
                k = 0;
                for (i = strlen(s); i >= 1; i--)
                {
                    if (s[i] == ';') 
                    {
                        k = i;
                    }
                    if (k > 0)
                    {
                        s = lstr(s,k-1);
                    }
                    k = 0;
                }
                for (j = 0; j < max_op; j++)
                {
                    pp[j][0] = '\0';
                }
                for (j = 1; j < strlen(s); j++)
                {
                    c = s[j];
                    // if (!(c in [' ',#8,#9,#10,','])) && (k <= max_op)                                                   //check this later
                    // {
                    //     pp[k][0] = pp[k][0] + c;
                    // }
                    // else if (!(lc in [' ',#8,#9,#10,',']))                                                   //check this later
                    // {
                    //     k = k + 1;
                    // }
                    lc = c;
                }
                parse1(n, robot[n]->plen, pp);
                robot[n]->plen++;
            }
            
        }
    

 
        if ( robot[n]->plen <= maxcode)
        {
            for (i = 0;  i < max_op; i++) 
            {
                pp[i][0] = '\0';
            }
            //pp[0][0] = "NOP";
            parse1(n,robot[n]->plen,pp);
        }
        else
        {
            robot[n]->plen--; 
        }
        if ( numlabels > 0 )
        {
            for ( i = 0; i < robot[n]->plen; i++)
            {
                for (j = 0; j < (max_op-1); j++)
                {
                    if (robot[n]->code[i].op[max_op] >> (j*4) == 3)                                                  //check this later
                    {
                        k = robot[n]->code[i].op[j];
                        if (( k>0) && (k <= numlabels ))
                        {
                            l = labelnum[k];
                            if (l < 0) 
                            {    
                                prog_error(19, "\0"); //'!' + labelname[k] + '" ('+cstr(l)+')'
                            }
                            if ((l < 0) || (l > maxcode))
                            {
                                prog_error(18, "\0"); //'!'+labelname[k]+'" ('+cstr(l)+')'
                            }
                            else
                            {
                                robot[n]->code[i].op[j] = l;
                                //mask = !($F << (j*4));
                                robot[n]->code[i].op[max_op] = (robot[n]->code[i].op[max_op] && mask) || (4 << (j*4));
                            }
                        }
                        else
                        {
                            prog_error(17,cstr(k));
                        }
                    }
                }
            textcolor(7);
            }
        }
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
    s = uCase(s);

    if(s == '\0'){
        return;
    }
    if(s[0] == '#')
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
    else if(s[0] == '/' || s[0] == '-' || s[0] == '=')
    {
        //s1 = rstr(s,strlen(s)-1);
        //Debugging
        if(s[1] == 'X')
        {
            step_mode = value(rstr(s,strlen(s)-1));
            found = true;
            if(step_mode == 0) step_mode = 1;
            if(step_mode < 1 || step_mode > 9)
                prog_error(24,rstr(s,strlen(s)-1));
        }
        //Debugging end
        else if(s[1] == 'D')
        {
            game_delay = value(rstr(s,strlen(s)-1));
            found = true;
        }
        else if(s[1] == 'T')
        {
            time_slice = value(rstr(s,strlen(s)-1));
            found = true;
        }
        else if(s[1] == 'L')
        {
            game_limit = value(rstr(s,strlen(s)-1))*1000;
            found = true;
        }
        else if(s[1] == 'Q')
        {
            sound_on = false;
            cout << "SOUND IS OFF" << endl;
            found = true;
        }
        else if(s[1] == 'M')
        {
            matches = value(&s[2]);
            found = true;
        }
        else if(s[1] == 'S')
        {
            show_source = false;
            cout << "SOURCE IS OFF" << endl;
            found = true;
        }
        else if(s[1] == 'G')
        {
            no_gfx = true;
            found = true;
        }
        else if(s[1] == 'R')
        {
            report = true;
            found = true;
            if(strlen(s) > 1)
                report_type = value(rstr(s,strlen(s)-1));
        }
        else if(s[1] == 'C')
        {
            compile_only = true;
            found = true;
        }
        else if(s[1] == '^')
        {
            show_cnotice = false;
            cout << "CNOTICE IS OFF" << endl;
            found = true;
        }
        else if(s[1] == 'A')
        {
            show_arcs = true;
            found = true;
        }
        else if(s[1] == 'W')
        {
            windoze = false;
            found = true;
        }
        else if(s[1] == '$')
        {
            debug_info = true;
            cout << "SHOW DEBUG INFO" << endl;
            found = true;
        }
        else if(s[1] == '#')
        {
            maxcode = value(rstr(s,strlen(s)-1))-1;
            found = true;
        }
        else if(s[1] == '!')
        {
            insane_missiles = true;
            if(strlen(s) > 1)
                insanity = value(rstr(s,strlen(s)-1));
            found = true;
        }
        else if(s[1] == '@')
        {
            old_shields = true;
            found = true;
        }
        else if(s[1] == 'E')
        {
            logging_errors = true;
            found = true;
        }
        if(insanity < 0)
            insanity = 0;
        if(insanity > 15)
            insanity = 15;
    }
    else if(s[0] == ';'){
        found = true;
    }
    else if(num_robots < max_robots && s != '\0')
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
        textcolor(3);
        cout << endl;
        cout << progname << " " << version << endl;
        cout << cnotice1 << endl;
        cout << cnotice2 << endl;
        cout << cnotice3 << endl;
    }
    textcolor(7);
    if(!registered)
    {
        textcolor(4);
        cout << "Unregistered version" << endl;
    }
    else
    {
        cout << "Registered to: " << reg_name << endl;
    }
    textcolor(7);
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
    if(k == 1){
      snprintf(s, strlen(s), "Robot # ");
      strcpy(s, cstr(n+1));
      snprintf(s, strlen(s), " (");
      strcpy(s, robot[n]->fn);
      snprintf(s, strlen(s), ") Wins!!!");  
    } 
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
        textcolor(15);
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
            textcolor(robot_color(i));
            if(k == 1 && n == i)
                j = 1;
            else
                j = 0;
            cout << addfront(cstr(i+1),2) << " - " << addrear(robot[i]->fn,15) << cstr(j) << addfront(cstr(robot[i]->wins),8)
            << addfront(cstr(robot[i]->trials),8) << addfront(cstr(robot[i]->armor) ,9) << '%' << addfront(cstr(robot[i]->kills),7)
            << addfront(cstr(robot[i]->deaths),8) << addfront(cstr(robot[i]->match_shots),9) << endl;
        }
        textcolor(15); //white
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

