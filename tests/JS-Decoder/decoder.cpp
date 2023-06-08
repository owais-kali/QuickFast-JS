
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
        candleStick[i].id = 1;
        candleStick[i].open = 2;
        candleStick[i].high = 3;
        candleStick[i].low = 4;
        candleStick[i].close = 5;
        candleStick[i].Volume_BTC = 6;
        candleStick[i].Volume_USD = 7;
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