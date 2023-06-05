//#define CLION

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

EMSCRIPTEN_KEEPALIVE
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

EMSCRIPTEN_KEEPALIVE
void test_print(){
  printf("hello world!");
}

EMSCRIPTEN_KEEPALIVE
int fib(int n) {
  if(n <= 0){
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