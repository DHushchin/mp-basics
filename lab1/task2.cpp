#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct WordFrequency {
    string word;
    int frequency = 0;
    int pages[100] = {-1};
    int ind = 0;
};

int main()
{
    int TotalWordsAmount = 0;
    int WordsAmount = 0, Size = 2;
    WordFrequency* WordList = new WordFrequency[Size];

    string StopWords[] = { "the", "a", "an", "for", "in", "on", "onto", "into", "of", "to", "at", "by",
                           "are", "but", "is", "am", "and", "not", "or", "with", "about", "towards",
                           "across", "though", "through", "up", "down", "above", "below", "over",
                           "under", "beside", "off", "before", "after", "during", "while", "since", "from",
                            "he", "she", "it", "i", "they", "you", "we", "that", "as", "one", "be", "the" };

    ifstream ReadingStream("text.txt");

    string CurrWord;
    int Counter = 0;


ReadingFile:
    if (!(ReadingStream >> CurrWord))
    {
        goto BubbleSorting;
    }
    Counter = 0;
    TotalWordsAmount++;

ToLowerCase:
    if (CurrWord[Counter] == '\0')
    {
        goto IgnoreStopWords;
    }

    if (CurrWord[Counter] == ',' || CurrWord[Counter] == '.' || CurrWord[Counter] == ':' ||
        CurrWord[Counter] == '!' || CurrWord[Counter] == '?' || CurrWord[Counter] == '-')
    {
        CurrWord[Counter] = '\n';
    }

    if (CurrWord[Counter] < 65 || (CurrWord[Counter] > 90 && CurrWord[Counter] < 97) || CurrWord[Counter] > 122)
    {
        goto ReadingFile;
    }

    if (65 <= CurrWord[Counter] && CurrWord[Counter] <= 90)
    {
        CurrWord[Counter] += 32;
    }

    Counter++;
    goto ToLowerCase;

    Counter = 0;

IgnoreStopWords:
    if (Counter == 51)
    {
        goto Counting;
    }

    if (CurrWord == StopWords[Counter])
    {
        goto ReadingFile;
    }
    Counter++;
    goto IgnoreStopWords;

Counting:
    Counter = 0;

IncrementFrequency:
    if (Counter == WordsAmount)
    {
        goto AddNewWord;
    }

    if (WordList[Counter].word == CurrWord)
    {
        WordList[Counter].frequency += 1;


        if (WordList[Counter].frequency < 100)
        {
            WordList[Counter].pages[WordList[Counter].ind++] = TotalWordsAmount / 250;
            goto ReadingFile;

        }
    }
    Counter++;
    goto IncrementFrequency;

AddNewWord:
    if (WordsAmount == Size - 1) // reallocation
    {
        Size *= 2;
        WordFrequency* TempWordList = new WordFrequency[Size];
        int i = 0;
    ArrayCopying:
        if (i == WordsAmount)
        {
            goto DeleteOldArray;
        }
        TempWordList[i] = WordList[i++];
        goto ArrayCopying;

    DeleteOldArray:
        delete[] WordList;
        WordList = TempWordList;
    }

    WordList[WordsAmount].word = CurrWord;
    WordList[WordsAmount].frequency = 1;
    WordList[WordsAmount].pages[WordList[WordsAmount].ind++] = TotalWordsAmount / 250;
    WordsAmount++;
    goto ReadingFile;

BubbleSorting:
    int i = 0;
OuterLoop:
    if (i >= WordsAmount - 1)
    {
        i = 0;
        goto Output;
    }
    Counter = i + 1;

InnerLoop:
    if (Counter >= WordsAmount) {
        i++;
        goto OuterLoop;
    }

    if (WordList[i].word > WordList[Counter].word) {
        WordFrequency tmp = WordList[i];
        WordList[i] = WordList[Counter];
        WordList[Counter] = tmp;
    }

    Counter++;
    goto InnerLoop;

Output:
    if (i >= WordsAmount)
    {
        goto Finish;
    }

    if (WordList[i].frequency && WordList[i].frequency < 100)
    {
        cout << WordList[i].word << ": ";
        Counter = 0;
        OutputPages:
            if (Counter < WordList[i].ind)
            {
                if (Counter == 0)
                {
                    cout << WordList[i].pages[Counter] + 1;
                }
                else if (WordList[i].pages[Counter] != WordList[i].pages[Counter - 1])
                {
                    cout << ", " << WordList[i].pages[Counter] + 1;
                }
                Counter++;
                goto OutputPages;
            }
        cout << endl;
    }
    i++;
    goto Output;

Finish:
    return 0;
}
