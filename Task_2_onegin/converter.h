#pragma once
#include <wchar.h>
#include <assert.h>


#ifdef NDEBUG
#define Assert_c(expr) if(!(expr))printf("Expression %ls is false.\n In file: %ls\n line: %d\n",_CRT_WIDE(#expr), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)); ///< Реализация assert для релиза
#else
#define Assert_c(expr) assert(expr); ///< Реализация assert для отладки переключить режим можно директивой #define NDEBUG
#endif

/**
\brief  Функция считает количество символов, закодированных в utf8
\param  [in]      src   Указатель на строку, закодированную в utf8
\return Возвращает количество символов, закодированных в utf8 или -1
        в случае ошибки.
\note   Ошибка может быть возвращена, если в строке имеется символ,
        для кодирования которого требуется более 3х байт.
*/
int utf8StrLen(const char* src);


/**
\brief  Функция преобразвет строку, закодированную в utf8 в массив wchar_t
\param  [in,out]  dest  Указатель на преобразованный массив
\param  [in]      src   Указатель на строку, закодированную в utf8
\return Возвращает 0, если преобразование прошло успешно, -1 в случае ошибки.
\note   Ошибка может возникнуть, если исходная utf8 строка содержала в себе символы,
        которые кодируются более чем 3 байтами, дело в том, что такие символы не
        помещаются в whcar_t.
*/
int utf8ToWchar(wchar_t* dest, const char* src);
