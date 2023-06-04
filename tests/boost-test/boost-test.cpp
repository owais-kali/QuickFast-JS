#include <emscripten.h>

#include <Application/QuickFAST.h>

#include "Codecs/Decoder.h"
#include "Codecs/XMLTemplateParser.h"
#include <Codecs/DataSourceBuffer.h>
#include <Codecs/GenericMessageBuilder.h>
#include <Codecs/SingleMessageConsumer.h>
#include <Messages/MessageAccessor.h>

QuickFAST::Codecs::TemplateRegistryPtr
parse_templates(const std::string &template_filename) {
  std::ifstream template_stream(template_filename.c_str());
  QuickFAST::Codecs::XMLTemplateParser parser;
  return parser.parse(template_stream);
}

EMSCRIPTEN_KEEPALIVE
void test(){
  parse_templates("");
  printf("test function called!\n");

  QuickFAST::Codecs::TemplateRegistryPtr templates_(nullptr);
  QuickFAST::Codecs::Decoder decoder_(templates_);

  QuickFAST::Codecs::DataSourceBuffer source(nullptr, 0);
  QuickFAST::Codecs::SingleMessageConsumer consumer;
  QuickFAST::Codecs::GenericMessageBuilder builder(consumer);
  decoder_.decodeMessage(source, builder);
  QuickFAST::Messages::Message& msg(consumer.message());
}