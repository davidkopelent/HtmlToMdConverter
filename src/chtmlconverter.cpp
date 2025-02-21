/**
 * chtmlconverter.cpp
 * Title: HTML converter class implementation
 * Author: David Kopelent
 */

#include "chtmlconverter.h"
using namespace std;

string CHtmlConverter::addHtmlHead(void) {
    return "<!DOCTYPE html>\n<html>\n<body>\n";
}

string CHtmlConverter::addHtmlFooter(void) {
    return "</body>\n</html>\n";
}

string CHtmlConverter::findLink(string line, const string &atribute) {
    size_t link = line.find(atribute);
    line = line.substr(link + atribute.length() + 2, line.length());
    line = line.substr(0, line.find('"'));
    return line;
}

string CHtmlConverter::convertLink(string line) {
    size_t checkLink = 0;
    while (true) {
        checkLink = line.find("href", (checkLink == 0) ? checkLink : checkLink + 4);
        if (checkLink == string::npos)
            break;

        string link = findLink(line.substr(checkLink, line.length()-checkLink), "href");
        int offset = checkLink + 7 + link.length();
        if (find_if(files.begin(), files.end(), [&](const string& str) { return str.find(link) != string::npos; }) != files.end()) {
            link = link.substr(0, link.find(".")) + "-converted.html";
            line = line.substr(0, checkLink) + "href=\"" + link + "\"" + line.substr(offset, line.length()-offset);
        }
    }
    return line;
}

bool CHtmlConverter::writeResults(vector<unique_ptr<CTag>> &tags) {
    ofstream outfile(outFile);
    if (outfile.fail()) {
        error.printMessage(error.fileCreateError(outFile));
        outfile.close();
        return false;
    }

    outfile << addHtmlHead();
    for (const auto &tag : tags) {
        string line = tag->getContent();
        if (!files.empty())
            line = convertLink(line);
        outfile << line << endl;
    }
    outfile << addHtmlFooter();
    outfile.close();
    return true;
}

CHtmlConverter::CHtmlConverter(const string &outFile) :
    outFile(outFile) {}

CHtmlConverter::CHtmlConverter(const string &outFile, vector<string> files) :
    outFile(outFile),
    files(files) {}

bool CHtmlConverter::convert(vector<unique_ptr<CTag>> &tags) {
    if (!writeResults(tags))
        return false;
    return true;
}
