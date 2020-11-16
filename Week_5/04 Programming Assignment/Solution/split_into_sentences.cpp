#include "test_runner.h"

#include <vector>

//----------------------------------------------------------------------------------------------------
// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
//----------------------------------------------------------------------------------------------------
template <typename Token>
using Sentence = std::vector<Token>;
//----------------------------------------------------------------------------------------------------
// Класс Token имеет метод bool IsEndSentencePunctuation() const
//----------------------------------------------------------------------------------------------------
template <typename Token>
std::vector<Sentence<Token>> SplitIntoSentences(std::vector<Token> tokens)
{
    std::vector<Sentence<Token>> sentences;
    Sentence<Token> sentence;

    for(auto it = tokens.begin(); it != tokens.end(); )
    {
        if(it->IsEndSentencePunctuation())
        {
            do
            {
                sentence.push_back(std::move(*it));
                ++it;
            }
            while(it != tokens.end() && it->IsEndSentencePunctuation());
            sentences.push_back(std::move(sentence));
        }
        else
        {
            sentence.push_back(std::move(*it));
            ++it;
        }
    }

    if (!sentence.empty()) sentences.push_back(std::move(sentence));
    return sentences;
}
//----------------------------------------------------------------------------------------------------
struct TestToken
{
    std::string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const
    {
        return is_end_sentence_punctuation;
    }

    bool operator==(const TestToken& other) const
    {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};
//----------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const TestToken& token)
{
    return stream << token.data;
}
//----------------------------------------------------------------------------------------------------
// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
//----------------------------------------------------------------------------------------------------
void TestSplitting()
{
    ASSERT_EQUAL(SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
                 std::vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

    ASSERT_EQUAL(SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
                 std::vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

    ASSERT_EQUAL(SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
                 std::vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}}, {{"Without"}, {"copies"}, {".", true}},}));
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    tr.RunTest(TestSplitting, "TestSplitting");
    return 0;
}

//----------------------------------------------------------------------------------------------------