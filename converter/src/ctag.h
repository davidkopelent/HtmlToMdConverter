/**
 * ctag.h
 * Title: Interface for tag class
 * Description: Class to represent parsed document tags and contents
 * Author: David Kopelent
 */

#ifndef CTAG
#define CTAG
#include "cmessage.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <cctype>
#include <algorithm>
using namespace std;

class CTag {
protected:
    // Tag content
    string content;

    // Tag atribute
    string atribute;

    // Tag type
    string type;

    // Warning message class
    CWarningMessage warning;

    // Error message class
    CErrorMessage error;

public:
    /**
     * Default constructor
    */
    CTag(void) = default;

    /**
     * Constructor
     * @param tag
    */
    CTag(const string &tag, const string &type);

    /**
     * Virtual destructor
    */
    virtual ~CTag() = default;

    /**
     * Parse new tag
     * @param lineNumber
     * @return bool
    */
    virtual bool parseTag(int lineNumber) = 0; 

    /**
     * Content getter
     * @return string
    */
    string getContent(void);

    /**
     * Atribute getter
     * @return string
    */
    string getAtribute(void);

    /**
     * Type getter
     * @return string
    */
    string getType(void);

    /**
     * Parse tag atributes
     * @param tag tag for parsing
     * @param atribute atribute to be parsed
     * @return string
    */
    string parseAttribute(string tag, const string &atribute);
};

class CHtmlTag : public CTag {
protected:
    string tag;
    unordered_set<string> ignoredTags;
    unordered_set<string> supportedTags;

    /**
     * Initialize tag lists
    */
    void initializeTagList(void);

public:
    CHtmlTag(void) = default;

    /**
     * Constructor
     * @param tag
    */
    CHtmlTag(const string &tag);

    /**
     * Constructor
     * @param tag
     * @param type
    */
    CHtmlTag(const string &tag, const string &type);

    bool parseTag(int lineNumber) override;
};

class CMDTag : public CTag {
protected:
    string tag;

public:
    /**
     * Constructor
     * @param tag
    */
    CMDTag(const string &tag);

    bool parseTag(int lineNumber) override;
};
#endif
