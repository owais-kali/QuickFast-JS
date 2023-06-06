#ifndef CLION
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

#include <Application/QuickFAST.h>

#include "Codecs/Decoder.h"
#include "Codecs/XMLTemplateParser.h"
#include <Codecs/DataSourceBuffer.h>
#include <Codecs/GenericMessageBuilder.h>
#include <Codecs/SingleMessageConsumer.h>
#include <Messages/MessageAccessor.h>

#include "template_consumer.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
QuickFAST::Codecs::TemplateRegistryPtr
parse_templates() {
    std::string candle_xml = "<?xml version=\"1.0\"?>\n"
                             "<templates xmlns=\"http://www.fixprotocol.org/ns/fast/td/1.1\">\n"
                             "    <template name=\"CandleData\" id=\"1\">\n"
                             "        <uInt32 name=\"SequenceNumber\" id=\"200\">\n"
                             "            <increment/>\n"
                             "        </uInt32>\n"
                             "        <uInt32 name=\"Timestamp\" id=\"70\">\n"
                             "            <copy/>\n"
                             "        </uInt32>\n"
                             "        <string name=\"Symbol\" id=\"10\">\n"
                             "            <constant value=\"BTC\"/>\n"
                             "        </string>\n"
                             "\n"
                             "        <uInt32 name=\"open\" id=\"20\">\n"
                             "            <copy/>\n"
                             "        </uInt32>\n"
                             "        <uInt32 name=\"high\" id=\"30\">\n"
                             "            <copy/>\n"
                             "        </uInt32>\n"
                             "        <uInt32 name=\"low\" id=\"40\">\n"
                             "            <copy/>\n"
                             "        </uInt32>\n"
                             "        <uInt32 name=\"close\" id=\"50\">\n"
                             "            <copy/>\n"
                             "        </uInt32>\n"
                             "        <uInt32 name=\"volume\" id=\"60\">\n"
                             "            <copy/>\n"
                             "        </uInt32>\n"
                             "    </template>\n"
                             "</templates>";

    QuickFAST::Codecs::XMLTemplateParser parser;
    return parser.parse(candle_xml);
}

size_t ReadDataFromFile(const char *path, char **out) {
    // Open the binary file for reading
    std::ifstream inFile(path, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Failed to open the file for reading.");
    }

    // Determine the file size
    inFile.seekg(0, std::ios::end);
    std::streampos fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    // Allocate memory to store the file data
    char *buffer = new char[fileSize];

    // Read the file data into the buffer
    inFile.read(buffer, fileSize);

    // Check if the read operation was successful
    if (!inFile) {
        std::cerr << "Failed to read the binary data from the file." << std::endl;
        delete[] buffer;
        throw std::runtime_error("Failed to read the binary data from the file.");
    }

    *out = buffer;
    // Close the file
    inFile.close();

    std::cout << "Binary data was successfully read from the file." << std::endl;

    return fileSize;
}

const char *cstr(const std::string &message) {
    char *cstr = new char[message.length() + 1];
    std::strcpy(cstr, message.c_str());
    return cstr;
}

EMSCRIPTEN_KEEPALIVE
const char *getAMessage() {
    return cstr("oh hai there!");
};

EMSCRIPTEN_KEEPALIVE
const char *test() {
    QuickFAST::Codecs::TemplateRegistryPtr templates_(parse_templates());
    QuickFAST::Codecs::Decoder decoder_(templates_);

    uint8_t encoded_data[] = {
            127,
            192,
            129,
            129,
            6,
            35,
            95,
            115,
            190,
            228,
            228,
            228,
            228,
            228,
    };

    // Decode the message
    QuickFAST::Codecs::DataSourceBuffer source(encoded_data, sizeof encoded_data);
    QuickFAST::Codecs::SingleMessageConsumer consumer;
    QuickFAST::Codecs::GenericMessageBuilder builder(consumer);
    decoder_.decodeMessage(source, builder);
    QuickFAST::Messages::Message &msg(consumer.message());

    // Examine message contents
    uint64_t seq_num, msg_type, timestamp;
    const QuickFAST::StringBuffer *string_buffer;
    std::string symbol;

    if (!msg.getUnsignedInteger(TemplateConsumer::id_seq_num_, QuickFAST::ValueType::UINT32, seq_num)) {
        std::cout << "Could not get seq num from msg" << std::endl;
    }

    if (!msg.getString(TemplateConsumer::id_symbol_, QuickFAST::ValueType::ASCII, string_buffer)) {
        std::cout << "Could not get symbol from msg" << std::endl;
    }
    symbol = (std::string) *string_buffer;

    return cstr(symbol);
}

EMSCRIPTEN_KEEPALIVE
void test_print() {
    printf("hello world!");
}

EMSCRIPTEN_KEEPALIVE
int fib(int n) {
    if (n <= 0) {
        return 0;
    }
    int i, t, a = 0, b = 1;
    for (i = 1; i < n; i++) {
        t = a + b;
        a = b;
        b = t;
    }
    return b;
}

}//extern "C" END

int main() {
    test();

    return 0;

    QuickFAST::Codecs::TemplateRegistryPtr templates_(parse_templates());
    QuickFAST::Codecs::Decoder decoder_(templates_);

    const unsigned char *encoded_data;
    auto size = ReadDataFromFile("/media/owais/LinuxHDD1/Freelancer/BitZee/TradeEngine/Tests/QuickFast_Decoder_Test/input/encoded_data.bin",
                                 (char **) &encoded_data);

    // Decode the message
    QuickFAST::Codecs::DataSourceBuffer source(encoded_data, size);
    QuickFAST::Codecs::SingleMessageConsumer consumer;
    QuickFAST::Codecs::GenericMessageBuilder builder(consumer);
    decoder_.decodeMessage(source, builder);
    QuickFAST::Messages::Message &msg(consumer.message());

    // Examine message contents
    uint64_t seq_num, msg_type, timestamp;
    const QuickFAST::StringBuffer *string_buffer;
    std::string symbol;

    if (!msg.getUnsignedInteger(TemplateConsumer::id_seq_num_, QuickFAST::ValueType::UINT32, seq_num)) {
        std::cout << "Could not get seq num from msg" << std::endl;
        return false;
    }

    if (!msg.getString(TemplateConsumer::id_symbol_, QuickFAST::ValueType::ASCII, string_buffer)) {
        std::cout << "Could not get symbol from msg" << std::endl;
        return false;
    }
    symbol = (std::string) *string_buffer;

    printf("Symbol: %s", symbol.c_str());

    delete encoded_data;
}