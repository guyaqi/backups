# 简单Console程序设计 2

这次是在动真格的之前在分享一些常用的技巧

## Hello, world

第一个例子不是helloworld会让人误以为教程很难

```
#include <stdio.h>
#include <Windows.h>

int main() {
    wchar_t str[] = L"Hello, world!";
    SetConsoleTitle(str);
    system("pause");
    return 0;
}

```

注意控制台的窗口标题改变了。
pause指令是为了防止程序直接运行结束，那样标题就会被重置。

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

## 