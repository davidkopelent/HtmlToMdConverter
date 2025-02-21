/**
 * cmdparser.h
 * Title: Interface for MD parser class
 * Description: Class takes MD document line and parse it to inner HTML representation
 * Author: David Kopelent
 */

#ifndef CMDPARSER
#define CMDPARSER
#include "cdocument.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <cctype>
#include <algorithm>
using namespace std;

class CMDParser : public CDocument {
protected:
    // Table indicator
    bool table;

    // Table row number
    int tableRow;

    // Table head indicator
    bool tableHeadStatus;

    // Number of tabs before list item
    int tab;

    // List indicator
    bool list;

    // Cache storage
    stack<string> cache;

    /**
     * Parse heading
     * @param line line for parsing
     * @return string
    */
    string parseHeading(string line);

    /**
     * Parse bold and italic text
     * @param line line for parsing
     * @return string
    */
    string parseBoldItalic(string line);

    /**
     * Parse bold text
     * @param line line for parsing
     * @return string
    */
    string parseBold(string line);

    /**
     * Parse italic text
     * @param line line for parsing
     * @return string
    */
    string parseItalic(string line);

    /**
     * Parse image
     * @param line line for parsing
     * @return string
    */
    string parseImage(string line);

    /**
     * Parse link
     * @param line line for parsing
     * @return string
    */
    string parseLink(string line);

    /**
     * Parse unordered list
     * @param line line for parsing
     * @return string
    */
    string parseUnorderedList(string line);

    /**
     * Parse ordered list
     * @param line line for parsing
     * @return string
    */
    string parseOrderedList(string line);

    /**
     * Trim line
     * @param line line to be trimmed
     * @return string
    */
    string trim(string line);

    /**
     * Check if table contains head
     * @param line line to be checked
     * @return bool
    */
    bool checkTableHead(const string &line);

    /**
     * Parse table
     * @param line line for parsing
     * @return string
    */
    string parseTable(string line);

    /**
     * Parse paragraph
     * @param line line for parsing
     * @return string
    */
    string parseParagraph(string line);

public:
    /**
     * Default constructor
    */
    CMDParser(void) = default;

    /**
     * Constructor
     * @param fileName file for parsing
    */
    CMDParser(const string &fileName);

    bool parse(string line) override;
};
#endif
