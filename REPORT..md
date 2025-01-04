|    |
| :- |

# **1 样例工程分析**

## **1.1 fork样例工程，并clone到本地仓库；**

Fork样例工程

[![1.png](https://i.postimg.cc/qqy5YV11/1.png)](https://postimg.cc/646c2SJZ)

如上图所示，已经fork成功
上述为fork的仓库

Clone到本地仓库

[![2.png](https://i.postimg.cc/J4dkgDBd/2.png)](https://postimg.cc/MvVHfG5y)
[![3.png](https://i.postimg.cc/PrqD2zNw/3.png)](https://postimg.cc/8sqsCvRp)


在对应的文件夹中找到该项目

[![4.png](https://i.postimg.cc/Nj9Hws6G/4.png)](https://postimg.cc/yDKdmzp2)
 

## **1.2 在本地开发环境上运行样例工程，理解样例工程的代码逻辑**，**精读样例工程软件代码，描述代码结构及部件组成；**

成功运行样例工程

[![5.png](https://i.postimg.cc/Bnr1SrpT/5.png)](https://postimg.cc/MnYGtrhH)

整体代码结构和组成分析

&#x20;层次结构:

*   游戏的核心由`Game`类控制。`Game`类负责管理房间（通过`Room`类）、解析命令（通过`Parser`类）和执行命令。
*   `Command`和`CommandWords`类用于处理用户输入的命令，`Command`类封装了命令的结构，`CommandWords`类验证命令的有效性。
*   `Room`类代表游戏世界中的单个房间，每个房间有多个出口（与其他房间连接）。
*   `Parser`类通过将用户输入转换为命令对象，为`Game`类提供命令解析功能。

&#x20;模块化设计:

*   每个类都有明确的职责，遵循了单一职责原则（SRP）。`Game`负责游戏逻辑，`Room`处理房间和出口，`Parser`解析输入，`Command`封装命令，`CommandWords`提供命令验证。

 交互流程:

*   用户通过命令行输入指令（如“go north”或“quit”）。
*   `Parser`类解析输入，生成`Command`对象。
*   `Game`类根据`Command`对象执行相应的操作（如移动到新房间、退出游戏、显示帮助等）。

·**扩展性**:

*   目前的代码框架已经实现了基础的命令解析、房间管理和用户交互。该架构非常适合扩展，比如可以添加更多的命令、房间类型、物品管理、角色管理等功能。
*   新的功能可以通过增加新的类或在现有类中增加方法来实现。

 **Game类分析：**

1\. Game() 构造函数

public Game() {

    createRooms();

    parser = new Parser();

}

作用：这是Game类的构造函数，用于初始化游戏对象。

细节：createRooms()：调用这个方法来创建游戏中的房间并将它们连接成迷宫。

parser = new Parser();：创建一个Parser对象，用于解析玩家输入的命令。

 

2\. createRooms() 方法

private void createRooms() {

…

}

作用：该方法用于创建所有的房间并连接它们形成一个迷宫。每个房间有不同的出口，并且它们之间通过这些出口进行连接。

细节：创建了五个房间（outside, theater, pub, lab, office），每个房间的描述提供了它的名称或位置。使用 setExit() 方法为每个房间设置出口，出口指定了房间的方向（如 "east", "south" 等）。最后，将currentRoom设置为outside，意味着玩家从“主入口外”开始游戏。

 

3\. play() 方法

public void play() {

    printWelcome();

    boolean finished = false;

    while (!finished) {

        Command command = parser.getCommand();

        finished = processCommand(command);

    }

    System.out.println("Thank you for playing.  Good bye.");

}

作用：这是游戏的主控循环，负责不断接收并处理玩家的命令，直到玩家选择退出游戏。

细节：调用printWelcome()显示欢迎信息。进入一个while循环，反复调用parser.getCommand()获取玩家输入的命令。调用processCommand(command)来处理每一个命令，并通过返回值finished来判断是否结束游戏。如果玩家选择退出游戏，打印感谢信息并结束。

 

4\. printWelcome() 方法

private void printWelcome() {

    System.out.println();

    System.out.println("Welcome to the World of Zuul!");

    System.out.println("World of Zuul is a new, incredibly boring adventure game.");

    System.out.println("Type 'help' if you need help.");

    System.out.println();

    System.out.println(currentRoom.getLongDescription());

}

作用：显示游戏的欢迎信息，并提供当前房间的详细描述。

细节：输出游戏的介绍信息，告诉玩家游戏非常无聊。显示玩家当前所在房间的长描述（currentRoom.getLongDescription()）。

 

5\. processCommand(Command command) 方法

private boolean processCommand(Command command) {

…

    }

作用：处理玩家输入的命令，根据命令类型执行不同的动作。

细节：检查命令是否有效，如果无效（command.isUnknown()），则输出提示信息。根据命令的第一个单词（commandWord）来判断执行什么操作：help：调用printHelp()显示帮助信息。go：调用goRoom(command)处理房间移动。quit：调用quit(command)处理退出游戏。返回值 wantToQuit 为true时，表示玩家选择退出游戏。

 

6\. printHelp() 方法

private void printHelp() {

    System.out.println("You are lost. You are alone. You wander");

    System.out.println("around at the university.");

    System.out.println();

    System.out.println("Your command words are:");

    parser.showCommands();

}

作用：输出游戏的帮助信息，显示玩家可以使用的命令。

细节：显示一段关于玩家在大学校园里迷路的描述。调用parser.showCommands()显示所有有效的命令（例如“go”，“quit”，“help”等）。

 

7\. goRoom(Command command) 方法

private void goRoom(Command command) {…

}

作用：处理“go”命令，让玩家移动到指定方向的房间。

细节：检查命令是否包含第二个单词（即方向），如果没有，则提示玩家输入一个方向。根据玩家输入的方向（如“east”，“west”等），调用currentRoom.getExit(direction)查找对应方向的房间。如果房间存在，则更新currentRoom并显示新房间的描述；如果没有对应的出口，则提示“没有门”。

 

8\. quit(Command command) 方法

private boolean quit(Command command) {

    if(command.hasSecondWord()) {

        System.out.println("Quit what?");

        return false;

    }

    else {

        return true;

    }

}

作用：处理“quit”命令，结束游戏。

细节：如果命令包含第二个单词（即“quit”后跟其他文字），则询问玩家“Quit what?”。如果没有第二个单词，则返回true，表示游戏结束。

 

 

**Room类分析：**

1.public class Room {

    private String description;

    private HashMap\<String, Room> exits;

}

description：保存房间的简短描述（如“在讲座厅”）。

exits：使用 HashMap\<String, Room> 类型的变量来存储房间的出口。String 表示出口的方向（如 "north"、"south" 等），Room 表示该方向上对应的

间。

 

2\. 构造函数 Room(String description)

public Room(String description) {

    this.description = description;

    exits = new HashMap<>();

}

作用：构造 Room 对象，初始化房间的描述以及出口的集合。

细节：

description 用来描述房间的简短描述。

exits 初始化为空的 HashMap，用于存储出口信息。

 

3\. setExit(String direction, Room neighbor)

public void setExit(String direction, Room neighbor) {

    exits.put(direction, neighbor);

}

作用：设置房间的出口。

细节：

direction：出口的方向（如 "north", "east" 等）。

neighbor：该方向上连接的房间。

通过 exits.put(direction, neighbor) 将方向和房间对象存储在 exits 中，表示从当前房间可以通过某个方向到达另一个房间。

 

4\. getShortDescription()

public String getShortDescription() {

    return description;

}

作用：返回房间的简短描述。

细节：

返回房间的基本描述 description，例如 "in a lecture theater" 或 "outside the main entrance" 等。

 

5\. getLongDescription()

public String getLongDescription() {

    return "You are " + description + ".\n" + getExitString();

}

作用：返回房间的详细描述，包含房间描述和出口信息。

细节：

返回的字符串包含了房间的描述 description 和出口信息。具体出口信息是通过调用 getExitString() 方法得到的。

 

6\. getExitString()

private String getExitString() {

    String returnString = "Exits:";

    Set\<String> keys = exits.keySet();

    for (String exit : keys) {

        returnString += " " + exit;

    }

    return returnString;

}

作用：生成并返回当前房间的出口信息。

细节：

通过 exits.keySet() 获取所有的出口方向（即 HashMap 的键集合）。

遍历这些方向，将它们拼接成一个字符串，以空格分隔，形成形如 "Exits: north south east" 的格式。

返回这个字符串，显示当前房间的所有出口方向。

 

7\. getExit(String direction)

public Room getExit(String direction) {

    return exits.get(direction);

}

作用：根据给定的方向返回对应的出口房间。

细节：

根据传入的方向 direction（例如 "north", "east" 等），从 exits 中获取对应的房间对象。

如果该方向没有出口，则返回 null。

 

 

 

**Command类分析：**

1\. 构造函数 Command(String firstWord, String secondWord)

作用：这个构造函数用于创建一个新的 Command 对象，并初始化命令的两个部分：

commandWord：命令的第一个单词（如 "go"、"look" 等）。

secondWord：命令的第二个单词（例如，“east” 或物品的名称）。

该构造函数将 firstWord 和 secondWord 传递给类的字段 commandWord 和 secondWord。

 

2\. getCommandWord()

作用：返回命令的第一个单词（commandWord）。例如，如果命令是 "go east"，则返回 "go"。

3\. getSecondWord()

作用：返回命令的第二个单词（secondWord）。例如，对于命令 "go east"，则返回 "east"。如果命令没有第二个单词（例如 "go"），则返回 null。

4\. isUnknown()

作用：检查命令的第一个单词（commandWord）是否为空（null）。如果 commandWord 为 null，返回 true，表示该命令是未知的。否则，返回 false。这个方法可以用来判断用户输入的命令是否有效。

5\. hasSecondWord()

作用：检查命令是否包含第二个单词。它通过检查 secondWord 是否为 null 来确定。如果 secondWord 不为空，则返回 true，表示命令有第二个单词；否则返回 false。这个方法用于判断用户输入的命令是否需要第二个参数（例如方向、物品等）。

 

 

**CommandWords类分析：**

1.validCommands：这是一个静态数组，包含了游戏中有效的命令。当前有三个有效命令："go"、"quit"、"help"。

3\. isCommand(String aString)

作用：检查传入的字符串 aString 是否为有效的命令。

细节：

遍历 validCommands 数组，检查 aString 是否与数组中的任何一个命令相匹配。

如果匹配，返回 true，表示该命令有效。

如果遍历完所有命令仍没有找到匹配的命令，返回 false，表示无效命令。

该方法用于验证玩家输入的命令是否合法。

4\. showAll()

作用：显示所有有效的命令。

细节：

遍历 validCommands 数组，将所有的有效命令依次打印出来，中间以两个空格分隔。

最后输出一个换行符，使输出格式整洁。

该方法通常在玩家请求帮助时调用，帮助玩家了解可以使用的命令。



## **1.3 以UML图描述样例工程的组成及结构图（类及类之间的关系）**

**可结合markdown语法和mermaid插件绘制所需图形**

[![6.png](https://i.postimg.cc/d1B79LY6/6.png)](https://postimg.cc/sQMDjf1G)

 利用mermaid插件绘制UML图

**基数解释**

1.  **Game -> Room (1..\*)**:

    一个 `Game` 类实例管理多个 `Room` 实例。在 `createRooms()` 方法中，`Game` 会创建多个房间并设置它们之间的出口。因此，`Game` 与 `Room` 之间是 **一对多**（1..\*）的关系，即一个游戏实例管理多个房间实例。
2.  **Room -> Room (0..\*)**:

    每个 `Room` 类实例有多个出口，每个出口指向另一个房间，因此 `Room` 与 `Room` 之间是 **多对多**（0..\*）的关系。某些房间可能没有出口（例如，迷宫的起始房间），而其他房间则有多个出口。
3.  **Game -> Command (1..\*)**:

    游戏通过命令来进行控制，多个命令可能在游戏中的多个循环步骤中使用，因此 `Game` 与 `Command` 是 **一对多**（1..\*）的关系。
4.  **Parser -> CommandWords (1..1)**:

    `Parser` 类每个实例都需要一个 `CommandWords` 实例来验证命令。因此，`Parser` 和 `CommandWords` 之间是 **一对一**（1..1）关系。
5.  **Command -> CommandWords (0..1)**:

    每个 `Command` 类实例有时会包含一个 `CommandWords` 类实例（如处理具体命令时会调用），但也有可能某些命令没有对应的第二个单词。因此，`Command` 与 `CommandWords` 之间是 **零到一**（0..1）关系。

    

## **1.4 标注样例工程中的代码**

### **1.4.1 基于javadoc规范标注代码，对包、类、方法、代码片段、参数和语句等代码层次进行注释（可参考Game类的标注样例）**

对包、类、方法、代码片段、参数和语句等代码层次进行注释，下图为Room类的部分注释：

[![7.png](https://i.postimg.cc/XJ3GF9TX/7.png)](https://postimg.cc/LqC8Fg4M)



具体注释见代码

### **1.4.2注释后的代码提交到本地代码库后，同步推送到远程代码仓库**；

首先添加对应的文件到暂存区，并提交更改到本地仓库，然后推送至远程仓库
[![8.png](https://i.postimg.cc/vm5xc02p/8.png)](https://postimg.cc/TyY3sJ69)

[![9.png](https://i.postimg.cc/VvkJZms8/9.png)](https://postimg.cc/R62CNrns)



到github中查看，推送成功，**下图的initial commit 即为注释代码的提交更新**
[![10.png](https://i.postimg.cc/x8pcWhqb/10.png)](https://postimg.cc/rRWV4h18)
[![11.png](https://i.postimg.cc/J7pDDDK4/11.png)](https://postimg.cc/8srPxCqq)



## **1.5 扩充和维护样例工程**

### **1.5.1 对样例代码中的功能设计进行分析，找出若干设计缺陷和改进点，并进行修正或扩充，并集成到工程代码中；**

在当前 `Game` 类的 `processCommand()` 方法中，采用了大量的 `if-else` 语句来处理不同的命令。这种设计在添加新的命令时会导致以下问题：

1.  **可扩展性差**：每当需要新增命令时，都需要修改 `processCommand()` 方法，添加新的 `else if` 语句。这种方式导致代码膨胀，维护变得困难。
2.  **不符合面向对象设计原则**：根据面向对象设计原则，`Game` 类应该专注于游戏的控制，而不应该承担大量命令处理的逻辑。将命令处理逻辑与游戏控制逻辑分离，更符合单一职责原则。
3.  **难以维护**：随着命令数量的增加，`processCommand()` 方法会变得越来越复杂，且容易出错。

解决思路

为了解决上述问题，使用 \*\*命令模式 \*\* 来重构该代码。命令模式可以将每个命令封装成一个对象，使得 `Game` 类不再直接处理命令，而是将命令的处理交给各个命令类来完成。

设计改进

1.  **命令接口 (`Command`ITF)**：定义一个命令接口，其中包含一个 `execute()` 方法，所有的命令类都实现这个接口。
2.  **具体命令类**：每个命令（如 `GoCommand`、`HelpCommand`、`QuitCommand`）实现 `Command`ITF 接口，并定义 `execute()` 方法来执行特定的行为。
3.  **命令注册**：在 `Game` 类中，通过一个 `Map`（键值对）来管理所有的命令类，键是命令名称，值是具体的命令对象。这样，增加新的命令就只需要添加新的命令类，而不需要修改 `processCommand()` 方法。
4.  **命令执行**：在 `processCommand()` 方法中，`Game` 类只需要查找并执行对应的命令对象即可。

[![12.png](https://i.postimg.cc/65T7dW1V/12.png)](https://postimg.cc/TpMYx6xh)

命令接口的实现：

[![13.png](https://i.postimg.cc/kgbBpjCB/13.png)](https://postimg.cc/sM3jB4vr)

Gocommand类的实现：

[![14.png](https://i.postimg.cc/HsKrzqfq/14.png)](https://postimg.cc/crR14b1h)


其中boolean值用来判断是否放弃，helpcommand和Gocommand返回false,quitcommand返回game.quit(command)用来判断用户是否真的放弃；



**Parse命令的改进：**

在当前的 `Parser` 类中，命令解析的机制是将用户输入的命令字符串分为两个部分：`word1` 和 `word2`。具体地，`word1` 是命令的主词（例如，`go` 或 `quit`），`word2` 是命令的副词（例如，`north` 或 `south`）。然而，当用户输入的命令包含超过两个词时，例如 `take magic cookie`，这种情况会导致问题，因为目前的实现只考虑了两个词。

改进scanner分隔命令行的部分：

[![new.png](https://i.postimg.cc/sx4txC5v/new.png)](https://postimg.cc/xNqsp7x2)

将读取到的第一个词作为命令的主词，后面全部读取作为副词。



# **2 功能扩充点**

## **2.1 功能扩充点一**

**一个房间里可以存放任意数量的物件，每个物件可以有一个描述和一个重量值，玩家进入一个房间后，可以通过“look”命令查看当前房间的信息以及房间内的所有物品信息；**

1\. 创建一个 `Item` 类

物品类 `Item` 需要包含物品的描述和重量两个属性。实现对应的方法，例如获取描述已经重量。

[![15.png](https://i.postimg.cc/DzQm288h/15.png)](https://postimg.cc/2q6CGjQ9)


2\. 修改 `Room` 类

在 `Room` 类中添加一个 `items` 属性，这个属性是一个 `List<Item>` 或 `Set<Item>`，用于存储该房间内的所有物品。同时，我们需要提供一个方法来添加物品和一个方法来显示物品信息。

[![16.png](https://i.postimg.cc/W4chLMpS/16.png)](https://postimg.cc/Yv8pQLWm)

[![18.png](https://i.postimg.cc/XJQJCmfD/18.png)](https://postimg.cc/8JfN8ynh)



3\. 修改 `LookCommand` 类

修改 `LookCommand` 类，使得在执行 `look` 命令时，除了查看房间描述，还能查看房间内的物品信息。

[![19.png](https://i.postimg.cc/kGG5FswM/19.png)](https://postimg.cc/Mfkxzyhg)


首先获取当前所在房间，然后利用房间中的获取房间描述以及获取物品信息的描述函数获取描述并输出。

**实验结果**：事先在outside 房间中添加了大宝剑以及小宝剑如下图



执行look命令：

[![1.png](https://i.postimg.cc/SQdTnrw2/1.png)](https://postimg.cc/w3tcPhxg)

如上图所示，物品信息描述成功。

[![2.png](https://i.postimg.cc/fTg8KbWM/2.png)](https://postimg.cc/GHGP3dsf)

## **2.2 功能扩充点二**

基本的back实现，本项目直接实现更加高级的back可以连级退回原始房间，见下个扩展点实现描述。



## **2.3 功能扩充点三**

**在游戏中实现一个高级的“back”命令，重复使用它就可以逐层回退几个房间，直到把玩家带回到游戏的起点；**

为了实现这一功能，需要设计一个机制来追踪玩家的房间历史。具体来说，需要：

**记录玩家的当前位置和历史**：可以使用一个栈（`Stack`）来存储玩家的历史房间，每次玩家进入一个新房间时，就将当前房间推入栈中；而当玩家使用“back”命令时，弹出栈顶的房间并返回到该房间。

[![21.png](https://i.postimg.cc/3rfNJMJk/21.png)](https://postimg.cc/hhxcp5mn)

**更新房间对象**：每次玩家移动时，更新其当前所在的房间，并推送到历史栈中。

[![22.png](https://i.postimg.cc/J49hZbXm/22.png)](https://postimg.cc/kBv9dRwh)

**命令的处理**：通过定义一个 `BackCommand` 类来实现 `CommandITF` 接口，处理玩家的“back”命令。

[![23.png](https://i.postimg.cc/T3g39pjb/23.png)](https://postimg.cc/sMfzffNf)

[![24.png](https://i.postimg.cc/1zS5YsMj/24.png)](https://postimg.cc/G4MC40WF)

每次调用back函数时，从历史房间栈中返回一个房间并输出房间描述，如果在初始房间则提示玩家已经在初始房间中没有地方返回。



**实验结果**：事先go south到lab,然后go east到office,执行back命令

[![5.png](https://i.postimg.cc/tRc6vn6v/5.png)](https://postimg.cc/MXyXvTd1)

第一次执行back命令返回lab,第二次执行Back命令回到outside,再次执行back提示已经在初始房间。



## **2.4 功能扩充点四**

**在游戏中增加具有传输功能的房间，每当玩家进入这个房间，就会被随机地传输到另一个房间；**

要实现一个传送房间，其中玩家进入房间后会被随机传送到任何一个房间，可以通过以下步骤来完成：

实现步骤：

**房间列表**：游戏中需要有一个房间集合，包含所有可用的房间。

**随机选择房间**：在玩家进入传送房间时，随机从所有房间中选择一个房间进行传送。

**修改游戏逻辑**：修改 `Game` 类，每次进入一个房间时判断是否是传送房间（GoRoom,enterRoom（传送）,back时都要判断，enterRoom同时也要记录在历史房间里）。

具体实现：

步骤 1: 扩展 `Game` 类，维护一个房间列表

我们需要修改 `Game` 类，使其能够维护一个所有房间的列表。然后，当玩家进入传送房间时，我们将从这个房间列表中随机选择一个房间。

[![25.png](https://i.postimg.cc/9fBX6KnF/25.png)](https://postimg.cc/yJkz9QKw)

步骤 2: 扩展 `Room` 类，支持传送功能

我们在 `TeleportRoom` 类中实现 `teleportPlayer` 方法，通过随机选择一个房间来传送玩家。

[![26.png](https://i.postimg.cc/6356tckV/26.png)](https://postimg.cc/HJR1twsj)

利用random函数从所有房间中随机选择一个房间，若选择的房间是当前房间则重新选择，随后调用enterroom函数传送玩家。

步骤3;传送函数的设计以及房间类型检查函数的设计

[![27.png](https://i.postimg.cc/xCxfCHQw/27.png)](https://postimg.cc/34G5fkd1)

CheckRoom设计：利用instanceof来判断当前房间类型是否是TeleportRoom，若是调用teleportRoom中的方法teleportPlayer方法传送玩家。

EnterRoom设计：直接让当前房间为指定的房间，实现传送，并再次调用checkRoom函数检查是否是传送房间。

**同时，对GoRoom函数和back函数进行更新，加上CheckRoom函数来判断是否是传送房间，若是传送房间则传送。**



**实验结果：事先在Outside北面设置传送房间**

[![9.png](https://i.postimg.cc/PxxL2d5k/9.png)](https://postimg.cc/WDBb4LZ9)

**检验传送房间效果：**

[![10.png](https://i.postimg.cc/tTMsc8sn/10.png)](https://postimg.cc/TLn2L7qT)

**如上图所示，首先执行命令go north往北走，输出提示，传送玩家，被传送至lab,执行back命令返回传送房间，再次被随机传送，传送至theater。**



## **2.5 功能扩充点五**

1.  **在游戏中新建一个独立的Player类用来表示玩家，并实现下列功能需求：**

    *   **一个玩家对象应该保存玩家的姓名等基本信息，也应该保存玩家当前所在的房间；**

[![28.png](https://i.postimg.cc/cCvs8H4r/28.png)](https://postimg.cc/sGRFk3Wr)
[![12.png](https://i.postimg.cc/t70YqPtX/12.png)](https://postimg.cc/vxzQX4Nj)
[![29.png](https://i.postimg.cc/L5Gmkpnv/29.png)](https://postimg.cc/GTJ0r6Ps)

 *   **玩家可以随身携带任意数量的物件，但随身物品的总重量不能操过某个上限值；**
    Cancarry函数用来判断玩家载重是否小于最大负重
    Takeitem函数用来增加物品的重量至玩家载重上。Dropitem函数用来丢掉身上的物品。


2.

 *   **在游戏中增加两个新的命令“take”和“drop”，使得玩家可以拾取房间内的指定物品或丢弃身上携带的某件或全部物品，当拾取新的物件时超过了玩家可携带的重量上限，系统应给出提示；**

[![19.png](https://i.postimg.cc/J4JQb5F5/19.png)](https://postimg.cc/nCF7xBpX)
[![20.png](https://i.postimg.cc/JzL5KBVV/20.png)](https://postimg.cc/xc6m181t)


   Take命令的实现：如果有第二个命令，则调用Room类中的getitem方法根据第二个命令找到对应物品，然后调用player中的takeitem函数拾起该物品，当前房间则去掉该物品。
   Drop函数的实现：同take理，调用玩家类的getinventory找到身上指定的物品，然后调用player中的dropitem函数丢弃该物品，该房间则增加对应物品。





*   **在游戏中增加一个新的命令“items”, 可以打印出当前房间内所有的物件及总重量，以及玩家随身携带的所有物件及总重量；**

   [![32.png](https://i.postimg.cc/dtTssLxf/32.png)](https://postimg.cc/dLwPntvR)

*   **在某个或某些房间中随机增加一个magic cookie（魔法饼干）物件，并增加一个“eat cookie”命令，如果玩家找到并吃掉魔法饼干，就可以增长玩家的负重能力；**
[![23.png](https://i.postimg.cc/WzZ0ws51/23.png)](https://postimg.cc/dZq7qcMb)


**首先需要判断玩家输入eat cookie命令的合法性，如果第二个单词不是cookie，则输出eat what?提醒玩家，接着查找房间中是否有魔法饼干，若有则调用eatmagiccookie函数。**



**实验结果：如下图所示，计划如下：首先在outside拿去大宝剑，由于玩家负重只有10，所以拿不起大宝剑，接着去pub吃掉魔法饼干，获取10的负重，这时我们的负重变为了20，可以回outside拿起大宝剑。**

[![24.png](https://i.postimg.cc/dt887t7W/24.png)](https://postimg.cc/dLV7pFjd)

[![25.png](https://i.postimg.cc/wjgDD8L9/25.png)](https://postimg.cc/tYv1HcBc)

[![26.png](https://i.postimg.cc/qvwyLbxy/26.png)](https://postimg.cc/qNtNBGYv)

**执行结果**

[![23.png](https://i.postimg.cc/WzZ0ws51/23.png)](https://postimg.cc/dZq7qcMb)

**如上图所示，运行结果与预期完全一致。**





# **3 测试用例以及结果**

## 3.1. `testCreateRooms()`

[![1.png](https://i.postimg.cc/C1B8wFTs/1.png)](https://postimg.cc/BL3bgfvj)

*   **目标**：检查房间是否正确创建，并验证房间之间的出口连接是否正确。
*   **分析**：

    *   从 `game.getAllRooms()` 获取所有房间，然后验证第一个房间（外部房间）和第二个房间（讲堂）之间的出口连接是否正确。
    *   确保房间出口的设置和房间间的连接是有效的。通过 `assertNotNull` 检查房间是否有出口，并通过 `assertEquals` 检查出口指向的房间是否正确。

## 3.2. `testRoomHasItems()`

[![2.png](https://i.postimg.cc/L5jZZNsq/2.png)](https://postimg.cc/1V5zk0wP)

*   **目标**：检查房间是否正确添加了物品。
*   **分析**：

    *   获取外部房间的物品集合 `outside.getItems()`，并验证其是否为空。
    *   `assertTrue(outside.getItems().size() > 0)` 确保房间内有物品。该测试检查物品添加是否成功。

## 3.3. `testGoRoom()`

[![3.png](https://i.postimg.cc/tJGsyWz9/3.png)](https://postimg.cc/xJgf3k7Z)

*   **目标**：验证玩家是否能够成功进入新房间。
*   **分析**：

    *   执行一个 `go` 命令，玩家从当前房间进入新房间。
    *   使用 `assertEquals` 确保当前房间描述符合预期。测试在执行 `go east` 命令后，玩家是否成功进入了“讲堂”房间。

## 3.4. `testBackCommand()`

[![4.png](https://i.postimg.cc/Rh1N0hPK/4.png)](https://postimg.cc/SYsyTSbx)

*   **目标**：测试“back”命令，验证玩家能否返回到上一个房间。
*   **分析**：

    *   玩家先进入新房间（通过 `go east` 命令），然后执行“back”命令，返回到原来的房间。
    *   通过 `assertEquals` 确保玩家正确地返回到“主入口”房间。

## 3.5 `testEatCommand()`

[![5.png](https://i.postimg.cc/ZKZWMPRc/5.png)](https://postimg.cc/yWQ6JZ0g)
[![5-2.png](https://i.postimg.cc/8kLF4X1c/5-2.png)](https://postimg.cc/NLfff42v)

*   **目标**：测试玩家是否可以吃掉魔法饼干并增加负重能力。
*   **分析**：

    *   通过 `go west` 命令进入 Pub 房间，检查房间内是否包含魔法饼干。
    *   玩家通过 `eat cookie` 命令吃掉魔法饼干后，验证饼干是否被移除（使用物品描述比对）。
    *   确认玩家的最大负重能力是否已增加（通过 `assertEquals(20, game.getPlayer().getMaxWeight())`）。

## 3.6. `testLookCommand()`

[![6.png](https://i.postimg.cc/x11c00LN/6.png)](https://postimg.cc/nCNH2fRn)

*   **目标**：测试 `look` 命令的有效性。
*   **分析**：

    *   使用 `look` 命令查看房间，但传入的 `word` 参数为 `null`。此时应该返回 `false`，表示 `look` 已经执行。
    *   确保返回值正确，并且房间描述没有被改变。

## 3.7. `testItemsCommand()`

[![7.png](https://i.postimg.cc/vZ2DTpvq/7.png)](https://postimg.cc/sMS30Hq7)

*   **目标**：测试 `items` 命令，查看房间和玩家携带物品的状态。
*   **分析**：

    *   `items` 命令尝试列出房间内的物品以及玩家携带的物品。由于 `word` 为 `null`，此时应该返回 `false`，表示items命令已经执行。

## 3.8. `testTakeCommand()`

[![8.png](https://i.postimg.cc/hjTGChR6/8.png)](https://postimg.cc/qhB0qJRx)

[![8-2.png](https://i.postimg.cc/NFtjZYgM/8-2.png)](https://postimg.cc/YGX7m5LK)

*   **目标**：测试玩家是否能够从房间中拾取物品。
*   **分析**：

    *   玩家首先进入“pub”房间，通过 `take` 命令拾取物品（如茅台）。
    *   验证物品是否从房间中移除，并加入到玩家的物品栏。
    *   通过 `assertTrue(game.getPlayer().getInventory().contains(maotai))` 确保物品在玩家的物品栏中。
    *   确保玩家的负重正确增加。

## 3.9. `testDropCommand()`

[![9.png](https://i.postimg.cc/h48jTJr7/9.png)](https://postimg.cc/JtnMWzS1)
[![9-2.png](https://i.postimg.cc/TYC3NZBd/9-2.png)](https://postimg.cc/pp5vp124)


*   **目标**：测试玩家是否能够丢弃携带的物品。
*   **分析**：

    *   玩家进入“pub”房间，拾取物品（茅台），然后通过 `drop` 命令将其丢弃。
    *   验证物品从玩家的物品栏中移除，且房间内重新添加物品。
    *   确保玩家的负重更新为 0。

## 3.10` testInvalidCommand()`

[![10.png](https://i.postimg.cc/GmthWX1k/10.png)](https://postimg.cc/Sn0h87Rs)

*   **目标**：验证无效命令的处理。
*   **分析**：

    *   执行无效命令 `fly`，并通过 `assertFalse(result)` 确保系统返回 `false`，表示命令无效。

\*\* \*\*

## 3.11 测试结果

[![222.png](https://i.postimg.cc/N0rGMLFF/222.png)](https://postimg.cc/GBdngLkn)

如上图所示所有测试结果均正确，测试通过了**创建房间、房间是否正确添加物品、是否能成功进入新房间、back命令、eat cookie命令、look命令、items命令、take命令、drop命令、命令合法验证等**

 

#

 

 
