/**
 *  Вариант 28
    Словарь.
    А: слово на русском языке (слово, часть речи).
    Б: слово на иностранном языке (слово, часть речи, возможные формы
    слова).
    Каждое слово на русском языке может переводиться несколькими
    вариантами иностранных слов. И наоборот
 */

#include "structs.h"
#include "functions.h"

#include <stdio.h>
#include <stdlib.h>


/**
 *  Главная функция программы с возможностью вывода информации и
 *  выбора дальнейших действий
 */
int main()
{
    char* wordToAddRus;
    char* wordToAddEng;
    char* partOfSpeechRus;
    char* partOfSpeechEng;

    int userChoice;

    EDblLinkedList* russianWords = createEdblLinkedList();
    ODblLinkedList* englishWords = createOdblLinkedList();

    do
    {
        printMenu();
        printf("Enter your choice:\n");
        printf(">");
        userChoice = intInputCheck();
        switch (userChoice)
        {
            case ADD_ENG_WORD:
                puts("Enter English word to add:");
                wordToAddEng = getDynamicString(wordToAddEng);

                printf("Enter part of speech of the word %s:", wordToAddEng);
                partOfSpeechEng = getDynamicString(partOfSpeechEng);

                if(wordToAddEng[0] == '\0' || partOfSpeechEng[0] == '\0')
                {
                    puts("incorrect words were entered!");
                    break;
                }
                else
                {
                    addEngWord(wordToAddEng, partOfSpeechEng, englishWords);
                    printf("English word %s with %s part of speech has been "
                           "added!\n", wordToAddEng, partOfSpeechEng);
                }
                break;

            case ADD_RUS_WORD:
                puts("Enter Russian word to add:");
                wordToAddRus = getDynamicString(wordToAddRus);

                printf("Enter part of speech of the word %s:", wordToAddRus);
                partOfSpeechRus = getDynamicString(partOfSpeechRus);

                if(wordToAddRus[0] == '\0' || partOfSpeechRus[0] == '\0')
                {
                    puts("incorrect words were entered!");
                    break;
                }
                else
                {
                    addRusWord(wordToAddRus, partOfSpeechRus, russianWords);
                    printf("Russian word %s with %s part of speech has been "
                           "added!\n", wordToAddRus, partOfSpeechRus);
                }

            case DELETE_WORDS:

                break;

            case PRINT_WORDS:
                printWords(russianWords, englishWords);
                break;

            case MAKE_MANY_TO_MANY_BOND:
                printRusWords(russianWords);

                puts("Enter the number of Russian word:");
                int rusWordNum = intInputCheck() - 1;
                RusNode* pickedRusWord = getRussianWord(russianWords,
                                                        rusWordNum);
                if (pickedRusWord == NULL)
                {
                    puts("No words added "
                         "or Incorrect Russian word number entered!");
                    break;
                }

                printEngWords(englishWords);
                puts("Enter the number of English word:");
                int engWordNum = intInputCheck() - 1;
                EngNode* pickedEngWord = getEnglishWord(englishWords,
                                                        engWordNum);
                if (pickedEngWord == NULL)
                {
                    puts("No words added "
                         "or Incorrect English word number entered!");
                    break;
                }

                if (connectNodes(pickedEngWord, pickedRusWord))
                {
                    printf("\nRelation: %s  ♾️———— ♾️%s\n",
                           pickedRusWord->value.word,
                           pickedEngWord->value.word);
                    puts("New Many-to-many relation made!");
                }
                break;

            case UPLOAD_TO_FILE:
                loadToFile(russianWords, englishWords);
                break;

            case DOWNLOAD_FROM_FILE:
                downloadFromFile();
                break;

            case EXIT:
                puts("Goodbye!");

                deleteEdblLinkedList((EDblLinkedList **) &wordToAddRus);
                deleteOdblLinkedList((ODblLinkedList **) &wordToAddEng);
                break;

            default:
                puts("Incorrect value!");
        }

    } while (userChoice != EXIT);
    return 0;
}
