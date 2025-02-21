/**
 * chtmlparser.h
 * Title: Interface for HTML parser class
 * Description: Class takes HTML document line and parse it to inner HTML representation
 * Author: David Kopelent
 */

#ifndef CHTMLPARSER
#define CHTMLPARSER
#include "cdocument.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

class CHtmlParser : public CDocument {
public:
    /**
     * Constructor
     * @param fileName file for parsing
    */
    CHtmlParser(const string &fileName);

    bool parse(string line) override;
};
#endif
