/**
 * ctagchecker.h
 * Title: Interface for tag check class
 * Description: Class to check tag type
 * Author: David Kopelent
 */

#ifndef CTAGCHECKER
#define CTAGCHECKER
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class CTagChecker {
public:
    CTagChecker(void) = default;

    /**
     * Check for link
     * @param tag tag to be checked
     * @return bool
    */
    bool isLink(const string &tag) const;

    /**
     * Check for paragraph
     * @param tag tag to be checked
     * @return bool
    */
    bool isParagraph(const string &tag) const;

    /**
     * Check for bold
     * @param tag tag to be checked
     * @return bool
    */
    bool isBold(const string &tag) const;

    /**
     * Check for italic
     * @param tag tag to be checked
     * @return bool
    */
    bool isItalic(const string &tag) const;

    /**
     * Check for image
     * @param tag tag to be checked
     * @return bool
    */
    bool isImage(const string &tag) const;

    /**
     * Check for heading
     * @param tag tag to be checked
     * @return bool
    */
    bool isHeading(const string &tag) const;

    /**
     * Check for list
     * @param tag tag to be checked
     * @return bool
    */
    bool isList(const string &tag) const;

    /**
     * Check for table
     * @param tag tag to be checked
     * @return bool
    */
    bool isTable(const string &tag) const;
};
#endif
