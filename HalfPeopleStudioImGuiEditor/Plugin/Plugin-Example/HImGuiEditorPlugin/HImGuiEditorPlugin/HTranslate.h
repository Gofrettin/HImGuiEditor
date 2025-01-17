#pragma once
#include <vector>
#include <string>
#include <curl/curl.h>
//#include <iostream>
#include <fstream>
#include <thread>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

static std::vector<std::string> CommonTranslationData = {
    "Confirm",
    "Cancel",
    "Reset"
};
static int TranslateTargetLang = -1;
static std::vector<std::string*> TranslateObject;
const std::vector<std::string> langs{
    "auto",     //Automatic
    "af",       //Afrikaans
    "sq",       //Albanian
    "am",       //Amharic
    "ar",       //Arabic
    "hy",       //Armenian
    "az",       //Azerbaijani
    "eu",       //Basque
    "be",       //Belarusian
    "bn",       //Bengali
    "bs",       //Bosnian
    "bg",       //Bulgarian
    "ca",       //Catalan
    "ceb",      //Cebuano
    "ny",       //Chichewa
    "zh-cn",    //Chinese Simplified
    "zh-tw",    //Chinese Traditional
    "co",       //Corsican
    "hr",       //Croatian
    "cs",       //Czech
    "da",       //Danish
    "nl",       //Dutch
 //   "en",       //English
    "eo",       //Esperanto
    "et",       //Estonian
    "tl",       //Filipino
    "fi",       //Finnish
    "fr",       //French
    "fy",       //Frisian
    "gl",       //Galician
    "ka",       //Georgian
    "de",       //German
    "el",       //Greek
    "gu",       //Gujarati
    "ht",       //Haitian Creole
    "ha",       //Hausa
    "haw",      //Hawaiian
    "iw",       //Hebrew
    "hi",       //Hindi
    "hmn",      //Hmong
    "hu",       //Hungarian
    "is",       //Icelandic
    "ig",       //Igbo
    "id",       //Indonesian
    "ga",       //Irish
    "it",       //Italian
    "ja",       //Japanese
    "jw",       //Javanese
    "kn",       //Kannada
    "kk",       //Kazakh
    "km",       //Khmer
    "ko",       //Korean
    "ku",       //Kurdish (Kurmanji)
    "ky",       //Kyrgyz
    "lo",       //Lao
    "la",       //Latin
    "lv",       //Latvian
    "lt",       //Lithuanian
    "lb",       //Luxembourgish
    "mk",       //Macedonian
    "mg",       //Malagasy
    "ms",       //Malay
    "ml",       //Malayalam
    "mt",       //Maltese
    "mi",       //Maori
    "mr",       //Marathi
    "mn",       //Mongolian
    "my",       //Myanmar (Burmese)
    "ne",       //Nepali
    "no",       //Norwegian
    "ps",       //Pashto
    "fa",       //Persian
    "pl",       //Polish
    "pt",       //Portuguese
    "ma",       //Punjabi
    "ro",       //Romanian
    "ru",       //Russian
    "sm",       //Samoan
    "gd",       //Scots Gaelic
    "sr",       //Serbian
    "st",       //Sesotho
    "sn",       //Shona
    "sd",       //Sindhi
    "si",       //Sinhala
    "sk",       //Slovak
    "sl",       //Slovenian
    "so",       //Somali
    "es",       //Spanish
    "su",       //Sundanese
    "sw",       //Swahili
    "sv",       //Swedish
    "tg",       //Tajik
    "ta",       //Tamil
    "te",       //Telugu
    "th",       //Thai
    "tr",       //Turkish
    "uk",       //Ukrainian
    "ur",       //Urdu
    "uz",       //Uzbek
    "vi",       //Vietnamese
    "cy",       //Welsh
    "xh",       //Xhosa
    "yi",       //Yiddish
    "yo",       //Yoruba
    "zu"        //Zulu
};
const std::vector<std::string> GetLangsText{
    "Automatic"                   ,
    "Afrikaans"                   ,
    "Albanian"                    ,
    "Amharic"                     ,
    "Arabic"                      ,
    "Armenian"                    ,
    "Azerbaijani"                 ,
    "Basque"                      ,
    "Belarusian"                  ,
    "Bengali"                     ,
    "Bosnian"                     ,
    "Bulgarian"                   ,
    "Catalan"                     ,
    "Cebuano"                     ,
    "Chichewa"                    ,
    "Chinese Simplified"          ,
    "Chinese Traditional"         ,
    "Corsican"                    ,
    "Croatian"                    ,
    "Czech"                       ,
    "Danish"                      ,
    "Dutch"                       ,
 //   "English"                     ,
    "Esperanto"                   ,
    "Estonian"                    ,
    "Filipino"                    ,
    "Finnish"                     ,
    "French"                      ,
    "Frisian"                     ,
    "Galician"                    ,
    "Georgian"                    ,
    "German"                      ,
    "Greek"                       ,
    "Gujarati"                    ,
    "Haitian Creole"              ,
    "Hausa"                       ,
    "Hawaiian"                    ,
    "Hebrew"                      ,
    "Hindi"                       ,
    "Hmong"                       ,
    "Hungarian"                   ,
    "Icelandic"                   ,
    "Igbo"                        ,
    "Indonesian"                  ,
    "Irish"                       ,
    "Italian"                     ,
    "Japanese"                    ,
    "Javanese"                    ,
    "Kannada"                     ,
    "Kazakh"                      ,
    "Khmer"                       ,
    "Korean"                      ,
    "Kurdish(Kurmanji)"           ,
    "Kyrgyz"                      ,
    "Lao"                         ,
    "Latin"                       ,
    "Latvian"                     ,
    "Lithuanian"                  ,
    "Luxembourgish"               ,
    "Macedonian"                  ,
    "Malagasy"                    ,
    "Malay"                       ,
    "Malayalam"                   ,
    "Maltese"                     ,
    "Maori"                       ,
    "Marathi"                     ,
    "Mongolian"                   ,
    "Myanmar(Burmese)"            ,
    "Nepali"                      ,
    "Norwegian"                   ,
    "Pashto"                      ,
    "Persian"                     ,
    "Polish"                      ,
    "Portuguese"                  ,
    "Punjabi"                     ,
    "Romanian"                    ,
    "Russian"                     ,
    "Samoan"                      ,
    "Scots Gaelic"                ,
    "Serbian"                     ,
    "Sesotho"                     ,
    "Shona"                       ,
    "Sindhi"                      ,
    "Sinhala"                     ,
    "Slovak"                      ,
    "Slovenian"                   ,
    "Somali"                      ,
    "Spanish"                     ,
    "Sundanese"                   ,
    "Swahili"                     ,
    "Swedish"                     ,
    "Tajik"                       ,
    "Tamil"                       ,
    "Telugu"                      ,
    "Thai"                        ,
    "Turkish"                     ,
    "Ukrainian"                   ,
    "Urdu"                        ,
    "Uzbek"                       ,
    "Vietnamese"                  ,
    "Welsh"                       ,
    "Xhosa"                       ,
    "Yiddish"                     ,
    "Yoruba"                      ,
    "Zulu"
};
static float Schedule = 1.f;
static std::thread* TranslateThread = NULL;

#define HT_Confirm    CommonTranslationData.at(0).c_str()
#define HT_Cancel     CommonTranslationData.at(1).c_str()
#define HT_Reset      CommonTranslationData.at(2).c_str()

namespace HTranslate
{
    static std::string string_To_UTF8(const std::string& str)
    {
        int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
        wchar_t* pwBuf = new wchar_t[nwLen + 1];
        ZeroMemory(pwBuf, nwLen * 2 + 2);
        ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
        int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
        char* pBuf = new char[nLen + 1];
        ZeroMemory(pBuf, nLen + 1);
        ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
        std::string retStr(pBuf);
        delete[]pwBuf;
        delete[]pBuf;
        pwBuf = NULL;
        pBuf = NULL;
        return retStr;
    }
    
    static  std::string UTF8_To_string(const std::string& str)
    {
        int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
        wchar_t* pwBuf = new wchar_t[nwLen + 1];
        memset(pwBuf, 0, nwLen * 2 + 2);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);
        int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
        char* pBuf = new char[nLen + 1];
        memset(pBuf, 0, nLen + 1);
        WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
        std::string retStr = pBuf;
        delete[]pBuf;
        delete[]pwBuf;
        pBuf = NULL;
        pwBuf = NULL;
        return retStr;
    }
    
    static  int writer(char* data, size_t size, size_t nmemb, std::string* writerData)
    {
        if (writerData == NULL)
            return 0;
        int len = size * nmemb;
        writerData->append(data, len);
    
        //cout << "\nWriterData" << writerData << endl;
    
        return len;
    }

    static std::string subreplace(std::string resource_str, std::string sub_str, std::string new_str)
    {
        std::string dst_str = resource_str;
        std::string::size_type pos = 0;
        while ((pos = dst_str.find(sub_str)) != std::string::npos)
        {
            dst_str.replace(pos, sub_str.length(), new_str);
        }
        return dst_str;
    }

    static std::string BuildURL(std::string TranslateTarget)
    {
        std::string translate_url = "http://translate.googleapis.com/translate_a/single?client=gtx&dt=t&sl=en&tl=";
        translate_url.append(langs.at(TranslateTargetLang));
        translate_url.append("&q=%22");

        std::string SaveTarget = TranslateTarget;

        SaveTarget = subreplace(SaveTarget, "\n", "");

        SaveTarget = subreplace(SaveTarget, " ", "%20");
        SaveTarget = subreplace(SaveTarget, "\"", "");


        translate_url.append(SaveTarget);
        translate_url.append("%22");
        return translate_url;
    }

    static std::string TranslateTargetObject(std::string& In)
    {
        if (TranslateTargetLang == -1)
            return In;
        std::string buffer;
        CURL* curl;
        CURLcode res;
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, HTranslate::BuildURL(In).c_str());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTranslate::writer);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if (CURLE_OK != res)
            {
                //std::cerr << "\nHTranslate->ERROR :  CURL ERROR ID  --  " << res;
                return In;
            }

        }
        curl_global_cleanup();



        if (HTranslate::UTF8_To_string(buffer).find("��") < 100000)
        {
            std::string cn = buffer.substr(7, buffer.find("\",\"") - 10);
            buffer = cn;//HTranslate::UTF8_To_string(cn);
        }
        else
        {
            if (langs.at(TranslateTargetLang) == "ja")
            {
                buffer = HTranslate::UTF8_To_string(buffer);
                std::string qt = buffer.substr(6, buffer.find("\",\"") - 8);

                buffer = HTranslate::string_To_UTF8(qt);
            }
            else
            {
                std::string qt = buffer.substr(6, buffer.find("\",\"") - 8);
                buffer = qt;
            }

        }
        return buffer;
    }


    static /*std::vector<std::string>*/ void ConvertVectorTranslateTarget(json& JS, const char* SaveTargetName)
    {
       // std::vector<std::string> Cache;
        for (size_t i = 0; i < TranslateObject.size(); i++)
        {
           // std::cout << "\n ConvertVectorTranslateTarget  Index " << i << "  " << *TranslateObject.at(i);
            //Cache.push_back(*TranslateObject.at(i));
            JS[SaveTargetName][i] = *TranslateObject.at(i);
        }
       // return Cache;
    }

    static void TranslateAllObjectThread()
    {
        for (size_t i = 0; i < CommonTranslationData.size(); i++)
        {
            TranslateObject.push_back(&CommonTranslationData.at(i));
        }


        json TranslateSave;
        std::ifstream Lfile("DependentFile\\configuration file\\TranslateCache.json");
        if (Lfile.good() && Lfile.seekg(0, std::ios_base::end).tellg() > 5) {
            Lfile.seekg(0, std::ios_base::beg);
            TranslateSave = json::parse(Lfile);
        }
        Lfile.close();

        //std::cout << "\nTranslateBuff Size   :" << TranslateSave["TranslateBuff"].size();
        //std::cout << "\nTranslateObject Size :" << TranslateObject.size();
        //std::cout << "\nTranslateSave IsNull :" << TranslateSave.is_null();

        if (TranslateSave["TranslateBuff"].size() != TranslateObject.size() || TranslateSave.is_null())
        {
            //std::cout << "\n Translate The Object";
            //TranslateSave["BaceTranslateTarget"] = ConvertVectorTranslateTarget();
            ConvertVectorTranslateTarget(TranslateSave,"BaceTranslateTarget");
            for (size_t i = 0; i < TranslateObject.size(); i++)
            {
                Schedule = i / (float)(TranslateObject.size()-1);
                *TranslateObject.at(i) = TranslateTargetObject(*TranslateObject.at(i));
                TranslateSave["TranslateBuff"][i] = json::string_t(*TranslateObject.at(i));
                //std::cout << "\n TranslateAllObjectThread -> HTranslate-> INFO -> Translate Buffer : " << HTranslate::UTF8_To_string(*TranslateObject.at(i));
            }


        }
        else
        {
           // std::cout << "\n Load Translate";
            json TG = TranslateSave["TranslateBuff"];
            for (size_t i = 0; i < TG.size(); i++)
            {
                *TranslateObject.at(i) = TG.at(i);
            }
        }


        std::ofstream file("DependentFile\\configuration file\\TranslateCache.json");
        if (file.is_open())
        {
            file << TranslateSave;
        }
        file.close();

    }

    static void UpdataTranslateObjectThread()
    {
        json TranslateSave;
        std::ifstream Lfile("DependentFile\\configuration file\\TranslateCache.json");
        if (Lfile.is_open())
            TranslateSave = json::parse(Lfile);
        Lfile.close();

        json TG = TranslateSave["BaceTranslateTarget"];
        for (size_t i = 0; i < TranslateObject.size(); i++)
        {
            Schedule = i / (float)(TranslateObject.size()-1);
            std::string SData = TG.at(i);
            *TranslateObject.at(i) = TranslateTargetObject(SData);
            //std::cout << "\nUpdataTranslateObjectThread -> HTranslate-> INFO -> Translate Buffer : " << HTranslate::UTF8_To_string(*TranslateObject.at(i));
        }
        //TranslateSave["TranslateBuff"] = ConvertVectorTranslateTarget();
        ConvertVectorTranslateTarget(TranslateSave, "TranslateBuff");


        std::ofstream file("DependentFile\\configuration file\\TranslateCache.json");
        if (file.is_open())
        {
            file << TranslateSave;
        }
        file.close();
    }
}


static void TranslateAllObject()
{
    if (TranslateThread)
    {
        TranslateThread->detach();
        delete TranslateThread;
        TranslateThread = NULL;
    }

    TranslateThread = new std::thread(HTranslate::TranslateAllObjectThread);
}

static void UpdataTranslateObject()
{
    if (TranslateThread)
    {
        TranslateThread->detach();
        delete TranslateThread;
        TranslateThread = NULL;
    }

    TranslateThread = new std::thread(HTranslate::UpdataTranslateObjectThread);
}

static const char* GetTranslateTargetLang(int Index)
{
    if (Index == -1)
        return "English";
    return GetLangsText.at(Index).c_str();
}