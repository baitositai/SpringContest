#include "../Application.h"
#include "TextManager.h"

void TextManager::Init()
{
    //テキスト管理
    std::string text = (Application::PATH_TEXT + "textData.txt").c_str();
    textDatas_ = LoadDialogues(text);

    //フォント関係初期化
    InitFont();
}

void TextManager::Release()
{
    // フォント登録解除
    for (int i = 0; i < static_cast<int>(FONT_TYPE::MAX); i++)
    {
        if (RemoveFontResourceEx(
            (Application::PATH_FONT + fontPath_[i]).c_str(),
            FR_PRIVATE,
            NULL)
            == -1)
        {
            return;
        }
    }
}

std::string TextManager::TextLoad(TEXTS text)
{
    std::string* txt = _Load(text);
    if (txt == nullptr)
    {
        return "null";
    }
    std::string ret = *txt;
    return ret;
}

int TextManager::GetTextSize(std::string txt,int num) const
{
    int ret = -1;
    size_t bufferSize = std::snprintf(nullptr, 0, txt.c_str(), num) + 1; // +1は終端のヌル文字用
    char* buffer = new char[bufferSize];

    return ret;
}

void TextManager::Destroy()
{
    Release();
}

void TextManager::InitFont()
{
    //フォントパス設定
    fontPath_[static_cast<int>(FONT_TYPE::NORMAR)] = "msgothic.ttc";
    fontPath_[static_cast<int>(FONT_TYPE::DOT)] = "FontDot.otf";
    fontPath_[static_cast<int>(FONT_TYPE::LOGO)] = "Corporate-Logo-Bold-ver3.otf";
    fontPath_[static_cast<int>(FONT_TYPE::BOKUTACHI)] = "bokutachi.otf";
    fontPath_[static_cast<int>(FONT_TYPE::HANAZOME)] = "PENGS.ttf";
    fontPath_[static_cast<int>(FONT_TYPE::BANANA)] = "YDWbananaslipplus.otf";
    fontPath_[static_cast<int>(FONT_TYPE::PENGS)] = "PENGS.ttf";

    //フォント名前設定
    fontName_[static_cast<int>(FONT_TYPE::NORMAR)] = "ＭＳ ゴシック";
    fontName_[static_cast<int>(FONT_TYPE::DOT)] = "ベストテンDOT";
    fontName_[static_cast<int>(FONT_TYPE::LOGO)] = "コーポレート・ロゴ ver3 Bold";
    fontName_[static_cast<int>(FONT_TYPE::BOKUTACHI)] = "ぼくたちのゴシック";
    fontName_[static_cast<int>(FONT_TYPE::HANAZOME)] = "はなぞめフォント";
    fontName_[static_cast<int>(FONT_TYPE::BANANA)] = "ＹＤＷ バナナスリップ plus plus";
    fontName_[static_cast<int>(FONT_TYPE::PENGS)] = "PENGS";

    // フォントをシステムに登録
    for (int i = 0; i < static_cast<int>(FONT_TYPE::MAX); i++)
    {
        if (AddFontResourceEx(
            (Application::PATH_FONT + fontPath_[i]).c_str(),
            FR_PRIVATE,
            NULL)
            == -1)
        {
            return;
        }
    }
}

std::unordered_map<TextManager::TEXTS, std::string>
TextManager::LoadDialogues(const std::string& filename)
{
    std::unordered_map<TEXTS, std::string> dialogues;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            size_t separatorPos = line.find(":");
            if (separatorPos != std::string::npos)
            {
                int id = std::stoi(line.substr(0, separatorPos));
                std::string dialogue = line.substr(separatorPos + 1);

                // idを列挙型にキャストしてマップに追加
                dialogues[static_cast<TEXTS>(id)] = dialogue;
            }
        }
        file.close();
    }
    else 
    {
        std::cerr << "ファイルを開けませんでした。" << std::endl;
    }

    return dialogues;
}

std::string* TextManager::_Load(TEXTS text)
{
    std::string* ret = new std::string;
    if (textDatas_.find(text) != textDatas_.end())
    {
        *ret = textDatas_.at(text);
        return ret;
    }

    *ret = "セリフが見つかりません。";

    return ret;
}

TextManager::TextManager(void)
{
    Init();
}
