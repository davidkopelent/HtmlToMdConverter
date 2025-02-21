/**
 * cdocument.h
 * Title: Interface for document conversion class
 * Description: Class takes HTML/MD document and processes parsing and converting
 * Author: David Kopelent
 */

#ifndef CDOCUMENT
#define CDOCUMENT
#include "ctag.h"
#include "cmessage.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <cctype>
#include <algorithm>
#include <memory>
using namespace std;

class CDocument {
protected:
    // Converting file name
    string fileName;

    // Number of line being converted
    int lineNumber;

    // Tag storage
    vector<unique_ptr<CTag>> tags;
    
    // Warning message class
    CWarningMessage warning;

    // Error message class
    CErrorMessage error;

public:
    /**
     * Default constructor
    */
    CDocument(void) = default;

    /**
     * Constructor
     * @param fileName file to be converted
    */
    CDocument(const string &fileName);

    /**
     * Virtual destructor
    */
    virtual ~CDocument() = default;

    /**
     * Read, parse and convert document processor
     * @param converter document converter class
     * @return bool
    */
    template<typename T>
    bool process(T converter);

    /**
     * Parse document content to universal representation (HTML)
     * @param line line for parsing
     * @return bool
    */
    virtual bool parse(string line) = 0;
};

template<typename T>
bool CDocument::process(T converter) {
    ifstream fileIn(fileName, ios::in);

    if (!fileIn.is_open()) {
        error.printMessage(error.fileOpenError(fileName));
        delete converter;
        return false;
    }

    string buffer;
    while (getline(fileIn, buffer)) {
        if (!parse(buffer)) {
            delete converter;
            return false;
        }
        lineNumber++;
    }

    parse("");
    if (!converter->convert(tags)) {
        delete converter;
        return false;
    }

    delete converter;
    return true;
}
#endif
