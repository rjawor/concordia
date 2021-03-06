#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>

#include "concordia/concordia.hpp"
#include "concordia/substring_occurence.hpp"
#include "concordia/common/config.hpp"
#include "concordia/common/utils.hpp"
#include "build/libdivsufsort/include/divsufsort.h"

#define READ_BUFFER_LENGTH 10000

namespace po = boost::program_options;

void reportError(long lineNumber, const std::string & error) {
    std::stringstream ss;
    ss << "Search error in line " << lineNumber << ": " << error;
    throw ConcordiaException(ss.str());
}

void checkConcordiaResults(
        const std::vector<ConcordiaSearchResult> & results,
        long baseLineCount) {
    long lineIndex = 1;
    BOOST_FOREACH(ConcordiaSearchResult result, results) {
        SUFFIX_MARKER_TYPE patternSize = result.getTokenVector().size();

        if (result.getBestOverlay().size() != 1) {
            reportError(baseLineCount + lineIndex,
                       "best overlay has more than one fragment.");
        }
        if (result.getBestOverlay().at(0).getMatchedLength()
             != patternSize) {
            reportError(baseLineCount + lineIndex,
                   "best overlay fragment has different size than pattern.");
        }
        if (result.getBestOverlayScore() != 1) {
            reportError(baseLineCount + lineIndex,
                   "best overlay score is not 1.");
        }
        if (result.getFragments().size() == 0) {
            reportError(baseLineCount + lineIndex,
                   "there are no matched fragments.");
        }
        if (result.getFragments().at(0).getMatchedLength()
             != patternSize) {
            reportError(baseLineCount + lineIndex,
                   "the first fragment does not cover the whole pattern.");
        }
    }
}

void performSearch(Concordia & concordia,
                   std::vector<std::string> & buffer,
                   long lineCount) {
    long baseLineCount = 0;
    if (lineCount % READ_BUFFER_LENGTH == 0) {
        baseLineCount = lineCount - READ_BUFFER_LENGTH;
    } else {
        baseLineCount = (lineCount / READ_BUFFER_LENGTH)
                          * READ_BUFFER_LENGTH;
    }
    std::vector<ConcordiaSearchResult> results;
    boost::posix_time::ptime timeStart =
       boost::posix_time::microsec_clock::local_time();
    // perform searching
    BOOST_FOREACH(std::string pattern, buffer) {
        results.push_back(*concordia.concordiaSearch(pattern));
    }
    boost::posix_time::ptime timeEnd =
        boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration msdiff =
                                    timeEnd - timeStart;

    int sentencesSearched = buffer.size();
    buffer.clear();

    long timeElapsed = msdiff.total_milliseconds();
    double speed = static_cast<double>(
                        1000 * sentencesSearched / timeElapsed);
    std::cout << "\tSearched a portion of " <<
          sentencesSearched << " sentences in "
          << timeElapsed << "ms. The speed: " <<
          speed << " sentences per second" << std::endl;
    std::cout << "\tChecking this portion..." << std::endl;
    checkConcordiaResults(results, baseLineCount);
    std::cout << "\tno errors." << std::endl;
    std::cout << "\tTotal search progress: " <<
          lineCount << " sentences searched." << std::endl;
}

int main(int argc, char** argv) {
    po::options_description desc("Allowed options");

    desc.add_options()
        ("help,h", "Display this message")
        ("config,c", boost::program_options::value<std::string>(),
                                 "Concordia configuration file (required)")
        ("simple-search,s", boost::program_options::value<std::string>(),
                                 "Pattern to be searched in the index")
        ("silent,n",
            "While searching with simple-search, do not output search results")
        ("anubis-search,a", boost::program_options::value<std::string>(),
                        "Pattern to be searched by anubis search in the index")
        ("concordia-search,x", boost::program_options::value<std::string>(),
                     "Pattern to be searched by concordia search in the index")
        ("read-file,r", boost::program_options::value<std::string>(),
                                 "File to be read and added to index")
        ("test,t", boost::program_options::value<std::string>(),
                              "Run performance and correctness tests on file");

    po::variables_map cli;
    po::store(po::parse_command_line(argc, argv, desc), cli);
    po::notify(cli);

    if (cli.count("help")) {
        std::cerr << desc << std::endl;
        return 1;
    }

    std::string configFile;
    if (cli.count("config")) {
        configFile = cli["config"].as<std::string>();
    } else {
        std::cerr << "No Concordia configuration file given. Terminating."
                                                                << std::endl;
        return 1;
    }


    try {
        std::cout << "\tInitializing concordia..." << std::endl;
        boost::posix_time::ptime time_start =
                        boost::posix_time::microsec_clock::local_time();
        Concordia concordia(configFile);
        boost::posix_time::ptime time_end =
                        boost::posix_time::microsec_clock::local_time();
        boost::posix_time::time_duration msdiff = time_end - time_start;
        std::cout << "\tInitialization (loading index from disk "
                      << "and regenerating SA) took: "
                      << msdiff.total_milliseconds() << "ms." << std::endl;

        std::cout << "\tWelcome to Concordia. Version = "
                  << concordia.getVersion() << std::endl;
        if  (cli.count("simple-search")) {
            std::string pattern = cli["simple-search"].as<std::string>();
            std::cout << "\tSearching for pattern: \"" << pattern <<
                                                          "\"" << std::endl;
            time_start = boost::posix_time::microsec_clock::local_time();
            std::vector<SubstringOccurence> result =
                                             concordia.simpleSearch(pattern);
            time_end = boost::posix_time::microsec_clock::local_time();
            msdiff = time_end - time_start;
            std::cout << "\tFound: " << result.size() << " matches. "
            << "Search took: " <<
                          msdiff.total_milliseconds() << "ms." << std::endl;
            if (!cli.count("silent")) {
                BOOST_FOREACH(SubstringOccurence occurence, result) {
                    std::cout << "\t\tfound match in sentence number: "
                              << occurence.getId() << std::endl;
                }
            }
        } else if  (cli.count("anubis-search")) {
            std::string pattern = cli["anubis-search"].as<std::string>();
            std::cout << "\tAnubis searching for pattern: \"" << pattern <<
                                                          "\"" << std::endl;
            time_start = boost::posix_time::microsec_clock::local_time();
            std::vector<AnubisSearchResult> result =
                                             concordia.anubisSearch(pattern);
            time_end = boost::posix_time::microsec_clock::local_time();
            msdiff = time_end - time_start;
            std::cout << "\tFound: " << result.size() << " matches. "
            << "Search took: " <<
                          msdiff.total_milliseconds() << "ms." << std::endl;
            if (!cli.count("silent")) {
                BOOST_FOREACH(AnubisSearchResult searchResult, result) {
                    std::cout << "\t\tfound matching sentence number: "
                              << searchResult.getExampleId()
                              << ", score: " << searchResult.getScore()
                              << std::endl;
                }
            }
        } else if  (cli.count("concordia-search")) {
            std::string pattern = cli["concordia-search"].as<std::string>();
            std::cout << "\tConcordia searching for pattern: \"" << pattern <<
                                                          "\"" << std::endl;
            time_start = boost::posix_time::microsec_clock::local_time();
            boost::shared_ptr<ConcordiaSearchResult> result =
                                             concordia.concordiaSearch(pattern);
            time_end = boost::posix_time::microsec_clock::local_time();
            msdiff = time_end - time_start;

            std::cout << "\tPattern used: " << std::endl << "\t\t";
            BOOST_FOREACH(std::string token, result->getTokenVector()) {
                std::cout << token << " ";
            }
            std::cout << std::endl;

            std::cout << "\tFound: " << result->getFragments().size()
                << " fragments. "  << "Search took: " <<
                          msdiff.total_milliseconds() << "ms." << std::endl;
            if (!cli.count("silent")) {
                std::cout << "\tBest overlay (score="<<
                    result->getBestOverlayScore()<< "): " << std::endl;
                BOOST_FOREACH(MatchedPatternFragment fragment,
                              result->getBestOverlay()) {
                    std::cout << "\t\tfragment [" << fragment.getStart()
                              << "," << fragment.getEnd()
                              << "] (exampleId, exampleOffset,"
                              << " patternOffset, length): "
                              << fragment.getExampleId() << ","
                              << fragment.getExampleOffset() << ","
                              << fragment.getPatternOffset() << ","
                              << fragment.getMatchedLength()
                              << std::endl;
                }

                std::cout << "\tAll pattern fragments: " << std::endl;
                BOOST_FOREACH(MatchedPatternFragment fragment,
                              result->getFragments()) {
                    std::cout << "\t\tfragment [" << fragment.getStart()
                              << "," << fragment.getEnd()
                              << "] (exampleId, exampleOffset,"
                              << " patternOffset, length): "
                              << fragment.getExampleId() << ","
                              << fragment.getExampleOffset() << ","
                              << fragment.getPatternOffset() << ","
                              << fragment.getMatchedLength()
                              << std::endl;
                }
            }
        } else if (cli.count("read-file")) {
            std::string filePath = cli["read-file"].as<std::string>();
            std::cout << "\tReading sentences from file: " << filePath <<
                                                                  std::endl;
            std::ifstream text_file(filePath.c_str());
            std::string line;
            if (text_file.is_open()) {
                long lineCount = 0;
                std::vector<Example> buffer;
                boost::posix_time::ptime timeStart =
                            boost::posix_time::microsec_clock::local_time();
                while (getline(text_file, line)) {
                    lineCount++;
                    buffer.push_back(Example(line, lineCount));
                    if (lineCount % READ_BUFFER_LENGTH == 0) {
                        concordia.addAllExamples(buffer);
                        buffer.clear();
                        boost::posix_time::ptime timeEnd =
                            boost::posix_time::microsec_clock::local_time();
                        boost::posix_time::time_duration msdiff =
                                                        timeEnd - timeStart;
                        long timeElapsed = msdiff.total_milliseconds();
                        double speed = static_cast<double>(
                                            1000 * lineCount / timeElapsed);
                        std::cout << "\tRead and added to index " <<
                                  lineCount << " sentences in " << timeElapsed
                                  << "ms. Current speed: " << speed <<
                                  " sentences per second" << std::endl;
                    }
                }
                if (buffer.size() > 0) {
                    concordia.addAllExamples(buffer);
                }
                text_file.close();
                boost::posix_time::ptime timeTotalEnd =
                             boost::posix_time::microsec_clock::local_time();
                boost::posix_time::time_duration totalMsdiff =
                                                    timeTotalEnd - timeStart;
                long totalTimeElapsed = totalMsdiff.total_milliseconds();
                double totalSpeed =
                      static_cast<double>(1000 * lineCount / totalTimeElapsed);
                std::cout << "\tReading finished. Read and added to index "
                  << lineCount << " sentences in " << totalTimeElapsed <<
                  "ms. Overall speed: " << totalSpeed <<
                  " sentences per second" << std::endl;
             } else {
                    std::cerr << "Unable to open file: "<< filePath;
                    return 1;
             }
        } else if (cli.count("test")) {
            std::string filePath = cli["test"].as<std::string>();
            std::cout << "\tTesting on file: " << filePath <<
                                                     std::endl;
            // adding to index
            std::ifstream text_file(filePath.c_str());
            std::string line;
            if (text_file.is_open()) {
                long lineCount = 0;
                std::vector<Example> buffer;
                boost::posix_time::ptime timeStart =
                            boost::posix_time::microsec_clock::local_time();
                while (getline(text_file, line)) {
                    lineCount++;
                    buffer.push_back(Example(line, lineCount));
                    if (lineCount % READ_BUFFER_LENGTH == 0) {
                        concordia.addAllExamples(buffer);
                        buffer.clear();
                        boost::posix_time::ptime timeEnd =
                            boost::posix_time::microsec_clock::local_time();
                        boost::posix_time::time_duration msdiff =
                                                        timeEnd - timeStart;
                        long timeElapsed = msdiff.total_milliseconds();
                        double speed = static_cast<double>(
                                            1000 * lineCount / timeElapsed);
                        std::cout << "\tRead and added to index " <<
                                  lineCount << " sentences in " << timeElapsed
                                  << "ms. Current speed: " << speed <<
                                  " sentences per second" << std::endl;
                    }
                }
                if (buffer.size() > 0) {
                    concordia.addAllExamples(buffer);
                }
                text_file.close();
                boost::posix_time::ptime timeTotalEnd =
                             boost::posix_time::microsec_clock::local_time();
                boost::posix_time::time_duration totalMsdiff =
                                                    timeTotalEnd - timeStart;
                long totalTimeElapsed = totalMsdiff.total_milliseconds();
                double totalSpeed =
                      static_cast<double>(1000 * lineCount / totalTimeElapsed);
                std::cout << "\tReading finished. Read and added to index "
                  << lineCount << " sentences in " << totalTimeElapsed <<
                  "ms. Overall speed: " << totalSpeed <<
                  " sentences per second" << std::endl;
            } else {
                   std::cerr << "Unable to open file: "<< filePath;
                   return 1;
            }

            // generating SA
            std::cout << "\tGenerating SA from RAM..." << std::endl;
            boost::posix_time::ptime SAStart =
                boost::posix_time::microsec_clock::local_time();
            concordia.refreshSAfromRAM();
            boost::posix_time::ptime SAEnd =
                boost::posix_time::microsec_clock::local_time();
            boost::posix_time::time_duration SAdiff =
                                            SAEnd - SAStart;
            long SAtimeElapsed = SAdiff.total_milliseconds();
            std::cout << "\tSA generated in " << SAtimeElapsed
                      << "ms." << std::endl;

            // searching
            std::ifstream test_file(filePath.c_str());
            if (test_file.is_open()) {
                long lineCount = 0;
                std::vector<std::string> buffer;
                while (getline(test_file, line)) {
                    lineCount++;
                    buffer.push_back(line);
                    if (lineCount % READ_BUFFER_LENGTH == 0) {
                        performSearch(concordia, buffer, lineCount);
                    }
                }
                if (buffer.size() > 0) {
                    performSearch(concordia, buffer, lineCount);
                }
                test_file.close();
                std::cout << "\tSearching finished. No errors reported."
                  << std::endl;

            } else {
                   std::cerr << "Unable to open file: "<< filePath;
                   return 1;
            }

        } else {
            std::cerr << "One of the options: simple-search, anubis-search, "
                      << "concordia-search or read-file must be provided."
                      << "See the options specification: "
                      << std::endl << desc << std::endl;
            return 1;
        }

        std::cout << "\tConcordia operation completed without errors."
                                                                << std::endl;
    } catch(ConcordiaException & e) {
        std::cerr << "ConcordiaException caught with message: "
                  << std::endl
                  << e.what()
                  << std::endl
                  << "Terminating execution."
                  << std::endl;
        return 1;
    } catch(std::exception & e) {
        std::cerr << "Unexpected exception caught with message: "
                  << std::endl
                  << e.what()
                  << std::endl
                  << "Terminating execution."
                  << std::endl;
        return 1;
    }
    return 0;
}
