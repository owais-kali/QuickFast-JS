
#include <boost/shared_ptr.hpp>
#include <Application/QuickFAST.h>
#include <Codecs/TemplateRegistry_fwd.h>
#include <Messages/FieldIdentity.h>

class TemplateConsumer {
public:
    static const QuickFAST::Messages::FieldIdentity id_candles_;
    static const QuickFAST::Messages::FieldIdentity id_candles_length_;

    static QuickFAST::Codecs::TemplateRegistryPtr
    parse_templates(const std::string& template_filename);
    // Common field identities
    static const QuickFAST::Messages::FieldIdentity id_seq_num_;
    static const QuickFAST::Messages::FieldIdentity id_timestamp_;
    static const QuickFAST::Messages::FieldIdentity id_symbol_;

    static const QuickFAST::Messages::FieldIdentity id_open_;
    static const QuickFAST::Messages::FieldIdentity id_high_;
    static const QuickFAST::Messages::FieldIdentity id_low_;
    static const QuickFAST::Messages::FieldIdentity id_close_;
    static const QuickFAST::Messages::FieldIdentity Volume_BTC;
    static const QuickFAST::Messages::FieldIdentity Volume_USD;
};

