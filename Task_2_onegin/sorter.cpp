#include "sorter.h"
#include <stdlib.h>
#include <stdio.h>
#include <cwctype>
#include <clocale>
#include <ctime>
#include <ctype.h>
#include <cmath>
#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>
#include "converter.h"

/**
 * @file sorter.cpp
 *
 * @brief Contains definitions of functions for sorting strings(Link)
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 10/17/2020
 */




int CmpWstr(const void* ptr1, const void* ptr2, int inc)
{
    Assert_c(ptr1 != NULL);
    Assert_c(ptr2 != NULL);

    if (ptr1 == NULL || ptr2 == NULL)
        return 0;

    C_string s1 = *((C_string*)ptr1);
    C_string s2 = *((C_string*)ptr2);

    while (!std::iswalpha(*s1) && *s1)
        s1 += inc;

    while (!std::iswalpha(*s2) && *s2)
        s2 += inc;

    while (*s1 && (*s1 == *s2))
    {
        do
            s1 += inc;
        while (!std::iswalpha(*s1) && *s1);
           
        do
            s2 += inc;
        while (!std::iswalpha(*s2) && *s2);
    }

    return (unsigned int)(*s1) - (unsigned int)(*s2);
}


/**
\brief  Функция сравнения двух структур Link
\detail Данная функция производит сравнение двух строк, которые записаны в структуре Link
в полях start и end. В зависимости от выбора функции будет использоваться тот или этой указатель
в Link.
\param  [in]   ptr1    Указатель на первую структуру Link
\param  [in]   ptr2    Указатель на вторую структуру Link
\retrun Возвращает положительное число, если первая строка (из структуры Bijection) идет позже (в смысле лексиграфического порядка),
чем вторая строка. Соответсвенно возвращает отрицательное, если вторая строка идет позже первой,
и ноль в случае совпадания строк.
@{
*/
static int CmpTableDirect(const void* ptr1, const void* ptr2)
{
    Assert_c(ptr1 != NULL);
    Assert_c(ptr2 != NULL);
    if (ptr1 == NULL || ptr2 == NULL)
        return 0;

    Link b1 = *((Link*)ptr1);
    Link b2 = *((Link*)ptr2);
    return CmpWstr(&b1.start, &b2.start, 1);
}
static int CmpTableInverse(const void* ptr1, const void* ptr2)
{
    Assert_c(ptr1 != NULL);
    Assert_c(ptr2 != NULL);
    if (ptr1 == NULL || ptr2 == NULL)
        return 0;

    Link b1 = *((Link*)ptr1);
    Link b2 = *((Link*)ptr2);
    return CmpWstr(&b1.end, &b2.end, -1);
}
/** @}*/

/**
\brief  Функция генерирует массив символов, содержащий строки считываемого файла.
\detail Функция генерирует массив символов, содержащий строки считываемого файла.
Каждая строка в массиве отделена от предыдущей нулевым символом. Пустые
строки в массив не записываются.
\param  [in]      filename          Имя считываемого файла
\param  [in,out]  outArray          Выходной массив
\param  [out]     outArrayLength    Размер выходного массива
\param  [out]     outNumDividers    Количество разделителей в выходном массиве
\note  В массив записываются знаки препинания и русские буквы, остальные символы пропускаются.
       Символ, стоящий перед указателем outArray всегда будет нулевым.
       При освобождении памяти следует вызывать free(outArray-1);
*/
static int GenerateDividedString(const char* filename, C_string* outArray, int* outArrayLength = NULL, int* outNumDividers = NULL)
{
    Assert_c(filename != NULL);
    if (filename == NULL)
        return SS_ERROR_NULLPTR;

    int fileSize = 0;
    int numLines = 0;
    {
        struct stat st;
        stat(filename, &st);
        fileSize = st.st_size;
    }

    int filedesc = open(filename, O_RDONLY);
    if (filedesc == -1)
        return SS_ERROR_ACCESS_FAIL;

    char* buffer = (char*)calloc(fileSize + 2, sizeof(char));
    if (!buffer)
        return SS_ERROR_NULLPTR;
    buffer++;
    buffer[fileSize] = 0;
    buffer[-1] = 0;
    

    int nReadBytes = read(filedesc, buffer, fileSize);
    if (nReadBytes< 0)
    {
        free(buffer - 1);
        close(filedesc);
        return SS_ERROR_ACCESS_FAIL;
    }
    buffer[nReadBytes] = 0;

    int countLetters = utf8StrLen(buffer);
    C_string data = (C_string)calloc(countLetters + 2, sizeof(C_string));
    data[0] = 0;
    data++;
    data[countLetters] = 0;
    utf8ToWchar(data, buffer);

    free(buffer-1);
    close(filedesc);

    *outArray = data;
    
    wchar_t w[2] = { 0, L'\n' };
    bool pingpong = 0;
    int currPtr = 0;
    int additionPtr = 0;

    fileSize = 0;
    numLines = 0;
    

    while ((w[pingpong] = data[additionPtr]) != 0)
    {
        bool isValidSymbol = (bool)wcschr(L",.;?!- \"", w[pingpong]) | (L'А' <= w[pingpong] && L'Я' >= w[pingpong]) || (L'а' <= w[pingpong] && L'я' >= w[pingpong]);
        if (w[pingpong] != L'\n' & isValidSymbol)
        {
            data[currPtr] = w[pingpong];
            currPtr++;
            fileSize++;
        }
        if (w[pingpong] == L'\n' && w[pingpong ^ 1] != L'\n')
        {
            data[currPtr] = L'\0';
            currPtr++;
            numLines++;
        }
        
        pingpong ^= 1;
        additionPtr++;
    }
    data[currPtr] = 0;
    numLines++;
    

    data = (C_string)realloc(data - 1, (fileSize + numLines +  1)*sizeof(wchar_t));
    Assert_c(data != NULL);
    if (!data)
        return SS_ERROR_NULLPTR;

    if (outArrayLength)
        *outArrayLength = fileSize + numLines;
    if (outNumDividers)
        *outNumDividers = numLines;
    return 0;
}

/**
\brief  Функция генерит таблицу,хранящая начала и концы каждой строки
\param  [in]      firstArray     Первый массив
\param  [in]      nDividers      Количество разделителей в первом массиве
\param  [in,out]  outTable       Указатель на таблицу соответствий
\param  [in,out]  outArraySize   Размер таблицы
\note   Память под таблицу выделять не нужно. Всю память функция выделяет автоматически.
Требуется только указать, где будет храниться указатель на таблицу, именно это значение и
будет записано в outTable.
\return Код ошибки или ноль в случае успеха.
*/
static int GenerateBijection(const C_string* firstArray, const int nDividers, Link** outTable, int* outArraySize)
{
    Assert_c(firstArray != NULL);
    Assert_c(outTable != NULL);
    if (!firstArray || !outTable)
        return SS_ERROR_NULLPTR;
    Assert_c(*firstArray != NULL);
    if (!*firstArray)
        return SS_ERROR_NULLPTR;

    Link* table = (Link*)calloc(nDividers, sizeof(Link));;
    Assert_c(table != NULL);
    if (!table)
        return SS_ERROR_NULLPTR;
    *outTable = table;

    int tableSize = 0;

    table->start = 0;
    table->start = 0;
    table->end = 0;
    C_string ptr = *firstArray;
    for (int i = 0; i < nDividers; i++)
    {
        table->start = ptr;

        ptr = wcschr(ptr, L'\0');
        Assert_c(ptr != NULL);
        if (!ptr)
            return SS_ERROR_NULLPTR;

        table->end = ptr- 1;

        ptr++;
        if (table->end - table->start > 1)
        {
            table++;
            tableSize++;
        }
    }
    *outTable = (Link*)realloc(*outTable, sizeof(Link)*tableSize);
    *outArraySize = tableSize;
    return 0;
}


void SortFromFile(const char* in_filename, const char* out_filename, Direction dir)
{
    std::setlocale(LC_ALL, "en_US.utf8");

    Assert_c(in_filename != NULL);
    Assert_c(out_filename != NULL);
    if (in_filename == NULL || out_filename == NULL)
        return;

    FILE* outFile = fopen(out_filename, "w");
    Assert_c(outFile != NULL);
    if (outFile == NULL)
        return;

    int errorCode = 0;


    //Построение строки, которая разделяет строки исходного файла нулевым символом
    int arrLength = 0;
    int nDividers = 0;
    C_string data = NULL;
    errorCode = GenerateDividedString(in_filename, &data, &arrLength, &nDividers);
    if (errorCode)
    {
        fclose(outFile);
        if (data)
            free(data-1);
        return;
    }


    //Построение таблицы индексов
    Link* table = NULL;
    int tableSize = 0;
    errorCode = GenerateBijection(&data, nDividers, &table, &tableSize);
    if (errorCode)
    {
        fclose(outFile);
        free(data-1);
        if (table)
            free(table);
        return;
    }

    //сортировка и вывод
    qsort(table, tableSize, sizeof(Link), dir == Direct ? CmpTableDirect : CmpTableInverse);

    for (int i = 0; i < tableSize; i++)
        fprintf(outFile, "%ls\n", table[i].start);

    fclose(outFile);
    free(data-1);
    free(table);
    return;
}

























