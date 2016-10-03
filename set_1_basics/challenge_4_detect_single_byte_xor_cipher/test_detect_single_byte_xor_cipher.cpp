#include <gtest/gtest.h>
#include <sstream>
#include "line_extract_streambuf.hpp"
#include <string>
#include <boost/asio.hpp>
#include <strstream>
#include "detect_single_byte_xor_cipher.hpp"
#include "break_single_byte_xor_cipher_recognize_words.hpp"


TEST(LineExtractStreamBuf, ExtractsLinesOneAtATimeAndRewindsProperly)
{
    std::stringstream inputStream;
    inputStream << "Hello world!\n"
                   "This is going to extract\r\n"
                   "a line at a time\r"
                   "even for strings with mixed line-endings\n";

    {
        cryptopals::line_extract_streambuf lineExtractor(inputStream);
        std::istream lineExtractorStream(&lineExtractor);
        std::string line;
        std::getline(lineExtractorStream, line, '\0');
        EXPECT_EQ("Hello world!", line);

        line.clear();
        EXPECT_EQ("", line);
        lineExtractorStream.clear();
        lineExtractorStream.seekg(0);
        std::getline(lineExtractorStream, line, '\0');
        EXPECT_EQ("Hello world!", line);
    }

    {
        cryptopals::line_extract_streambuf lineExtractor(inputStream);
        std::istream lineExtractorStream(&lineExtractor);
        std::string line;
        std::getline(lineExtractorStream, line, '\0');
        EXPECT_EQ("This is going to extract", line);

        line.clear();
        EXPECT_EQ("", line);
        lineExtractorStream.clear();
        lineExtractorStream.seekg(0);
        std::getline(lineExtractorStream, line, '\0');
        EXPECT_EQ("This is going to extract", line);
    }

    {
        cryptopals::line_extract_streambuf lineExtractor(inputStream);
        std::istream lineExtractorStream(&lineExtractor);
        std::string line;
        std::getline(lineExtractorStream, line, '\0');
        EXPECT_EQ("a line at a time", line);

        line.clear();
        EXPECT_EQ("", line);
        lineExtractorStream.clear();
        lineExtractorStream.seekg(0);
        std::getline(lineExtractorStream, line, '\0');
        EXPECT_EQ("a line at a time", line);
    }

    {
        cryptopals::line_extract_streambuf lineExtractor(inputStream);
        std::istream lineExtractorStream(&lineExtractor);
        std::string line;
        std::getline(lineExtractorStream, line, '\0');
        EXPECT_EQ("even for strings with mixed line-endings", line);

        line.clear();
        EXPECT_EQ("", line);
        lineExtractorStream.clear();
        lineExtractorStream.seekg(0);
        std::getline(lineExtractorStream, line, '\0');
        EXPECT_EQ("even for strings with mixed line-endings", line);
    }
}


TEST(DetectSingleByteXorCipher, DetectsAndReturnsLineNumberAndXorByte)
{
    std::string fileContents;
    {
        boost::asio::ip::tcp::iostream challenge4File("cryptopals.com", "http");
        challenge4File << "GET /static/challenge-data/4.txt\r\n" << std::flush;
        std::getline(challenge4File, fileContents, '\0');
    }
    std::istrstream fileRead(fileContents.c_str(), fileContents.size());
    cryptopals::break_single_byte_xor_cipher_recognize_words xorCipherBreaker;
    auto lineNumberScoreAndXorByte =
            cryptopals::detect_single_byte_xor_cipher(std::cout,
                                                      fileRead,
                                                      xorCipherBreaker);
    EXPECT_NE(0, std::get<1>(lineNumberScoreAndXorByte));
    std::cout << "\nMessage was decrypted from line "
              << std::get<0>(lineNumberScoreAndXorByte) + 1
              << " using XOR key "
              << std::hex << int(std::get<2>(lineNumberScoreAndXorByte))
              << std::dec
              << ", with score " << std::get<1>(lineNumberScoreAndXorByte)
              << std::endl;
}