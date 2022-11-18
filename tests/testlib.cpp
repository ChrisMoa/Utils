#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <StringUtils.hpp>
#include <string>
#include <FileSystemUtils.h>

TEST_CASE("Quick check", "[main]")
{
    std::vector<double> values{1, 2., 3.};
    // auto [mean, moment] = accumulate_vector(values);

    // REQUIRE( mean == 2.0 );
    // REQUIRE( moment == Approx(4.666666) );
}

TEST_CASE("String test", "[StringUtils]")
{
    std::string list = "a/b/c/d";
    std::string list2 = "a/b/c/d/";

    std::vector<std::string> shouldList = {"a", "b", "c", "d"};

    auto isList = String::ExtendedString::extractList(list, "/");
    auto isList2 = String::ExtendedString::extractList(list2, "/");
    REQUIRE(isList == shouldList);
    REQUIRE(isList2 == shouldList);

    std::vector<std::string> list3 = {"a", "b", "c"};
    std::string shouldString3 = "a/b/c/";
    auto isString3 = String::ExtendedString::listToString(list3, "/");
    REQUIRE(isString3 == shouldString3);
}

TEST_CASE("Log test", "[LogUtils]")
{
    // using namespace Log;
    // auto logger = shared_ptr<ILogger>(new LoggerConsole());
    // logger->setLogLevel(Log::LogEntry::Level::TRACE);
    // Log::LoggerManager::getInstance()->addLogger(logger);
    // DEBUG("Logger created");
    // TRACE("Text");
    // DEBUG("Text");
    // LINFO("Text");
    // WARNING("Text");
    // ERROR("Text");
    REQUIRE(true);
}

TEST_CASE("Filesystem test", "[FilesystemUtils]")
{
    std::string exePath = Util::getExePath();
    auto exePathSould = "/home/chrismintpc/Projects/Utils/build/tests";
    REQUIRE(exePath == exePathSould);

    auto exePathStrings = Util::getExePathStrings();
    std::vector<std::string> exePathStringsShould = {"/", "home", "chrismintpc", "Projects", "Utils", "build", "tests"};
    REQUIRE(exePathStrings == exePathStringsShould);

    /* Also tested:
    - getSubDirectoriesAbs(exePath);
    - getSubDirectoriesRel
    - getSubFilesAbs
    - getSubFilesRel
    - createFileInDirectory
    - createFolderInDirectory
    - getFilenameOfName
    - getDirOfName
    - fileExists
    */
}
