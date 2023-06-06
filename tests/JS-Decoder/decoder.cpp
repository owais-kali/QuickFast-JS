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

const char *cstr(const std::string &message) {
    char *cstr = new char[message.length() + 1];
    std::strcpy(cstr, message.c_str());
    return cstr;
}

EMSCRIPTEN_KEEPALIVE
const char* Decode(const char* template_xml, uint8_t encoded_data[], const int encoded_data_size) {
    QuickFAST::Codecs::XMLTemplateParser parser;
    QuickFAST::Codecs::TemplateRegistryPtr templates_(parser.parse(template_xml));
    QuickFAST::Codecs::Decoder decoder_(templates_);

    // Decode the message
    QuickFAST::Codecs::DataSourceBuffer source(encoded_data, encoded_data_size);
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

#ifdef CLION
int main()
{
    return 0;
}
#endif

}//extern "C" END