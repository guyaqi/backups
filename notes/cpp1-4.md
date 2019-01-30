# 简单Console程序设计 2

这次是在动真格的之前在分享一些常用的技巧

## Hello, world

第一个例子不是helloworld会让人误以为教程很难

```
#include <stdio.h>
#include <Windows.h>

int main() {
    TCHAR str[] = TEXT("Hello, world!");
    SetConsoleTitle(str);
    getchar();
    return 0;
}

```

注意控制台的窗口标题改变了。
getchar是为了防止程序直接运行结束，那样标题就会被重置。

注意TCHAR与TEXT宏,这两个宏在对应的情况下有不同的解释，这与你的编译器默认使用的编码方式相关。
* 当UNICODE宏被定义的时候(MSVC编译器指令/D UNICODE)，TCHAR是wchat_t,TEXT宏被解释成C语言内部用来转换宽字符的宏(L"somestr")
* 如果没有定义UNICODE宏,TCHAR就是char,TEXT宏不进行任何操作。

这种设定是在utf-8编码没有被广泛支持的时候,为了程序代码能够兼容使用不同代码的机器设定的，比如我使用的win7默认使用gb2312(还是gbk来着)字符集对应的编码方式,而win10以上和其他使用linux内核的系统默认使用utf-8编码方式。

值得一提的是utf-8使用char,而通常C++,Java,C#对UNICODE的支持指的是使用utf-16的编码方式,在C++中utf-16字符就是wchar_t(宽字符)。

更多关于编码的东西我找个机会写一篇。

## 江南皮革厂倒闭了

```
#include <stdio.h>
#include <string.h>
#include <Windows.h>

wchar_t ad[] = L"                                 "
"浙江温州，浙江温州，最大皮革厂，江南皮革厂倒闭了！"
"老板黄鹤吃喝嫖赌，欠下了3.5个亿，带着他的小姨子跑了。"
"我们没有办法，拿着钱包抵工资。"
"原价都是三百多、二百多、一百多的钱包，通通二十块，通通二十块！"
"黄鹤你不是人，我们辛辛苦苦给你干了大半年，你不发工资，你还我血汗钱，还我血汗钱！";

int main() {

    bool done = false;
    while (!done) {
        for (int i = 0; i < wcslen(ad); i++) {
            SetConsoleTitle(ad+i);
            Sleep(200);
        }
    }
    return 0;
}

```

## 私人订制

```
#include <stdio.h>
#include <string.h>
#include <Windows.h>

int main() {
	system("mode con: cols=120 lines=35");
	system("color 3f");
	printf("您的专属豪华版控制台:)");
	getchar();
	
	return 0;
}

```

没错只不过是改了大小。。。

## End

作业暂时没有，明天争取继续更新。
