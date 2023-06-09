
#ifndef CLION
#include <emscripten.h>
#include <emscripten/bind.h>
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

struct CandleStick {
    int id;
    int open;
    int high;
    int low;
    int close;
    int Volume_BTC;
    int Volume_USD;
};

EMSCRIPTEN_KEEPALIVE
const int Decode(const char *template_xml, uint8_t encoded_data[], const int encoded_data_size, CandleStick* candleStick) {
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
    size_t CandlesLength = 0;
    msg.getSequenceLength(TemplateConsumer::id_candles_, CandlesLength);

    for (int i = 0; i < CandlesLength; ++i) {
        const QuickFAST::Messages::MessageAccessor *candles_accessor;
        if (msg.getSequenceEntry(TemplateConsumer::id_candles_,
                                 i, candles_accessor)) {
            uint64_t id = 0;
            uint64_t open = 0;
            uint64_t high = 0;
            uint64_t low = 0;
            uint64_t close = 0;
            uint64_t Volume_BTC = 0;
            uint64_t Volume_USD = 0;

            candles_accessor->getUnsignedInteger(TemplateConsumer::id_seq_num_,
                                                 QuickFAST::ValueType::INT32, id);
            candles_accessor->getUnsignedInteger(TemplateConsumer::id_open_,
                                                 QuickFAST::ValueType::INT32, open);
            candles_accessor->getUnsignedInteger(TemplateConsumer::id_high_,
                                                 QuickFAST::ValueType::INT32, high);
            candles_accessor->getUnsignedInteger(TemplateConsumer::id_low_,
                                                 QuickFAST::ValueType::INT32, low);
            candles_accessor->getUnsignedInteger(TemplateConsumer::id_close_,
                                                 QuickFAST::ValueType::INT32, close);
            candles_accessor->getUnsignedInteger(TemplateConsumer::Volume_BTC,
                                                 QuickFAST::ValueType::INT32, Volume_BTC);
            candles_accessor->getUnsignedInteger(TemplateConsumer::Volume_USD,
                                                 QuickFAST::ValueType::INT32, Volume_USD);


            candleStick[i].id = id;
            candleStick[i].open = open;
            candleStick[i].high = high;
            candleStick[i].low = low;
            candleStick[i].close = close;
            candleStick[i].Volume_BTC = Volume_BTC;
            candleStick[i].Volume_USD = Volume_USD;
        }
    }

    return CandlesLength;
}

#ifdef CLION
int main() {
    CandleStick candle;
    printf("%lu", sizeof(candle));
    return 0;
}
#endif

}//extern "C" END