/**
 * cmdconverter.h
 * Title: Interface for MD converter class
 * Description: Class takes inner HTML representation and converts it to MD format
 * Author: David Kopelent
 */

#ifndef CMDCONVERTER
#define CMDCONVERTER
#include "ctag.h"
#include "ctagchecker.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <stack>
#include <queue>
#include <cctype>
#include <algorithm>
#include <memory>
using namespace std;

class CMDConverter {
protected:
    // Output file
    string outFile;

    // Storage with all files for conversion
    vector<string> files;

    // Tag atributes storage
    queue<string> atributes;

    // Cache storage for table tags
    queue<string> tableCache;

    // Table indicator
    bool table;

    // Table row number
    int row;

    // Cache storage for list tags
    stack<string> listCache;

    // Cache storage for ordered list indexes
    stack<int> listIndexes;

    // Number of tabs before list items
    int tab;

    // Opening tags storage for pair checking
    stack<pair<string,int>> openTags;

    // Storage for converted elements
    vector<string> results;

    // Tag checker class
    CTagChecker tagChecker;
    
    // Warning message class
    CWarningMessage warning;

    // Error message class
    CErrorMessage error;

    /**
     * Compare tags
     * @param lTag first tag
     * @param rTag second tag
     * @return bool
    */
    bool isTagEqual(const string &lTag, const string &rTag);

    /**
     * Check paired tags
     * @param tag tag to be checked
     * @param type tag type
     * @param lineNumber position of tag in the document
     * @return bool
    */
    bool checkTags(const string &tag, const string &type, int lineNumber);

    /**
     * Convert link
     * @param tag tag for conversion
     * @param atribute link
     * @return string
    */
    string convertLink(const string &tag, const string &atribute);

    /**
     * Convert paragraph
     * @param tag tag for conversion
     * @return string
    */
    string convertParagraph(const string &tag);

    /**
     * Convert bold text
     * @param tag tag for conversion
     * @return string
    */
    string convertBold(const string &tag);

    /**
     * Convert italic text
     * @param tag tag for conversion
     * @return string
    */
    string convertItalic(const string &tag);

    /**
     * Convert headings
     * @param tag tag for conversion
     * @return string
    */
    string convertHeading(const string &tag, const string &headingSize);

    /**
     * Convert image
     * @param tag tag for conversion
     * @param atribute image src
     * @return string
    */
    string convertImage(const string &tag, const string &atribute);

    /**
     * Convert lists
     * @param tag tag for conversion
     * @return string
    */
    string convertList(const string &tag);

    /**
     * Convert table
     * @param tag tag for conversion
     * @return string
    */
    string convertTable(const string &tag);

    /**
     * Write converted results to output file
     * @return bool
    */
    bool writeResults(void);

public:
    /**
     * Default constructor
    */
    CMDConverter() = default;

    /**
     * Constructor
     * @param outFile output file
    */
    CMDConverter(const string &outFile);

    /**
     * Virtual destructor
    */
    virtual ~CMDConverter() = default;

    /**
     * Constructor
     * @param outFile
     * @param files files to be converted (for intern link conversion)
    */
    CMDConverter(const string &outFile, vector<string> files);

    /**
     * Conversion controller
     * @param tags parsed tags
     * @return bool
    */
    virtual bool convert(vector<unique_ptr<CTag>> &tags);
};
#endif
