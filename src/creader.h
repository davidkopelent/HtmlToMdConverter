/**
 * creader.h
 * Title: Interface for input reader
 * Description: Class to comunicate with user and process conversion
 * Author: David Kopelent
 */

#ifndef CREADER
#define CREADER
#include "config.h"
#include "cmessage.h"
#include "cfilecheck.h"
#include "cdocument.h"
#include "chtmlparser.h"
#include "cmdparser.h"
#include "chtmlconverter.h"
#include "cmdconverter.h"
#include <string>
#include <queue>
#include <vector>
using namespace std;

class CReader {
private:
    // Number of successfuly converted files
    int convertedFilesCount;
    
    // Queue to save files for converting
    queue<string> files;

    vector<string> filesToConvert;

    // Folder with files for converting
    string folder;

    // Convert HTML to MarkDown / MarkDown to HTML
    string conversionType;

    // Folder in which converted document will be saved
    string destinationName;

    // File check class
    CFileCheck fileCheck;

    // Message class
    CMessage message;

    // Warning message class
    CWarningMessage warning;

    // Error message class
    CErrorMessage error;

    /**
     * Convert file
     * @param fileName name of file that will be converted
     * @return TRUE if conversion was successfull / FALSE if problem occured
     */
    bool convertFile(const string &fileName);

    bool convert(void);

    /**
     * Convert files one by one
     * @return TRUE if conversion was successfull / FALSE if problem occured
     */
    bool convertFiles(void);

    /**
     * Convert files in folder
     * @return TRUE if conversion was successfull / FALSE if problem occured
     */
    bool convertFolder(void);

    /**
     * Convert files in folder recursively
     * @return TRUE if conversion was successfull / FALSE if problem occured
     */
    bool convertFolderRecursively(void);

    /**
     * Call methods based on operation
     * @return TRUE if no problem occured
     */
    bool inputController(void);

public:
    /**
     * Constructor
     */
    CReader(void);

    /**
     * Destructor
     */
    ~CReader(void) = default;

    /**
     * Process input from user
     * @return TRUE if no problem occured
     */
    bool processInput(void);

    /**
     * Cleans unused memory and data
    */
    void clean(void);
};
#endif
