/**
 * cmessage.h
 * Title: Interface for message class
 * Description: Class to print program messages
 * Author: David Kopelent
*/

#ifndef CMESSAGE
#define CMESSAGE
#include "config.h"
#include <iostream>
#include <string>
using namespace std;

class CMessage {
public:
    /**
     * Default constructor
    */
    CMessage(void) = default;
    
    /**
     * Virtual destructor
    */
    virtual ~CMessage() = default;

    /**
     * Print conversion success rate - number of successfully converted files
     * @param convertedFilesCount number of successfully converted files
     * @param filesTotal number of converting files
     * @return string
    */
    string successRate(const int convertedFilesCount, const int filesTotal);

    /**
     * Print conversion success message
     * @return string
    */
    string conversionSuccessfull(void);

    /**
     * Print converting file information tab
     * @return string
    */
    string convertingFile(const string &fileName);

    /**
     * Print menu for file conversion
     * @return string
    */
    string convertFilesMenu(void);

    /**
     * Print menu for folder conversion
     * @return string
    */
    string convertFolderMenu(void);

    /**
     * Print menu for operation chose
     * @return string
    */
    string operation(void);

    /**
     * Print main menu - select conversion type
     * @return string
    */
    string menu(void);

    /**
     * Print normal / success message
     * @param message message to print
    */
    virtual void printMessage(const string &message);
};

class CWarningMessage : public CMessage {
public:
    /**
     * Default constructor
    */
    CWarningMessage(void) = default;

    /**
     * Print unknown conversion warning
     * @param input wrong input
     * @return string
    */
    string unkwnownConversion(const string &input);

    /**
     * Print unknown operation warning
     * @param input wrong input
     * @return string
    */
    string unkwnownOperation(const string &input);

    /**
     * Print invalid file extension warning
     * @param fileName name of the file where problem occured
     * @return string
    */
    string invalidFileExtension(const string &fileName);

    /**
     * Print weird formating warning
     * @param lineNumber line where problem occured
     * @return string
     */
    string formatingWarning(const int &lineNumber);

    /**
     * Print unsupported formating warning
     * @param fileName name of the file where problem occured
     * @param lineNumber line where problem occured
     * @return string
     */
    string formatingNotSupported(const string &formating, const int &lineNumber);

    /**
     * Print warning message
     * @param message message to print
    */
    void printMessage(const string &message);
};

class CErrorMessage : public CMessage {
public:
    /**
     * Default constructor
    */
    CErrorMessage(void) = default;

    /**
     * Print invalid user input error
     * @return string
    */
    string invalidInput(void);

    /**
     * Cannot open file error
     * @param fileName name of the invalid file
     * @return string
    */
    string fileOpenError(const string &fileName);

    /**
     * Cannot create file error
     * @param fileName name of the invalid file
     * @return string
    */
    string fileCreateError(const string &fileName);

    /**
     * Print empty file warning
     * @param fileName name of the empty file
     * @return string
     */
    string emptyFile(const string &fileName);

    /**
     * Print empty folder warning
     * @param folderName name of the empty folder
     * @return string
     */
    string emptyFolder(const string &folderName);

    /**
     * Print invalid file warning
     * @param fileName name of the invalid file
     * @return string
     */
    string invalidFile(const string &fileName);

    /**
     * Print invalid folder warning
     * @param folderName name of the invalid folder
     * @return string
     */
    string invalidFolder(const string &folderName);

    /**
     * Print invalid file format or extension warning
     * @param fileName name of the invalid file
     * @return string
     */
    string invalidFormat(const string &fileName);

    /**
     * Print invalid tag warning
     * @param lineNumber line where problem occured
     * @return string
     */
    string invalidTag(const int &lineNumber);

    /**
     * Print invalid formating error
     * @param lineNumber line where problem occured
     * @return string
     */
    string invalidFormating(const int &lineNumber);

    /**
     * Print message while exceeding limit of 100 files converting at once
     * @return string
    */
    string limitExceeded(void);

    /**
     * Print error message
     * @param message message to print
    */
    void printMessage(const string &message);
};
#endif