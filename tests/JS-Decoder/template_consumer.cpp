
#include <boost/cstdint.hpp>
#include "template_consumer.h"
#include <fstream>
#include <Codecs/XMLTemplateParser.h>

using namespace QuickFAST::Messages;

const FieldIdentity TemplateConsumer::id_candles_("Candles");
const QuickFAST::Messages::FieldIdentity id_candles_length_("CandlesLength");

const FieldIdentity TemplateConsumer::id_seq_num_("SequenceNumber");
const FieldIdentity TemplateConsumer::id_timestamp_("Timestamp");
const FieldIdentity TemplateConsumer::id_symbol_("Symbol");

const FieldIdentity TemplateConsumer::id_open_("open");
const FieldIdentity TemplateConsumer::id_high_("high");
const FieldIdentity TemplateConsumer::id_low_("low");
const FieldIdentity TemplateConsumer::id_close_("close");
const FieldIdentity TemplateConsumer::Volume_BTC("Volume BTC");
const FieldIdentity TemplateConsumer::Volume_USD("Volume USD");

QuickFAST::Codecs::TemplateRegistryPtr 
TemplateConsumer::parse_templates(const std::string& template_filename)
{
    std::ifstream template_stream(template_filename.c_str());
    QuickFAST::Codecs::XMLTemplateParser parser;
    return parser.parse(template_stream);
}
