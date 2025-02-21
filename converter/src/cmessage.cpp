/**
 * cmessage.cpp
 * Title: Message class implementation
 * Author: David Kopelent
 */

#include "cmessage.h"
using namespace std;

string CMessage::successRate(const int convertedFilesCount, const int filesTotal) {
    return "\n\033[3;42;30m SUCCESSFULLY CONVERTED: " + to_string(convertedFilesCount) + "/" + to_string(filesTotal) + " FILES \033[0m";
}

string CMessage::conversionSuccessfull(void) {
    return "👍 \x1B[32mSUCCESS!\033[0m";
}

string CMessage::convertingFile(const string &fileName) {
    return "\n\x1B[32mConverting file: \033[0m" + fileName;
}

string CMessage::convertFilesMenu(void) {
    return "\n\033[3;47;30m Files (Start conversion [START/ST/SPACE]): \033[0m";
}

string CMessage::convertFolderMenu(void) {
    return "\n\033[3;47;30m Folder name: \033[0m";
}

string CMessage::operation(void) {
    return "\n\033[3;47;30m Convert (Folder [DIR], Folder recursively [RDIR], File/s [FILE]): \033[0m";
}

string CMessage::menu(void) {
    return "\n\033[3;47;30m New conversion (HTML -> MarkDown [HTML],  MarkDown -> HTML [MD], Exit program -> [EXIT]): \033[0m";
}

void CMessage::printMessage(const string &message) {
    cout << message << endl;
}

/* ------------------------------------------------------------------------------------------ */

string CWarningMessage::unkwnownConversion(const string &input) {
    return "Unknown conversion type '" + input + "'!";
}

string CWarningMessage::unkwnownOperation(const string &input) {
    return "Unknown operation '" + input + "'!";
}

string CWarningMessage::invalidFileExtension(const string &fileName) {
    return "Invalid file extension in file '" + fileName + "' [skipping]!";
}

string CWarningMessage::formatingWarning(const int &lineNumber) {
    return "Formating on line " + to_string(lineNumber) + " is probably not correct [skipping]!";
}

string CWarningMessage::formatingNotSupported(const string &formating, const int &lineNumber) {
    return "Formating '" + formating + "' on line " + to_string(lineNumber) + " is not supported!";
}

void CWarningMessage::printMessage(const string &message) {
    cout << "\x1B[33mWARNING: \033[0m" << message << endl;
}

/* ------------------------------------------------------------------------------------------ */

string CErrorMessage::invalidInput(void) {
    return "Invalid input!";
}

string CErrorMessage::fileOpenError(const string &fileName) {
    return "File '" + fileName + "' cannot be open!";
}

string CErrorMessage::fileCreateError(const string &fileName) {
    return "File '" + fileName + "' cannot be created!";
}

string CErrorMessage::emptyFile(const string &fileName) {
    return "File '" + fileName + "' is empty or doesn't exists! [skipping]";
}

string CErrorMessage::emptyFolder(const string &folderName) {
    return "Folder '" + folderName + "' is empty, doesn't exists or no files for conversion found! [skipping]";
}

string CErrorMessage::invalidFile(const string &fileName) {
    return "File '" + fileName + "' is not valid!";
}

string CErrorMessage::invalidFolder(const string &folderName) {
    return "Folder '" + folderName + "' is not valid!";
}

string CErrorMessage::invalidFormat(const string &fileName) {
    return "Invalid file format '" + fileName + "'!";
}

string CErrorMessage::invalidTag(const int &lineNumber) {
    return "Tag is not paired on line " + to_string(lineNumber) + "!";
}

string CErrorMessage::invalidFormating(const int &lineNumber) {
    return "Invalid formating on line " + to_string(lineNumber) + "!";
}

string CErrorMessage::limitExceeded(void) {
    return "Limit of conversions has been exceeded (max. 100 files at once)!";
}

void CErrorMessage::printMessage(const string &message) {
    cout << "❌ \x1B[31mERROR: \033[0m" << message << endl;
}
