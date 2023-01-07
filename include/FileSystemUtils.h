//
// Created by chris-tab on 11.05.21.
//

#ifndef FILESYSTEMUTILS_H
#define FILESYSTEMUTILS_H

#define UNIX

#include <string>
#include <vector>

namespace Util {

/**
 * @brief get the path to the app
 * @param void
 * @return the path string
 */
std::string getExePath(void);

/**
 * @brief get the path to the app where every subdirecory is stored in the vector
 * @param  void
 * @return the path container
 */
std::vector< std::string > getExePathStrings(void);

/**
 * @brief get the subdirectories of the given path with absolut path
 * @param path the path which defines where to get the subdirectories
 * @return subdirectory container
 */
std::vector< std::string > getSubDirectoriesAbs(std::string path);

/**
 * @brief get the subdirectories of the given path with relative path
 * @param path the path which defines where to get the subdirectories
 * @return subdirectory container
 */
std::vector< std::string > getSubDirectoriesRel(std::string path);

/**
 * @brief get all files of the given path with absolut path
 * @param path the path which defines where to get the subdirectories
 * @return files container
 */
std::vector< std::string > getSubFilesAbs(std::string path);

/**
 * @brief get all files of the given path with relative path
 * @param path the path which defines where to get the subdirectories
 * @return files container
 */
std::vector< std::string > getSubFilesRel(std::string path);

/**
 * @brief creates a new folder in a subdirectory given by relPath
 * @param foldername the foldername
 * @param relPath the path which defines where to write the folder
 * @return void
 */
void createFolderInDirectory(std::string foldername, std::string relPath = "");

/**
 * @brief creates a new file in a subdirectory given by relPath
 * @param filename the filename (contains the name itself and also fileextension)
 * @param relPath the path which defines where to write the file
 * @return void
 */
void createFileInDirectory(std::string filename, std::string relPath = "");

/**
 * @brief get the filename and extension of the given path string name
 * @param name the path string
 * @return the filename and extension
 */
std::string getFilenameOfName(std::string name);

/**
 * @brief get the directory of the given path string name
 * @param name the path string
 * @return the extraced path of name
 */
std::string getDirOfName(std::string name);

/**
 * @brief checks if a file exists (path and filename are allowed)
 * @param filename the filename
 * @return true if file exists
 */
bool fileExists(std::string filename);

/**
 * @brief removes the file from the filesystem
 * @param filename the filename which should be removed
 * @return void
 */
void removeFile(std::string filename);

/**
 * @brief renames or moves a file from the originFileName to the newFileName
 * @param originFilename the origin filename
 * @param newFilename the new filename
 * @return void
 */
void renameFile(std::string originFilename, std::string newFilename);

/**
 * @brief copys the originFileName to copyFileName
 * @param originFilename the origin filename
 * @param copyFilename the copied file
 * @return void
 */
void copyFile(std::string originFilename, std::string copyFilename);

}  // namespace Util

#endif  // FILESYSTEMUTILS_H
