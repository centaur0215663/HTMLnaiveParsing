/*------------------NaiveParsing.cpp----------------------*/

//Author : Afeef Hamid
//This program does basically what a browser does, it interprets a text file with markups (tags)
//Uses HTML (Hyper-Text-Markup-Language)


#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <list>

using namespace std;

int main(){
    string target("html_example.html");         //file we want to parse
    int counter(1);                             //counts how many times we've tried opening the file

    ifstream fin (target.c_str());              //out file input stream object, initialized with path to target

    //-------------check to see if file opened correctly-------------
    while (fin.fail())
    {
        //ERROR MESSAGE
        cerr <<"fin.open("<<target<<") failed. This has been attempt " << counter<<endl;
        
        fin.clear();    //clear fin's buffer, so we can try opening it again

        //--Try to get user input for alternate path to target
        counter++;      //increment our # of attempts
        cout <<"Please enter a path to the input file, or enter null to exit"<<endl;
        string pathAlt;         
        cin >>pathAlt;
        if (pathAlt == "null" || counter >5){               //give up
            cerr<<"Exiting program, giving up :'("<<endl;       //error message
            exit(93);                                           //close program
        }
        fin.open(pathAlt.c_str());                          //try to open file with alternate path
    }
    //------------------------file opened----------------------------

    //list of tags encountered
    list<string> htmlTags;
    bool multiLineComment = false;          //this flag tells us if we are in a multiline comment
    //------------------------Main Parsing Loop----------------------
    while(!fin.eof()){                  //while we HAVE NOT reached the end of the file
        //first we will practice pulling tags from the document, by storing all tags

        string temp;                //working line
        getline(fin,temp);          //get a line from fin, store to temp
        //we need some way to store current tags, mabye in a list that we can add and subtract to
        


        //iterate character by character, if tag is found, replace with padding or flip flags
        for(int pointer = 0; pointer < temp.length();pointer++)       //go until second to last element in temp
        {
            
            if (temp[pointer] == '<'){       //start of tag
            
                //pointer is at the start of a tag
                int start = pointer;
                //now we look for a > to denote the end of a tag (this means the contents of comments are a unique tag)
                if(temp[pointer+1] == '!'){
                    multiLineComment = true;
                    //cout << "multiline comment = true\n";
                }
                else if (!multiLineComment){
                    //cout<<temp[pointer];    //if we dont know what the tag is, do nothing, as long as it isnt in the comment
                    //figure out how long the tag is
                    int taglength(pointer);
                    for(;taglength<temp.length();taglength++)
                    {
                        if(temp[taglength] == '>'){
                            pointer=taglength;
                            break;
                        }
                    }
                }
                //REMEMBER TO MOVE POINTER AFTER PULLING OUT THE TAG

            }
            else if ((temp[pointer] == '>') && multiLineComment){       //end multiline comment
                multiLineComment=false;
                //cout << "multiline comment = false\n";
            }
            else if(!multiLineComment){                           //if not a tag, we probably want to write it!
                cout <<temp[pointer];
            }
            //cout << pointer <<endl;
        }
        
        
        if(!multiLineComment) cout <<endl;          //print parsed version of line
        //cout <<temp<<endl;
    }


}


//algorithm:

//open file
    //check for errors in opening

//read file word by word
    //figure out what to do with sections of text by looking at tags
        // <html>  -> denotes start of file, good!     | not shown
        // <head>  -> Head, we will ignore             | not shown
        // <title> ->

    //once we encounter a tag -> print/ommit words until end tag

//done!

//first version of this program will NOT use regex, since regex isn't  really part of the courses lessons
//second version will use regex to improve readability of code
//this is version 1