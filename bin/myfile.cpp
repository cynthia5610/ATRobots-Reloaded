/*  MYFILE.PAS
    Attempted: 2/20/2018
*/



#include <string.h>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <cstdint>
//uint8_t
//int8_t
using namespace std;




//function prototypes
string lstr             (string s1, int l);                 //puts part of a string into lstr
long file_size          (char* fn);                         //returns filesize
void delete_file        (char* fn);                         //deletes a file 
void rename_file        (char* fn, char* fn2);              //renames a file
//void open_filein    (var h:word; fn:string);
//void open_fileout   (var h:word; fn:string);
//void open_fileboth  (var h:word; fn:string);
//void create_fileout (var h:word; fn:string);
//void read_file      (h:word; ploc:pointer; var len:integer);
//void write_file     (h:word; ploc:pointer; var len:integer);
//void close_file     (h:word);
//void file_seek      (h,d:word; m:byte; var p:word);
//void long_seek      (h:word; d:longint; m:byte; var p:longint);
//void read_long      (h:word; ploc:pointer; var len:word);
//void write_long     (h:word; ploc:pointer; var len:word);


//Puts part of a string into a new string, which is later used for comparisons against rstr... not in this function
string lstr(string s1, int length)
{
    
    string lstr = "";
    lstr.append(s1, 0, length); 
    return lstr;
}


//Returns kilobyte filesize as long or double 
long file_size(char* fn)
{
    if( ( fn ) == 0 )
        perror( "Error, no file to give size of." );
    std::ifstream in(fn, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

//Deletes file name passed to function
void delete_file(char* fn)
{
    if( remove( fn ) != 0 )
        perror( "Error deleting file" );
    else
        puts( "File successfully deleted" );
}

//renames file fn to fn2, if both exist
void rename_file(char* fn, char* fn2)
{
    int result = 0;
    if( ( fn ) == 0 )
        perror( "Error, no file name given to rename." );
    else if (( fn2 ) == 0 )
        perror( "Error, no rename has been issued." );
    else
    {
        result = rename( fn , fn2 );
        if ( result == 0 )
            puts ( "File successfully renamed" );
        else
            perror( "Error renaming file" );
    }
}


int main() 
{
    //string word2 ="";
    //string word = "thanks for all the fish";
    //word2 = lstr(word, 8);
    //cout<<word2<<endl;
    //long fs = file_size("test.txt");
    //cout <<"Size is: "<< fs << endl;
    //delete_file("test.txt");
    //rename_file("test.txt", "testy.txt");
    return 0; 
}
