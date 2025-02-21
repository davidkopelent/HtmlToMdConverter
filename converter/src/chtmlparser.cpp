/**
 * chtmlparser.cpp
 * Title: HTML parser class implementation
 * Author: David Kopelent
 */

#include "chtmlparser.h"
using namespace std;

CHtmlParser::CHtmlParser(const string &fileName) :
    CDocument(fileName) {}

bool CHtmlParser::parse(string line) {
    bool printSpace = true;

    if (!line.empty()) {
        size_t tabs = line.find_first_not_of(" \t");
        if (tabs != string::npos)
            line = line.substr(tabs, line.length()-tabs);

        int it = 0;
        while (true) {
            size_t start = line.find_first_of("<");
            size_t end = line.find_first_of(">");

            if (start == string::npos || end == string::npos) {
                if (!line.empty()) {
                    size_t trim = line.find_first_not_of(" \t");
                    trim = (trim != string::npos) ? trim : line.length();
                    tags.push_back(unique_ptr<CTag>(new CHtmlTag(line.substr(trim, line.length()-trim), "text")));
                }
                break;
            }

            if ((start != string::npos && end == string::npos) || (start == string::npos && end != string::npos)) {
                error.printMessage(error.invalidTag(lineNumber));
                return false;
            }

            if (start != 0 && it == 0) {
                tags.push_back(unique_ptr<CTag>(new CHtmlTag(" " + line.substr(0, start), "text")));
                line = line.substr(start, line.length()-start);
                end = end - start;
                start = 0;
            }
          
            CTag * tag = new CHtmlTag(line.substr(start, end-start+1));
            if (!tag->parseTag(lineNumber)) {
                error.printMessage(error.invalidTag(lineNumber));
                delete tag;
                return false;
            }

            if (tag->getContent().empty() && tag->getType() != "unknown")
                printSpace = false;

            tags.push_back(unique_ptr<CTag>(tag));
            line = line.substr(end+1, line.length()-end-1);

            if (!line.empty() && line.at(0) != '<') {
                size_t contentStart = line.find_first_of("<");
                contentStart = (contentStart != string::npos) ? contentStart : line.length();
                tags.push_back(unique_ptr<CTag>(new CHtmlTag(line.substr(0, contentStart), "text")));
                line = line.substr(contentStart, line.length()-contentStart);
            }
            it++;
        }
    }

    if (printSpace)
        tags.push_back(unique_ptr<CTag>(new CHtmlTag("/n")));
    tags.push_back(unique_ptr<CTag>(new CHtmlTag("/c")));
    return true;
}
