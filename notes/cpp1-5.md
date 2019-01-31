# 简单Console程序设计 3

这次是分享一个控制台交互的代码框架

## Hello, world

第一个例子不是helloworld会让人误以为教程很难

```
#include <stdio.h>

int main() {
    printf("Hello, world!\n");
    return 0;
}

```

一个helloworld用来代替我自己祭天

## 盒子里的钟大少

能使用方向键控制钟大少的移动，但是钟大少已经被关进Console了。

```
#include <stdio.h>
#include <Windows.h>

constexpr int lines = 15;
constexpr int cols = 35;
int x, y;

void go(int x, int y);
void setCursorVisable(bool visable);
void keyDownCallback(int vk, void(*callback)());

void init();
void update();
void onUpKey();
void onLeftKey();
void onDownKey();
void onRightKey();


int main() {
    bool done = false;
    init();
    update();
    while (!done) {
        keyDownCallback(VK_UP, onUpKey);
        keyDownCallback(VK_LEFT, onLeftKey);
        keyDownCallback(VK_DOWN, onDownKey);
        keyDownCallback(VK_RIGHT, onRightKey);
        keyDownCallback(VK_ESCAPE, []() {exit(0); });
    }
}

void init() {
    system("mode con: cols=30 lines=15");
    setCursorVisable(false);
    x = 1;
    y = 1;
}
void update() {
    system("cls");
    go(x, y);
    printf("#");
}

void go(int x, int y) {
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), 
        {(short)x, (short)y});
}

void onUpKey() { 
    if (y > 0)y -= 1; 
    update();
}
void onLeftKey() { 
    if (x > 0)x -= 1;
    update();
}
void onDownKey() {
    if (y < lines - 1)y += 1;
    update();
}
void onRightKey() { 
    if (x < cols - 1)x += 1;
    update();
}

void keyDownCallback(int vk, void(*callback)()) {
    static bool callbackCalled[256] = { 0 };
    if (GetKeyState(vk) < 0) {
        if (!callbackCalled[vk]) {
            callbackCalled[vk] = true;
            callback();
        }
            
    } else {
        callbackCalled[vk] = false;
    }
}

void setCursorVisable(bool visable) {
    CONSOLE_CURSOR_INFO info;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(handle, &info);
    info.bVisible = visable;
    SetConsoleCursorInfo(handle, &info);
}
```

这三个是底层的包装，因为Windows的函数都太长了，你懂。。。
* go 设置光标位置
* setCursorVisable 用来隐藏光标
* keyDownCallback 这个函数包装了一小段逻辑，检测某个键是否按下，按下就调用后面的函数

这几个是程序逻辑的每一部分
* init 初始化了光标的位置x和y并且做了一些其他的小事情
* update 根据xy重新画出钟大少的新位置
* onUpKey 把钟大少向上移动
* onLeftKey 把钟大少向左移动
* onDownKey 把钟大少向下移动
* onRightKey 把钟大少向右移动

main函数中响应Esc退出那段使用了Lambda表达式，没学过的可以去了解一下。

## End

作业暂时没有，争取明天继续更新
