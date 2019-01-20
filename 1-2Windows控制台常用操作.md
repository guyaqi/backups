# Windows控制台常用操作

WindowsAPI的函数大多名称较长，如果不是有意向专门学习的话，没有太大的必要特地记住(用的时候还是会忘)

微软公司出产的各种API，都可以在[msdn](https://msdn.microsoft.com/zh-cn/)找到详细的文档和简单的例子，如果你想了解某个WindowsAPI的所有用法，这是最权威的地方。

## Hello, world

第一个例子不是helloworld会让人误以为教程很难

```
#include <stdio.h>
#include <stdlib.h>

int main()
{
	system("color 3f");
	printf("Hello, world.\n");
	return 0;
}
```
不同操作系统的命令行环境有很大不同。在仅仅使用标准输入输出的时候差别不大，所以一般只涉及输入输出的程序代码，稍作修改或者不用修改就能正常的在其他操作系统编译并使用。

上面的代码改变了命令行的背景色，system函数是一个标准的C语言函数，用来执行一条命令，color命令是Windows控制台自带的命令，用于改变控制台默认的前景色(输出文字的颜色)和背景色。由于其他的系统默认是没有这条命令的，所以这行代码只能在Windows上使用。

关于color命令，更多的信息可以在网上**方便的**找到。

## 彩虹屁

上面的例子只能调整前景色和背景色，显然不够绚丽。
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int main()
{
	int fc, bc;
	HANDLE handle;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));

	while (true) {
		fc = rand() % 16;
		bc = rand() % 16;
		SetConsoleTextAttribute(handle, fc<<4 + bc);
		putchar('#');
	}
	return 0;
}

```
这次这个程序只能手动关闭。。。是停不下来的。。。

上面的例子只是疯狂的改变前景色和背景色，然后输出一个'#'。

HANDLE是Windows系统最常用的一种数据结构，通常叫做句柄，用来表示一个窗口，一个设备抽象等等，创建一个窗口，或者修改一些东西的时候经常要创建或者获取句柄。

上面通过GetStdHandle获取了标准输出设备的句柄，t通过SetConsoleTextAttribute修改了标准输出的颜色。所以接下来的输出就变色了。

## 蒙多想去哪就去哪

```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int main()
{
	HANDLE handle;
	COORD coord;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));

	for (int i = 0; i < 20; i++) {
		coord.X = rand() % 40;
		coord.Y = rand() % 18;
		SetConsoleCursorPosition(handle, coord);
		printf("Hello, world.");
	}
	return 0;
}

```

这个例子在屏幕的各个位置输出了Hello, world。

COORD是一个简单的结构体，只有X和Y两个成员，用来表示光标位置。

SetConsoleCursorPosition设置了光标的位置，光标在哪，当然就从什么位置输出。

## 眼不见心不烦
有时候你可能不想看见那个光标。

```
#include <stdio.h>
#include <Windows.h>

int main()
{
	HANDLE handle;
	CONSOLE_CURSOR_INFO cursor = {100,FALSE};

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);

	printf("Loading");
	for (int i = 0; i < 5; i++) {
		putchar('.');
		Sleep(1000);
	}
	return 0;
}
```

## 实时交互
使用标准输入的程序只能在输入回车后输入的数据才能一并被读取，要实现更好的交互模式肯定需要学习新的方法。

```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

char words[][128] = {
	"别碰我！",
	"咸猪手！",
	"离我远点！"
};

int main()
{

	PBYTE keys = new BYTE[256];
	int count;
	BOOL warning = FALSE;

	srand(time(0));
	
	while (true) {
		
		count = 0;
		for (int i = 65; i <= 90; i++) {
			if (GetKeyState(i) >= 0)
				count++;
		}

		if (count == 26) {
			system("cls");
			warning = FALSE;
		} else if(!warning){
			printf("%s", words[rand()%3]);
			warning = TRUE;
		}
	}
	return 0;
}
```

这是一个调皮的程序。。。。

GetKeyState获取某个键是否被按下，按下返回负数。参数是一种叫**虚拟键码**的东西，并不是ascii编码，只是在字母键的范围它们是一样的。

## 我的Console我做主

作业:设计一个改变控制台配色的程序，预先搭配好三五个配色，在执行程序的时候可以随时切换，要求使用方向键进行控制，界面看起来就像这样。
```
----------------------------------



            Colors
        1. While & Blue
    ->  2. Red & Grey
        3. While & Black
        4. While & Blue

       This is a test text.

----------------------------------
```

箭头可以使用方向键控制，并且可以切换到指定的配色。

最好选项就用那个选项指示的配色显示，这样看起来更直观。

## 总结

上面的几个小例子都弄懂了，写一个控制台的推箱子，贪吃蛇，俄罗斯方块是完全可以的。如果你喜欢，可以做一做尝试。

## 感谢

感谢南方姑娘为我指出了上一期中出现的问题。还有谢谢你读完这篇文章。