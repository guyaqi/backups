# 简单Console程序设计

这次主要是以实例程序来演示简单Console程序的写法

## Hello, world

第一个例子不是helloworld会让人误以为教程很难


```
#include <stdio.h>
#include <Windows.h>

void rand_pos();
void rand_color();

int main() {

    int done = 0;
    while (!done) {
        if (GetKeyState(VK_ESCAPE) < 0)
            done = 1;
        rand_color();
        rand_pos();
        printf("Hello, world");
    }
    return 0;
}

void rand_pos() {
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        { rand()%60, rand() % 25 }
    );
}

void rand_color() {
    char cmd[] = "color 00";
    for (int i = 6; i <= 7; i++) {
        cmd[i] = rand() % 16;
        if (cmd[i] < 10)
            cmd[i] += '0';
        else
            cmd[i] += 'a' - 10;
    }
    system(cmd);
}


```
如果你要这个helloworld程序有点长，那就吐槽吧。。。

这个程序稍微借鉴了模块化的设计思想，把要做的一件事分解成许多小事。在现实开发中，模块的划分在程序开发之前，否则就没办法明确的分工了，不好好的分工怎么清楚的分锅呢？

然而这一小段代码是没必要分成很多函数的，每个函数只调用了一次，并没有代码的重用，分开写只是为了提高可读性。并且给你一个例子，让你对模块化有一个初步的印象。

## 我说鸡蛋你说要

读这段代码之前，先看一下这段[Yo~老板,煎饼果子来一套~我说鸡蛋~你说要](https://tv.sohu.com/v/dXMvMjAyNzMzNzE2Lzc5MDE5ODk0LnNodG1s.html)

按空格来说要，和QQ炫舞一样(手动滑稽)

```
#include <stdio.h>
#include <time.h>
#include <Windows.h>

char words_start[][256] = {
	"在这寒冷的冬天来套煎饼果子",
	"这香香的味道让你神魂颠倒"
};

char words[][256] = {
	
	"哎 火腿肠要不要",
	"鸡蛋 要不要",
	"我说鸡蛋你说要",
	"鸡蛋",
	"鸡蛋",
	"鸡蛋 鸡蛋 鸡蛋",
	"鸡蛋 鸡蛋 鸡蛋 鸡蛋 鸡蛋 鸡蛋",
	
};

int yo[] = {
	1,1,0,1,1,3,8
};

char words_end[][256] = {
	"哎呦 棒极了",
	"咋的 不配合呢"
};

void go_to(short, short);
void rand_color();
void cls();
void wait_short();
void wait_long();
void hide_cursor();
int beats(double seconds);


int main() {

	int line = 4;
	int miss = 0;

	rand_color();
	hide_cursor();

	for (auto str : words_start) {
		go_to(3, line);
		line++;
		printf("%s\n", str);
		wait_long();
	}

	for (int i = 0; i < 7; i++) {
		go_to(3, line);
		line++;
		printf("%s\n", words[i]);
		if (i == 6) {
			wait_long();
		}
		else {
			wait_short();
		}
		for (int j = 0; j < yo[i]; j++) {
			if (!beats(1.8))
				miss++;
		}
	}
	Sleep(2000);
	cls();
	go_to(5, 5);
	if (miss > 5) {
		printf("%s", words_end[1]);
	}else {
		printf("%s", words_end[0]);
	}
	return 0;
}

void go_to(short x, short y) {
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		{ x, y }
	);
}

void rand_color() {
	char colors[][64] = {
		"color 3f",
		"color 4e",
		"color 5c",
		"color 0d",
		"color c2",
		"color f3",
		"color 64",
	};
	system(colors[rand()%7]);
}

void cls() {
	system("cls");
}

void wait_short() {
	Sleep(600);
}
void wait_long() {
	Sleep(1800);
}

void hide_cursor() {
	CONSOLE_CURSOR_INFO cursor = { 1, FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

int beats(double seconds) {
	clock_t start = clock();
	double twentieth = seconds / 20;
	static int responsed = 0;

	for (int i = 0; i < 20; i++) {
		do {
			
			if (GetKeyState(VK_SPACE) < 0 && !responsed) {
				responsed = 1;
				go_to(3, 3);
				printf(">>>>>>>>>>>>>>>>>>>>>>");
				rand_color();
				return 1;
			}
			if (GetKeyState(VK_SPACE) <= 0) {
				responsed = 0;
			}
				
		}while (clock() - start < twentieth * i * CLK_TCK);
		go_to(3, 3);
		char bar[] = ">--------------------<";
		bar[i+1] = '*';
		printf("%s", bar);
	}
	return 0;
}
```

go_to函数让切换光标位置更方便了，如果你确定一件事情要做很多次，写一个函数会是很方便的做法。

cls是仅仅一行的函数，我仅仅是为了少打几个字母而已。

因为我把所有的游戏逻辑都写到了main函数里面，剩下的几个函数就只是为了让程序逻辑清晰一点。

这个小例子是我仓促写出来的，难免有疏漏，如果有改进的建议可以发PR，或者联系我(QQ:1360668777)

## 优化设计

如果你上一次的作业是一个main到底的，代码里面有很多相同的部分是复制粘贴的，请你认真思考，并且修改代码。让程序更清晰易读。

## 总结

把你经常会复制粘贴的代码封装成函数，会提高效率改善心情。程序的可读性也会变强。

