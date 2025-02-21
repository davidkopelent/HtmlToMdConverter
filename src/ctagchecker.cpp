/**
 * ctagchecker.cpp
 * Title: Check tag class implementation
 * Author: David Kopelent
 */

#include "ctagchecker.h"
#include <iostream>
#include <string>
using namespace std;

bool CTagChecker::isLink(const string &tag) const {
    return (tag == "<a>" || tag == "</a>");
}

bool CTagChecker::isParagraph(const string &tag) const {
    return (tag == "<p>" || tag == "</p>" || tag == "<br>");
}

bool CTagChecker::isBold(const string &tag) const {
    return (tag == "<b>" || tag == "</b>" || tag == "<strong>" || tag == "</strong>");
}

bool CTagChecker::isItalic(const string &tag) const {
    return (tag == "<i>" || tag == "</i>" || tag == "<em>" || tag == "</em>");
}

bool CTagChecker::isImage(const string &tag) const {
    return (tag == "<img>");
}

bool CTagChecker::isHeading(const string &tag) const {
    return (tag == "<h1>" || tag == "</h1>" || tag == "<h2>" || tag == "</h2>" 
            || tag == "<h3>" || tag == "</h3>" || tag == "<h4>" || tag == "</h4>"
            || tag == "<h5>" || tag == "</h5>" || tag == "<h6>" || tag == "</h6>");
}

bool CTagChecker::isList(const string &tag) const {
    return (tag == "<ul>" || tag == "</ul>" || tag == "<ol>" || tag == "</ol>" 
            || tag == "<li>" || tag == "</li>");
}

bool CTagChecker::isTable(const string &tag) const {
    return (tag == "<table>" || tag == "</table>" || tag == "<thead>" || tag == "</thead>" 
            || tag == "<tbody>" || tag == "</tbody>" || tag == "<tr>" || tag == "</tr>" 
            || tag == "<th>" || tag == "</th>" || tag == "<td>" || tag == "</td>");
}
