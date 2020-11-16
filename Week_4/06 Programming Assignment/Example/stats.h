#pragma once

#include "http_request.h"

#include <array>
#include <string_view>
#include <map>
using namespace std;

class StatPiece {
public:
  template <typename Container>
  StatPiece(const Container& known_keys, string_view default_key)
    : default_key(default_key)
  {
    counts[default_key] = 0;
    for (string_view key : known_keys) {
      counts[key] = 0;
    }
  }

  void Add(string_view value);

  const map<string_view, int>& GetValues() const {
    return counts;
  }

private:
  const string_view default_key;
  map<string_view, int> counts;
};

class Stats {
public:
  Stats() = default;

  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;

private:
  // Ключевое слово inline позволяет определить статические члены 
  // known_methods, default_method и т.д. здесь, в .h-файле. Без 
  // него нам бы пришлось объявить их здесь, а определеление вынести 
  // в stats.cpp 
  inline static const array<string, 4> known_methods = {"GET", "POST", "DELETE", "PUT"};
  inline static const string default_method= "UNKNOWN";

  inline static const array<string, 5> known_uris = {"/", "/product", "/basket", "/help", "/order"};
  inline static const string default_uri = "unknown";

  StatPiece methods{known_methods, default_method};
  StatPiece uris{known_uris, default_uri};
};

HttpRequest ParseRequest(string_view line);