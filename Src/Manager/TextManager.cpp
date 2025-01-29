#include "../Application.h"
#include "TextManager.h"

void TextManager::Init()
{
    //�e�L�X�g�Ǘ�
    std::string text = (Application::PATH_TEXT + "textData.txt").c_str();
    textDatas_ = LoadDialogues(text);

    //�t�H���g�֌W������
    InitFont();
}

void TextManager::Release()
{
    // �t�H���g�o�^����
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
    size_t bufferSize = std::snprintf(nullptr, 0, txt.c_str(), num) + 1; // +1�͏I�[�̃k�������p
    char* buffer = new char[bufferSize];

    return ret;
}

void TextManager::Destroy()
{
    Release();
}

void TextManager::InitFont()
{
    //�t�H���g�p�X�ݒ�
    fontPath_[static_cast<int>(FONT_TYPE::NORMAR)] = "msgothic.ttc";
    fontPath_[static_cast<int>(FONT_TYPE::DOT)] = "FontDot.otf";
    fontPath_[static_cast<int>(FONT_TYPE::LOGO)] = "Corporate-Logo-Bold-ver3.otf";
    fontPath_[static_cast<int>(FONT_TYPE::BOKUTACHI)] = "bokutachi.otf";
    fontPath_[static_cast<int>(FONT_TYPE::HANAZOME)] = "PENGS.ttf";
    fontPath_[static_cast<int>(FONT_TYPE::BANANA)] = "YDWbananaslipplus.otf";
    fontPath_[static_cast<int>(FONT_TYPE::PENGS)] = "PENGS.ttf";

    //�t�H���g���O�ݒ�
    fontName_[static_cast<int>(FONT_TYPE::NORMAR)] = "�l�r �S�V�b�N";
    fontName_[static_cast<int>(FONT_TYPE::DOT)] = "�x�X�g�e��DOT";
    fontName_[static_cast<int>(FONT_TYPE::LOGO)] = "�R�[�|���[�g�E���S ver3 Bold";
    fontName_[static_cast<int>(FONT_TYPE::BOKUTACHI)] = "�ڂ������̃S�V�b�N";
    fontName_[static_cast<int>(FONT_TYPE::HANAZOME)] = "�͂Ȃ��߃t�H���g";
    fontName_[static_cast<int>(FONT_TYPE::BANANA)] = "�x�c�v �o�i�i�X���b�v plus plus";
    fontName_[static_cast<int>(FONT_TYPE::PENGS)] = "PENGS";

    // �t�H���g���V�X�e���ɓo�^
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

                // id��񋓌^�ɃL���X�g���ă}�b�v�ɒǉ�
                dialogues[static_cast<TEXTS>(id)] = dialogue;
            }
        }
        file.close();
    }
    else 
    {
        std::cerr << "�t�@�C�����J���܂���ł����B" << std::endl;
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

    *ret = "�Z���t��������܂���B";

    return ret;
}

TextManager::TextManager(void)
{
    Init();
}
