#include <fstream>
#include <iostream>

#include <Application/QuickFAST.h>

#include "Codecs/Decoder.h"
#include "Codecs/XMLTemplateParser.h"
#include <Codecs/DataSourceBuffer.h>
#include <Codecs/GenericMessageBuilder.h>
#include <Codecs/SingleMessageConsumer.h>
#include <Messages/MessageAccessor.h>

#include "template_consumer.h"

QuickFAST::Codecs::TemplateRegistryPtr parse_templates(const std::string& template_filename)
{
  std::ifstream template_stream(template_filename.c_str());
  QuickFAST::Codecs::XMLTemplateParser parser;
  return parser.parse(template_stream);
}

size_t ReadDataFromFile(const char* path, char** out){
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
  char* buffer = new char[fileSize];

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

  return fileSize;

  std::cout << "Binary data was successfully read from the file." << std::endl;
}

int main() {
  QuickFAST::Codecs::TemplateRegistryPtr templates_(parse_templates("/media/owais/LinuxHDD1/Freelancer/BitZee/TradeEngine/Tests/QuickFast_Decoder_Test/input/Candle.xml"));
  QuickFAST::Codecs::Decoder decoder_(templates_);

  const unsigned char* encoded_data;
  auto size = ReadDataFromFile("/media/owais/LinuxHDD1/Freelancer/BitZee/TradeEngine/Tests/QuickFast_Decoder_Test/input/encoded_data.bin",
                       (char **)&encoded_data);

  // Decode the message
  QuickFAST::Codecs::DataSourceBuffer source(encoded_data, size);
  QuickFAST::Codecs::SingleMessageConsumer consumer;
  QuickFAST::Codecs::GenericMessageBuilder builder(consumer);
  decoder_.decodeMessage(source, builder);
  QuickFAST::Messages::Message& msg(consumer.message());

  // Examine message contents
  uint64_t seq_num, msg_type, timestamp;
  const QuickFAST::StringBuffer* string_buffer;
  std::string symbol;

  if (!msg.getUnsignedInteger(TemplateConsumer::id_seq_num_, QuickFAST::ValueType::UINT32, seq_num)) {
    std::cout << "Could not get seq num from msg" << std::endl;
    return false;
  }

  if (!msg.getString(TemplateConsumer::id_symbol_, QuickFAST::ValueType::ASCII, string_buffer)) {
    std::cout << "Could not get symbol from msg" << std::endl;
    return false;
  }
  symbol = (std::string)*string_buffer;

  delete encoded_data;
}
