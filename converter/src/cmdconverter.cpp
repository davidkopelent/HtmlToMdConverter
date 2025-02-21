/**
 * cmdconverter.cpp
 * Title: MD converter class implementation
 * Author: David Kopelent
 */

#include "cmdconverter.h"
using namespace std;

bool CMDConverter::isTagEqual(const string &lTag, const string &rTag) {
    string tag = lTag.substr(0,1) + "/" + lTag.substr(1,lTag.length()-1);
    return (tag == rTag);
}

bool CMDConverter::checkTags(const string &tag, const string &type, int lineNumber) {
    if (type == "tag") {
        if (tag[1] != '/' && tag != "<img>" && tag != "<br>") {
            openTags.push({tag, lineNumber});
        } else if (tag[1] == '/' && tag != "/n" && tag != "/c") {
            if (openTags.empty() || !isTagEqual(openTags.top().first, tag)) {
                error.printMessage(error.invalidTag(lineNumber));
                return false;
            }
            openTags.pop();
        }
    }
    return true;
}

string CMDConverter::convertLink(const string &tag, const string &atribute) {
    if (tag == "<a>") {
        atributes.push(atribute);
        return "[";
    } else if (tag == "</a>") {
        string link = "#";
        if (!atributes.empty()) {
            link = atributes.front();
            atributes.pop();
        }

        if (!link.empty()) {
            if (find_if(files.begin(), files.end(), [&](const string& str) {return str.find(link) != string::npos;}) != files.end())
                link = link.substr(0, link.find(".")) + "-converted.md";
        }

        return "](" + link + ")";
    }
    return "";
}

string CMDConverter::convertParagraph(const string &tag) {
    if (tag == "<br>")
        return "\n";
    return "";
}

string CMDConverter::convertBold(const string &tag) {
    return "**";
}

string CMDConverter::convertItalic(const string &tag) {
    return "*";
}

string CMDConverter::convertHeading(const string &tag, const string &headingSize) {
    if (tag[1] == '/')
        return "\n";
    return "\n" + string(stoi(headingSize), '#') + " ";
}

string CMDConverter::convertImage(const string &tag, const string &atribute) {
    string src = (!atribute.empty()) ? atribute : "#";
    return "![Image](" + src + ")";
}

string CMDConverter::convertList(const string &tag) {
    if (tag == "<ul>") {
        listCache.push("<ul>");
        tab++;
    } else if (tag == "<ol>") {
        listCache.push("<ol>");
        listIndexes.push(0);
        tab++;
    } else if (tag == "<li>" && listCache.top() == "<ul>") {
        return "\n" + string(tab-1, '\t') + "* ";
    } else if (tag == "<li>" && listCache.top() == "<ol>") {
        listIndexes.top() += 1;
        return "\n" + string(tab-1, '\t') + to_string(listIndexes.top()) + ". ";
    } else if (tag == "</ul>" || tag == "</ol>") {
        listCache.pop();
        if (tag == "</ol>")
            listIndexes.pop();
        tab--;
    }
    return "";
}

string CMDConverter::convertTable(const string &tag) {
    if (tag == "<table>") {
        table = true;
        return "\n";
    } else if (tag == "</table>") {
        table = false;
        return "\n";
    } else if (tag == "</td>" || tag == "</th>") {
        return " | ";
    } else if (tag == "<tr>") {
        string cell = "";
        if (row == 1) {
            while (!tableCache.empty()) {
                cell += tableCache.front();
                tableCache.pop();
            }
        }  
        cell += "\n| ";
        row++;
        return cell;
    }
    return "";
}

bool CMDConverter::writeResults(void) {
    ofstream outfile(outFile);
    if (outfile.fail()) {
        error.printMessage(error.fileCreateError(outFile));
        outfile.close();
        return false;
    }

    for (const auto &result : results)
        outfile << result;
    outfile.close();
    return true;
}

CMDConverter::CMDConverter(const string &outFile) :
    outFile(outFile),
    table(false),
    row(0),
    tab(0) {}

CMDConverter::CMDConverter(const string &outFile, vector<string> files) :
    outFile(outFile),
    files(files),
    table(false),
    row(0),
    tab(0) {}

bool CMDConverter::convert(vector<unique_ptr<CTag>> &tags) {
    int lineNumber = 1;
    for (const auto &tag : tags) {
        string content = tag->getContent();

        if (!checkTags(content, tag->getType(), lineNumber))
            return false;

        if (tagChecker.isLink(content)) {
            results.push_back(convertLink(content, tag->getAtribute()));

        } else if (tagChecker.isParagraph(content)) {
            results.push_back(convertParagraph(content));

        } else if (tagChecker.isBold(content)) {
            results.push_back(convertBold(content));

        } else if (tagChecker.isItalic(content)) {
            results.push_back(convertItalic(content));

        } else if (tagChecker.isHeading(content)) {
            results.push_back(convertHeading(content, tag->getAtribute()));

        } else if (tagChecker.isImage(content)) {
            results.push_back(convertImage(content, tag->getAtribute()));

        } else if (tagChecker.isList(content)) {
            results.push_back(convertList(content));

        } else if (tagChecker.isTable(content)) {
            results.push_back(convertTable(content));

        } else if (content == "/n" && !table && tab == 0) {
            results.push_back("\n");
            
        } else if (content != "/n" && content != "/c") {
            results.push_back(content);
            if (table && row == 1 && content.length() != 0) {
                if (tableCache.empty())
                    tableCache.push("\n| ");
                tableCache.push(string(content.length(), '-') + " | ");
            }
        }   

        if (content == "/c")
            lineNumber++;
    }

    if (!openTags.empty()) {
        error.printMessage(error.invalidTag(openTags.top().second));
        return false;
    }

    return writeResults();
}
