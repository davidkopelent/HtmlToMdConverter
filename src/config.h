/**
 * config.h
 * Title: Configuration file
 * Description: File with program parameters
 * Author: David Kopelent
*/

#ifndef CONFIG
#define CONFIG
#include <iostream>
#include <string>
using namespace std;

// Welcome screen
const string WELCOME_SCREEN_TEXT = " WELCOME TO HTML / MARKDOWN FILE CONVERTER! ";
const string WELCOME_SCREEN = "\033[3;47;30m" + WELCOME_SCREEN_TEXT + "\033[0m";

// Conversion type commands
const string EXIT = "EXIT";
const string HTML_TO_MARKDOWN = "HTML";
const string MARKDOWN_TO_HTML = "MD";

// Operation commands
const string FOLDER_CONVERT = "DIR";
const string FOLDER_RECURSIVE_CONVERT = "RDIR";
const string FILE_CONVERT = "FILE";
const string CONVERT_EXECUTE = "START";

// File limit
const int LIMIT = 100;
#endif