#include <string>
#include <list>

#include "test_runner.h"
#include "profile.h"
//----------------------------------------------------------------------------------------------------
class Editor
{
public:
    Editor();
    void Left();
    void Right();
    void Insert(char token);
    void Cut(size_t tokens = 1);
    void Copy(size_t tokens = 1);
    void Paste();
    std::string GetText() const;
private:
    std::list<char> text;
    std::list<char> buffer;
    std::list<char>::iterator cursor;
};
//----------------------------------------------------------------------------------------------------
Editor::Editor() : text{}, cursor{text.begin()}
{

}
//----------------------------------------------------------------------------------------------------
void Editor::Left()
{
    if (cursor == begin(text)) return;
    cursor--;
}
//----------------------------------------------------------------------------------------------------
void Editor::Right()
{
    if (cursor == end(text)) return;
    cursor++;
}
//----------------------------------------------------------------------------------------------------
void Editor::Insert(char token)
{
    text.insert(cursor, token);
}
//----------------------------------------------------------------------------------------------------
void Editor::Cut(size_t tokens)
{
    Copy(tokens);
    auto temp_cursor = cursor;
    for (size_t i = tokens; i > 0; --i)
    {
        if (++temp_cursor == end(text)) break;
    }
    cursor = text.erase(cursor, temp_cursor);
}
//----------------------------------------------------------------------------------------------------
void Editor::Copy(size_t tokens)
{
    buffer = {cursor, std::next(cursor, tokens)};
}
//----------------------------------------------------------------------------------------------------
void Editor::Paste()
{
    text.insert(cursor, buffer.begin(), buffer.end());
}
//----------------------------------------------------------------------------------------------------
std::string Editor::GetText() const
{
    return {text.begin(), text.end()};
}
//----------------------------------------------------------------------------------------------------
void TypeText(Editor& editor, const std::string& text)
{
    for(char c : text)
    {
        editor.Insert(c);
    }
}
//----------------------------------------------------------------------------------------------------
void TestEditing()
{
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;

        TypeText(editor, "hello, world");
        for(size_t i = 0; i < text_len; ++i)
        {
            editor.Left();
        }
        editor.Cut(first_part_len);

        for(size_t i = 0; i < text_len - first_part_len; ++i)
        {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}
//----------------------------------------------------------------------------------------------------
void TestReverse()
{
    Editor editor;

    const std::string text = "esreveR";
    for(char c : text)
    {
        editor.Insert(c);
        editor.Left();
    }
    ASSERT_EQUAL(editor.GetText(), "Reverse");
}
//----------------------------------------------------------------------------------------------------
void TestNoText()
{
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}
//----------------------------------------------------------------------------------------------------
void TestEmptyBuffer()
{
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    LOG_DURATION("All tests");
    {
        tr.RunTest(TestEditing, "TestEditing");
        tr.RunTest(TestReverse, "TestReverse");
        tr.RunTest(TestNoText, "TestNoText");
        tr.RunTest(TestEmptyBuffer, "TestEmptyBuffer");
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------