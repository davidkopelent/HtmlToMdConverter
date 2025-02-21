/**
 * cfilecheck.h
 * Title: Interface for file check class
 * Description: Class is used to check valid file extension and file contents
 * Author: David Kopelent
 */

#ifndef CFILECHECK
#define CFILECHECK
#include "config.h"
#include <string>
using namespace std;

class CFileCheck {
public:
    /**
     * Default constructor
     */
    CFileCheck(void) = default;

    /**
     * Default destructor
     */
    ~CFileCheck(void) = default;

    /**
     * Check if file is not empty
     * @param fileName name of the file to be checked
     * @return bool
    */
    bool checkEmptyFile(const string &fileName);

    /**
     * Check HTML file extension
     * @param fileName name of the file to be checked
     * @return bool
     */
    bool checkHtmlExtension(const string &fileName);

    /**
     * Check MarkDown file extension
     * @param fileName name of the file to be checked
     * @return bool
     */
    bool checkMarkDownExtension(const string &fileName);
};
#endif