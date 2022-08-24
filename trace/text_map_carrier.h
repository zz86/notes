// text_map_carrier.h, copy from example folder
#ifndef LIGHTSTEP_TEXT_MAP_CARRIER
#define LIGHTSTEP_TEXT_MAP_CARRIER

#include <opentracing/propagation.h>
#include <string>
#include <unordered_map>

// using opentracing::TextMapReader;
// using opentracing::TextMapWriter;
// using opentracing::expected;
// using opentracing::string_view;

#include <cassert>
#include <unordered_map>

#include <zipkin/opentracing.h>
using namespace zipkin;
using namespace opentracing;

# define MAXLINE 1024

// class textMapCarrier
class TextMapCarrier : public TextMapReader, public TextMapWriter {
public:
  TextMapCarrier(std::unordered_map<std::string, std::string> &text_map)
      : text_map_(text_map) {}

  expected<void> Set(string_view key, string_view value) const override {
    text_map_[key] = value;
    return {};
  }

  expected<void> ForeachKey(
      std::function<expected<void>(string_view key, string_view value)> f)
      const override {
    for (const auto &key_value : text_map_) {
      auto result = f(key_value.first, key_value.second);
      if (!result)
        return result;
    }
    return {};
  }

  std::unordered_map<std::string, std::string> &text_map_;
};

// span context reader/writer helper

std::string read_span_context(std::unordered_map<std::string, std::string> m)
{
    std::string output = "";

    for (auto it = m.cbegin(); it != m.cend(); it++)
    {
        output += (it->first) + ":" + it->second + ",";
    }

    return output.substr(0, output.size() - 1);
}


void write_span_context(std::unordered_map<std::string, std::string> &m, char *context)
{
   char * keypair = strtok(context, ",");
   while(keypair != NULL)
   {
       std::string s(keypair);
       std::string::size_type found = s.find_first_of(':');
       m.insert(std::pair<std::string, std::string>(s.substr(0,found),s.substr(found+1)));
       keypair =strtok(NULL, ",");
   }
}

auto init_tracer(std::string service_name) {
  // init opentracing zipkin
  ZipkinOtTracerOptions options;
  options.service_name = service_name;
  auto tracer = makeZipkinOtTracer(options);
  assert(tracer);
  return tracer;
}

auto str_to_spancontext(auto &tracer, std::string spancontext_str){
  char contxt[MAXLINE];
  strcpy(contxt, spancontext_str.c_str());
  std::unordered_map<std::string, std::string> text_map;
  write_span_context(std::ref(text_map), &contxt[0]);
  TextMapCarrier carrier(text_map);
  auto span_context_maybe = tracer->Extract(carrier); // extraction

  return span_context_maybe;
}

std::string span_to_str(auto &tracer, auto &span) {
  std::unordered_map<std::string, std::string> text_map;
  TextMapCarrier carrier(text_map);
  auto err = tracer->Inject(span->context(), carrier); //injection
  std::string span_context_str = read_span_context(text_map);
  
  return span_context_str; 
}

#endif // LIGHTSTEP_TEXT_MAP_CARRIER


