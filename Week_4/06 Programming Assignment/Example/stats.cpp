#include "stats.h"

void Stats::AddMethod(string_view method) {
  methods.Add(method);
}

void Stats::AddUri(string_view uri) {
  uris.Add(uri);
}

const map<string_view, int>& Stats::GetMethodStats() const {
  return methods.GetValues();
}

const map<string_view, int>& Stats::GetUriStats() const {
  return uris.GetValues();
}

void LeftStrip(string_view& sv) {
  while (!sv.empty() && isspace(sv[0])) {
    sv.remove_prefix(1);
  }
}

string_view ReadToken(string_view& sv) {
  LeftStrip(sv);

  auto pos = sv.find(' ');
  auto result = sv.substr(0, pos);
  sv.remove_prefix(pos != sv.npos ? pos : sv.size());
  return result;
}

HttpRequest ParseRequest(string_view line) {
  auto method = ReadToken(line);
  auto uri = ReadToken(line);
  return {method, uri, ReadToken(line)};
}

void StatPiece::Add(string_view value) {
  if (auto it = counts.find(value); it != counts.end()) {
    ++it->second;
  } else {
    ++counts[default_key];
  }
}