#include <emscripten.h>

#include <Application/QuickFAST.h>

#include "Codecs/Decoder.h"
#include "Codecs/XMLTemplateParser.h"
#include <Codecs/DataSourceBuffer.h>
#include <Codecs/GenericMessageBuilder.h>
#include <Codecs/SingleMessageConsumer.h>
#include <Messages/MessageAccessor.h>

extern "C" {

EMSCRIPTEN_KEEPALIVE
void test(){
  printf("test function called!\n");

  QuickFAST::Codecs::TemplateRegistryPtr templates_(nullptr);
  QuickFAST::Codecs::Decoder decoder_(templates_);

  QuickFAST::Codecs::DataSourceBuffer source(nullptr, 0);
  QuickFAST::Codecs::SingleMessageConsumer consumer;
  QuickFAST::Codecs::GenericMessageBuilder builder(consumer);
  decoder_.decodeMessage(source, builder);
  QuickFAST::Messages::Message& msg(consumer.message());
}
}