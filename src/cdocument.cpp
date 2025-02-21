/**
 * cdocument.cpp
 * Title: Document class implementation
 * Author: David Kopelent
 */

#include "cdocument.h"
using namespace std;

CDocument::CDocument(const string &fileName) :
    fileName(fileName),
    lineNumber(1) {}
