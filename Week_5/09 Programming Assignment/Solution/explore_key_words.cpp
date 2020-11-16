#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <algorithm>
#include <future>

//----------------------------------------------------------------------------------------------------
struct Stats
{
    std::map<std::string, int> word_frequences;

    void operator += (const Stats& other);
};
//----------------------------------------------------------------------------------------------------
void Stats::operator += (const Stats& other)
{
    for (auto& [word, frequency] : other.word_frequences)
    {
        word_frequences[word] += frequency;
    }
}
//----------------------------------------------------------------------------------------------------
Stats ExploreLine(const std::set<std::string>& key_words, const std::string& line)
{
    Stats words;
    std::string_view line_view(line);

    auto pos_view = line_view.find_first_not_of(" ");
    line_view.remove_prefix(pos_view);

    while (pos_view != std::string_view::npos)
    {

        pos_view = line_view.find_first_of(" ");
        auto key = std::string(line_view.substr(0, pos_view));

        if (key_words.count(key) > 0)
        {
            words.word_frequences[std::move(key)]++;
        }

        if (pos_view == std::string::npos)
        {
            break;
        }
        else
        {
            line_view.remove_prefix(pos_view + 1);
        }
    }
    return words;
}
//----------------------------------------------------------------------------------------------------
Stats ExploreKeyWordsSingleThread(const std::set<std::string>& key_words, std::istream& input)
{
    Stats result;
    for (std::string line; getline(input, line); )
    {
        result += ExploreLine(key_words, line);
    }
    return result;
}
//----------------------------------------------------------------------------------------------------
Stats ExploreBatch(const std::set<std::string>& key_words, std::vector<std::string> lines)
{
    Stats result;
    for (const std::string& line : lines)
    {
        result += ExploreLine(key_words, line);
    }
    return result;
}
//----------------------------------------------------------------------------------------------------
Stats ExploreKeyWords(const std::set<std::string>& key_words, std::istream& input)
{
    Stats result;
    std::vector<std::future<Stats>> futures;
    const size_t max_batch_size = 5000;

    std::vector<std::string> batch;
    batch.reserve(max_batch_size);


    for (std::string line; getline(input, line); )
    {
        batch.push_back(move(line));
        if (batch.size() >= max_batch_size)
        {
            futures.push_back(
                    async(ExploreBatch, ref(key_words), move(batch))
            );
            batch.reserve(max_batch_size);
        }
    }

    if (!batch.empty())
    {
        result += ExploreBatch(key_words, move(batch));
    }

    for (auto& f : futures)
    {
        result += f.get();
    }
    return result;
}
//----------------------------------------------------------------------------------------------------
void TestBasic()
{
    const std::set<std::string> key_words = {"yangle", "rocks", "sucks", "all"};

    std::stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const std::map<std::string, int> expected =
    {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    LOG_DURATION("All tests");
    tr.RunTest(TestBasic, "TestBasic");
}
//----------------------------------------------------------------------------------------------------