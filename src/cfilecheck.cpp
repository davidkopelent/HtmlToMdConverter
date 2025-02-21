/**
 * cfilecheck.cpp
 * Title: File check class implementation
 * Author: David Kopelent
 */

#include "cfilecheck.h"
#include <iostream>
#include <fstream>
using namespace std;

bool CFileCheck::checkEmptyFile(const string &fileName) {
    ifstream file (fileName, ios::in);
    if (file.peek() == ifstream::traits_type::eof()) {
        file.close();
        return true;
    }
    file.close();
    return false;
}

bool CFileCheck::checkHtmlExtension(const string &fileName) {
    return (fileName.substr(fileName.find_last_of(".") + 1) == "html");
}

bool CFileCheck::checkMarkDownExtension(const string &fileName) {
    return (fileName.substr(fileName.find_last_of(".") + 1) == "md");
}
