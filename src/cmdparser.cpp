/**
 * cmdparser.cpp
 * Title: MD parser class implementation
 * Author: David Kopelent
 */

#include "cmdparser.h"
using namespace std;

string CMDParser::parseHeading(string line) {
    size_t check = line.find("#");
    size_t check2 = line.find_first_of(" ");

    if (check == string::npos || check2 == string::npos || (check2-check) > 6)
        return line;

    line = "<h" + to_string(check2-check) + ">" + line.substr(check2+1, line.length()-check2-1) + "</h" + to_string(check2-check) + ">";
    return line;
}

string CMDParser::parseBoldItalic(string line) {
    bool isBoldItalic = false;
    while (true) {
        size_t check = line.find("***");

        if (check == string::npos)
            break;

        if (isBoldItalic) {
            line = line.substr(0, check) + "</i></b>" + line.substr(check+3, line.length()-check-3);
            isBoldItalic = false;
        } else if (!isBoldItalic) {
            if (line.find("***", check+3) == string::npos) {
                warning.printMessage(warning.formatingWarning(lineNumber));
                return line;
            }
            line = line.substr(0, check) + "<b><i>" + line.substr(check+3, line.length()-check-3);
            isBoldItalic = true;
        }
    }
    return line;
}

string CMDParser::parseBold(string line) {
    bool isBold = false;
    while (true) {
        size_t check = line.find("**");

        if (check == string::npos)
            break;

        if (isBold) {
            line = line.substr(0, check) + "</b>" + line.substr(check+2, line.length()-check-2);
            isBold = false;
        } else if (!isBold) {
            if (line.find("**", check+2) == string::npos) {
                warning.printMessage(warning.formatingWarning(lineNumber));
                return line;
            }
            line = line.substr(0, check) + "<b>" + line.substr(check+2, line.length()-check-2);
            isBold = true;
        }
    }
    return line;
}

string CMDParser::parseItalic(string line) {
    bool isItalic = false;
    while (true) {
        size_t check = line.find("*");

        if (check == string::npos)
            break;
        
        if (isItalic) {
            line = line.substr(0, check) + "</i>" + line.substr(check+1, line.length()-check-1);
            isItalic = false;
        } else if (!isItalic) {
            if (line.find("*", check+2) == string::npos) {
                warning.printMessage(warning.formatingWarning(lineNumber));
                return line;
            }
            line = line.substr(0, check) + "<i>" + line.substr(check+1, line.length()-check-1);
            isItalic = true;
        }
    }
    return line;
}

string CMDParser::parseImage(string line) {
    while (true) {
        size_t check = line.find("![");
        size_t check2 = line.find("]");
        size_t atribute1 = check2 + 1;
        size_t atribute2 = line.find(")");
        
        if (check == string::npos || check2 == string::npos || atribute2 == string::npos) {
            if (check != string::npos && (check2 == string::npos || line[atribute1] != '(' || atribute2 == string::npos)) {
                warning.printMessage(warning.formatingWarning(lineNumber));
                return line;
            }
            break;
        }

        string atribute = line.substr(atribute1+1, atribute2-atribute1-1);
        if (atribute.empty()) {
            warning.printMessage(warning.formatingWarning(lineNumber));
            return line;
        }
        line = line.substr(0, check) + "<img src=\"" + atribute + "\"/>" + line.substr(atribute2+1, line.length()-atribute2-1); 
    }
    return line;
}

string CMDParser::parseLink(string line) {
    while (true) {
        size_t check = line.find("[");
        size_t check2 = line.find("]", check);
        size_t atribute1 = check2 + 1;
        size_t atribute2 = line.find(")", check);
        
        if (check == string::npos || check2 == string::npos || line[atribute1] != '(' || atribute2 == string::npos) {
            if (check != string::npos && (check2 == string::npos || line[atribute1] != '(' || atribute2 == string::npos)) {
                warning.printMessage(warning.formatingWarning(lineNumber));
                return line;
            }
            break;
        }

        string atribute = line.substr(atribute1+1, atribute2-atribute1-1);
        if (atribute.empty()) {
            warning.printMessage(warning.formatingWarning(lineNumber));
            return line;
        }
        line = line.substr(0, check) + "<a href=\"" + atribute + "\">" + line.substr(check+1, check2-1-check) + "</a>" + line.substr(atribute2+1, line.length()-atribute2-1);
    }
    return line;
}

string CMDParser::parseUnorderedList(string line) {
    size_t check = line.find("* ");

    if (check == string::npos || line.empty()) {
        if (line.empty() && !cache.empty() && list) {
            while (!cache.empty()) {
                line = cache.top() + "\n" + line;
                cache.pop();
            }
            list = false;
        }
        return line;
    }

    list = true;
    string lineCheck = line.substr(0, check);
    int whitespaces = lineCheck.length();
    string listTag = "";

    if (lineCheck.find_first_not_of(" \t") == string::npos) {
        if (cache.empty() || whitespaces > tab || (cache.top() != "</ul>" && whitespaces == tab)) {
            lineCheck = lineCheck + "<ul>\n" + lineCheck;
            cache.push("</ul>");
        } else if (whitespaces < tab) {
            for (int i = whitespaces; i < tab; i++ ) {
                listTag += string(whitespaces+1, '\t') + cache.top() + "\n";
                cache.pop();
            }
        }

        line = listTag + lineCheck + "<li>" + line.substr(check+2, line.length()-check-2) + "</li>";
        tab = whitespaces;
    }

    return line;
}

string CMDParser::parseOrderedList(string line) {
    size_t check = line.find(". ");

    if (check == string::npos || !isdigit(line[check-1]) || line.empty()) {
        if (line.empty() && !cache.empty() && list) {
            while (!cache.empty()) {
                line = cache.top() + "\n" + line;
                cache.pop();
            }
            list = false;
        }
        return line;
    }

    list = true;
    string lineCheck = line.substr(0, check-1);
    int whitespaces = lineCheck.length();
    string listTag = "";

    if (lineCheck.find_first_not_of(" \t") == string::npos) {
        if (cache.empty() || whitespaces > tab || (cache.top() != "</ol>" && whitespaces == tab)) {
            lineCheck = lineCheck + "<ol>\n" + lineCheck;
            cache.push("</ol>");
        } else if (whitespaces < tab) {
            for (int i = whitespaces; i < tab; i++ ) {
                listTag += string(whitespaces+1, '\t') + cache.top() + "\n";
                cache.pop();
            }
        }

        line = listTag + lineCheck + "<li>" + line.substr(check+2, line.length()-check-2) + "</li>";
        tab = whitespaces;
    }

    return line;
}

string CMDParser::trim(string line) {
    size_t lineBegin = line.find_first_not_of(" \t");
    if (lineBegin == string::npos)
        return line;

    size_t lineEnd = line.find_last_not_of(" \t");
    size_t lineRange = lineEnd - lineBegin + 1;
    return line.substr(lineBegin, lineRange);
}

bool CMDParser::checkTableHead(const string &line) {
    return (all_of(line.begin(), line.end(), [](char const &c) { return (c == '-' || c == '|' || isspace(c)); }));
}

string CMDParser::parseTable(string line) {
    size_t check = line.find("|");

    if (check == string::npos || check != 0 || line.empty()) {
        if ((line.empty()) && table) {
            line = "</tbody>\n</table>\n" + line;
            table = false;
            tableHeadStatus = false;
        }
        return line;
    }

    string tableStart = "";
    if (!table) {
        if (line.find("|", check+1) == string::npos) {
            warning.printMessage(warning.formatingWarning(lineNumber));
            return line;
        }
        tableStart = "<table>\n<thead>\n";
        tableRow = 1;
    }

    table = true;
    string cellContent = trim(line.substr(check+1, line.length()-check-1));

    if (!tableHeadStatus && checkTableHead(cellContent))
        tableHeadStatus = true;

    if (tableRow == 2) {
        line = "</thead>\n<tbody>";
        tableRow++;
        return line;
    }
    
    line = tableStart + "<tr>\n<td>" + cellContent;
    while (true) {
        check = line.find("|");

        if (check == string::npos || check == line.length()-1)
            break;

        string cellContentBegin = trim(line.substr(0, check));
        string cellContentEnd = trim(line.substr(check+1, line.length()-check-1));
        line = cellContentBegin + "</td>\n<td>" + cellContentEnd;
    }

    cellContent = trim(line.substr(0, line.length()-1));
    line = cellContent + "</td>\n</tr>";
    tableRow++;
    return line;
}

string CMDParser::parseParagraph(string line) {
    size_t check = line.find_first_not_of(" \t");
    if (check == string::npos)
        return "";

    if (line[check] != '<')
        line = "<p>" + line + "</p>";
    return line;
}

CMDParser::CMDParser(const string &fileName) :
    CDocument(fileName),
    table(false),
    tableHeadStatus(false),
    tab(0),
    list(false) {}

bool CMDParser::parse(string line) {
    line = parseHeading(line);
    line = parseUnorderedList(line);
    line = parseOrderedList(line);
    line = parseBoldItalic(line);
    line = parseBold(line);
    line = parseItalic(line);
    line = parseImage(line);
    line = parseTable(line); 
    line = parseLink(line); 
    line = parseParagraph(line);
    tags.push_back(unique_ptr<CTag>(new CMDTag(line)));
    return true;
}
