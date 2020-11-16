#include "search_server.h"
#include "profile.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

//----------------------------------------------------------------------------------------------------
std::vector<std::string_view> SplitIntoWords(std::string_view line)
{
    std::vector<std::string_view> result;
    size_t curr = line.find_first_not_of(' ', 0);
    while (true)
    {
        auto space = line.find(' ', curr);
        result.emplace_back(line.substr(curr, space - curr));

        if (space == line.npos)
        {
            break;
        }
        else
        {
            curr = line.find_first_not_of(' ', space);
        }

        if (curr == line.npos) break;
    }
    return result;
}
//----------------------------------------------------------------------------------------------------
SearchServer::SearchServer(std::istream& document_input)
{
    UpdateDocumentBase(document_input);
}
//----------------------------------------------------------------------------------------------------
void SearchServer::UpdateDocumentBase(std::istream& document_input)
{
    LOG_DURATION("UpdateDocumentBase")
    InvertedIndex new_index;
    for (std::string current_document; std::getline(document_input, current_document); )
    {
        new_index.Add(std::move(current_document));
    }
    index = std::move(new_index);
}
//----------------------------------------------------------------------------------------------------
void SearchServer::AddQueriesStream(std::istream& query_input, std::ostream& search_results_output)
{
    LOG_DURATION("AddQueriesStream")

    std::vector<size_t> docs(50000);
    std::vector<size_t> indx(50000);
    for (std::string current_query; getline(query_input, current_query); )
    {
        size_t curr_ind = 0;
        for (const auto& word : SplitIntoWords(current_query))
        {
            auto vec = index.Lookup(word);
            for (const auto& [docid, count] : vec)
            {
                if (docs[docid] == 0)
                {
                    indx[curr_ind++] = docid;
                }
                docs[docid] += count;
            }
        }

        std::vector<std::pair<size_t, size_t>> search_result;
        for (size_t docid = 0; docid < curr_ind; ++docid)
        {
            size_t count = 0;
            size_t id = 0;
            std::swap(count, docs[indx[docid]]);
            std::swap(id, indx[docid]);
            search_result.emplace_back(id, count);
        }

        const size_t ANSWERS_COUNT = 5;
        std::partial_sort(std::begin(search_result), std::begin(search_result) + std::min<size_t>(ANSWERS_COUNT, search_result.size()),
                std::end(search_result),
            [](std::pair<size_t, size_t> lhs, std::pair<size_t, size_t> rhs)
            {
                int64_t lhs_docid = lhs.first;
                auto lhs_hit_count = lhs.second;
                int64_t rhs_docid = rhs.first;
                auto rhs_hit_count = rhs.second;
                return std::make_pair(lhs_hit_count, -lhs_docid) > std::make_pair(rhs_hit_count, -rhs_docid);
            });

        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(search_result, ANSWERS_COUNT))
        {
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << "\n";
    }
}
//----------------------------------------------------------------------------------------------------
void InvertedIndex::Add(std::string&& document)
{
    docs.push_back(std::move(document));
    const size_t docid = docs.size() - 1;

    for (const auto& word : SplitIntoWords(docs.back()))
    {
        auto& vec_pair = index[word];
        if(!vec_pair.empty() && vec_pair.back().first == docid)
        {
            vec_pair.back().second += 1;
        }
        else
        {
            vec_pair.emplace_back(docid, 1);
        }
    }
}
//----------------------------------------------------------------------------------------------------
std::vector<std::pair<size_t, size_t>> InvertedIndex::Lookup(std::string_view word) const
{
    if (auto it = index.find(word); it != index.end())
    {
        return it->second;
    }
    else
    {
        return {};
    }
}
//----------------------------------------------------------------------------------------------------