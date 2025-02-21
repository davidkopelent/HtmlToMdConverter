/**
 * chtmlconverter.h
 * Title: Interface for HTML converter class
 * Description: Class takes inner HTML representation and converts it to HTML format
 * Author: David Kopelent
 */

#ifndef CHTMLCONVERTER
#define CHTMLCONVERTER
#include "ctag.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <cctype>
#include <algorithm>
#include <memory>
using namespace std;

class CHtmlConverter {
private:
    // Output file
    string outFile;

    // Storage with all files for conversion
    vector<string> files;
    
    // Warning message class
    CWarningMessage warning;

    // Error message class
    CErrorMessage error;

    /**
     * Add HTML head to file
    */
    string addHtmlHead(void);
    
    /**
     * Add HTML footer to file
    */
    string addHtmlFooter(void);

    /**
     * Find link on line and return it
     * @param line line with link
     * @param atribute link atribute (href)
     * @return string
    */
    string findLink(string line, const string &atribute);

    /**
     * Convert internal links
     * @param line line to be converted
     * @return string
    */
    string convertLink(string line);

    /**
     * Write converted results to file
     * @param converted tags
     * @return bool
    */
    bool writeResults(vector<unique_ptr<CTag>> &tags);

public:
    /**
     * Default constructor
    */
    CHtmlConverter() = default;

    /**
     * Constructor
     * @param outFile
    */
    CHtmlConverter(const string &outFile);

    /**
     * Virtual destructor
    */
    virtual ~CHtmlConverter() = default;

    /**
     * Constructor
     * @param outFile
     * @param files files to be converted (for intern link conversion)
    */
    CHtmlConverter(const string &outFile, vector<string> files);

    /**
     * Convert controller
     * @param tags tags for conversion
    */
    virtual bool convert(vector<unique_ptr<CTag>> &tags);
};
#endif
