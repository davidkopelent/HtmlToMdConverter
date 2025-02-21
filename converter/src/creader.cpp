/**
 * creader.cpp
 * Title: Input reader class implementation
 * Author: David Kopelent
 */

#include "creader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

CReader::CReader(void) : 
    destinationName("./")
{
}   

void CReader::clean(void) {
    while (!files.empty())
        files.pop();
    filesToConvert.clear();
}

bool CReader::convertFile(const string &fileName) {
    message.printMessage(message.convertingFile(fileName));

    if (fileCheck.checkEmptyFile(fileName)) {
        error.printMessage(error.emptyFile(fileName));
        return false;
    }

    if (conversionType == HTML_TO_MARKDOWN) {
        if (!fileCheck.checkHtmlExtension(fileName)) {
            error.printMessage(error.invalidFile(fileName));
            return false;
        }

        CDocument * document = new CHtmlParser(fileName);;
        if (!document->process(new CMDConverter(fileName.substr(0, fileName.find_last_of(".")) + "-converted.md", filesToConvert))) {
            delete document;
            return false;
        }
        delete document;
    } else if (conversionType == MARKDOWN_TO_HTML) {
        if (!fileCheck.checkMarkDownExtension(fileName)) {
            error.printMessage(error.invalidFile(fileName));
            return false;
        }

        CDocument * document = new CMDParser(fileName);
        if (!document->process(new CHtmlConverter(fileName.substr(0, fileName.find_last_of(".")) + "-converted.html", filesToConvert))) {
            delete document;
            return false;
        }
        delete document;
    }

    message.printMessage(message.conversionSuccessfull());
    convertedFilesCount++;
    return true;
}

bool CReader::convert(void) {
    int filesTotal = 0;
    while (!files.empty()) {
        if (!files.front().empty()) {
            if (conversionType == HTML_TO_MARKDOWN) {
                if (fileCheck.checkHtmlExtension(files.front())) {
                    filesToConvert.push_back(files.front());
                    filesTotal++;
                } else {
                    warning.printMessage(warning.invalidFileExtension(files.front()));
                }
            } else if (conversionType == MARKDOWN_TO_HTML) {
                if (fileCheck.checkMarkDownExtension(files.front())) {
                    filesToConvert.push_back(files.front());
                    filesTotal++;
                } else {
                    warning.printMessage(warning.invalidFileExtension(files.front()));
                }
            }
        }
        files.pop();
    }

    for (const auto &file : filesToConvert)
        convertFile(file);
    
    message.printMessage(message.successRate(convertedFilesCount, filesTotal));
    return true;
}

bool CReader::convertFiles(void) {
    string newFile;
    message.printMessage(message.convertFilesMenu());

    int filesTotal = 0;
    while (getline(cin, newFile)) {
        if (filesTotal > LIMIT) {
            error.printMessage(error.limitExceeded());
            return false;
        }

        if (newFile == CONVERT_EXECUTE || newFile == CONVERT_EXECUTE.substr(0,2) || newFile.empty())
            break;

        files.push(newFile);
        filesTotal++;
    }

    if (files.empty() || filesTotal == 0) {
        error.printMessage(error.invalidInput());
        return false;
    }

    return convert();
}

bool CReader::convertFolder(void) {
    string folder;
    message.printMessage(message.convertFolderMenu());

    if (!getline(cin, folder))
        return false;
        
    destinationName = (folder.empty()) ? destinationName : folder;
    int filesTotal = 0;

    try {
        for (auto const &file : filesystem::directory_iterator(folder, filesystem::directory_options::skip_permission_denied)) {
            if (filesTotal > LIMIT) {
                error.printMessage(error.limitExceeded());
                return false;
            }
            
            if (filesystem::is_regular_file(file)) {
                files.push(file.path());
                filesTotal++;
            }
        }

        if (filesTotal == 0) {
            error.printMessage(error.emptyFolder(folder));
            return false;
        }
    } catch (const filesystem::filesystem_error &errorFolder) {
        error.printMessage(error.invalidFolder(errorFolder.path1()));
        return false;
    }

    return convert();
}

bool CReader::convertFolderRecursively(void) {
    string folder;
    message.printMessage(message.convertFolderMenu());

    if (!getline(cin, folder))
        return false;

    destinationName = (folder.empty()) ? destinationName : folder;
    int filesTotal = 0;

    try {
        for (const auto &file : filesystem::recursive_directory_iterator(folder, filesystem::directory_options::skip_permission_denied)) {
            if (filesTotal > LIMIT) {
                error.printMessage(error.limitExceeded());
                return false;
            }
            
            if (filesystem::is_regular_file(file)) {
                files.push(file.path());
                filesTotal++;
            }
        }

        if (filesTotal == 0) {
            error.printMessage(error.emptyFolder(folder));
            return false;
        }
    } catch (const filesystem::filesystem_error &errorFolder) {
        error.printMessage(error.invalidFolder(errorFolder.path1()));
        return false;
    }

    return convert();
}

bool CReader::inputController(void) {
    string operation;
    message.printMessage(message.operation());

    if (!getline(cin, operation))
        return false;

    if (operation == FOLDER_CONVERT) {
        if (!convertFolder())
            return false;
    } else if (operation == FOLDER_RECURSIVE_CONVERT) {
        if (!convertFolderRecursively())
            return false;
    } else if (operation == FILE_CONVERT) {
        if (!convertFiles())
            return false;
    } else {
        warning.printMessage(warning.unkwnownOperation(operation));
        return false;
    }

    return true;
}

bool CReader::processInput(void) {
    while (true) {
        clean();
        convertedFilesCount = 0;
        message.printMessage(message.menu());

        if (!getline(cin, conversionType))
            return false;

        if (conversionType == EXIT) {
            break;
        } else if (conversionType == HTML_TO_MARKDOWN || conversionType == MARKDOWN_TO_HTML) {
            inputController();
        } else {
            warning.printMessage(warning.unkwnownConversion(conversionType));
        }

        if (cin.eof())
            break;
    }
    return true;
}
