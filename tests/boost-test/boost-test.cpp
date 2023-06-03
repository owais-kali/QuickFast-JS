#include <emscripten.h>

#include "iostream"

#include <boost/bind.hpp>
#include <boost/cstdint.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/operators.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/weak_ptr.hpp>

#include <Application/QuickFAST.h>

#include "Codecs/Decoder.h"
#include "Codecs/XMLTemplateParser.h"
#include <Codecs/DataSourceBuffer.h>
#include <Codecs/GenericMessageBuilder.h>
#include <Codecs/SingleMessageConsumer.h>
#include <Messages/MessageAccessor.h>

extern "C" {
QuickFAST::Codecs::TemplateRegistryPtr
parse_templates(const std::string &template_filename) {
  std::ifstream template_stream(template_filename.c_str());
  QuickFAST::Codecs::XMLTemplateParser parser;
  return parser.parse(template_stream);
}
}