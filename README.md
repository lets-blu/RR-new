# RR 外设库

RR 是一个使用 **C 语言**编写，采用**面向对象**设计思想的**跨平台**外设库，专为 Arduino 及兼容平台（如 AVR、ESP8266、ESP32、STM32 等）提供统一、可扩展的硬件驱动抽象层。

## 1. 安装指南

### 1.1 安装

您可以通过以下两种方式将 RR 库安装到 Arduino 开发环境中。

#### 方式一：通过 ZIP 包安装（推荐新手）

1. 访问本库的 GitHub 主页：[https://github.com/lets-blu/RR-new](https://github.com/lets-blu/RR-new)  
2. 点击页面上的 **Code** 按钮，选择 **Download ZIP**，下载压缩包。  
3. 解压下载的 ZIP 文件，并将解压后得到的文件夹**重命名**为 `RR`（去掉可能存在的 `-main` 或 `-master` 后缀）。  
4. 将 `RR` 文件夹移动至 Arduino 的 **libraries** 目录下：  
   - **Windows**：`我的文档\Arduino\libraries\` （例如 `C:\Users\你的用户名\Documents\Arduino\libraries\`）  
   - **Linux**：`~/Arduino/libraries/` （即 `/home/你的用户名/Arduino/libraries/`）  
   > 如果该目录下没有 `libraries` 文件夹，请手动新建一个。

#### 方式二：通过 Git 克隆安装（推荐开发者）

在终端（Terminal）中执行以下命令，进入 Arduino 库目录后克隆本仓库：

```bash
# 进入 Arduino 库目录
cd ~/Arduino/libraries/          # Linux
# cd "C:\Users\你的用户名\Documents\Arduino\libraries\"   # Windows (请在 PowerShell 或 CMD 中执行)

# 克隆仓库
git clone https://github.com/lets-blu/RR-new.git RR
```

### 1.2 验证安装

完成上述任一安装方式后，请**重启 Arduino IDE**。在 IDE 菜单栏中依次点击 **文件 -> 示例**，如果能在下拉列表中看到 **RR** 库的示例程序，则说明安装成功。

![图 1. Arduino IDE示例菜单中显示RR库](extras/images/图%201.%20Arduino%20IDE示例菜单中显示RR库.png "图 1. Arduino IDE示例菜单中显示RR库")

<div style="page-break-before: always;"></div>

## 2. 创建工程

### 2.1 设置核心

在开始使用 RR 库的各项功能之前，首先需要在 `setup()` 函数中完成**核心（Core）**的初始化。核心对象负责库内部的调度、设备管理和事件循环，是所有后续操作的基础。

请将以下代码添加到您的 `setup()` 函数中（放在最前面）：

```cpp
#include <RR.h>   // 请确保包含本库的头文件

static ArduinoCore core;                        // 1. 声明一个静态核心对象（生命周期贯穿整个程序）
ArduinoCore_Construct(&core);                   // 2. 调用构造方法，初始化核心内部资源
DeviceManager_SetCore(DeviceManager_GetInstance(), &core.base); // 3. 将核心实例注册到设备管理器中
```

**代码说明**：
- **`static` 修饰符**：保证核心对象在程序运行期间只被构造一次，即使在软复位（如重置 Arduino）时也不会重复创建，有效避免栈溢出或内存碎片。
- **`ArduinoCore_Construct`**：执行核心底层硬件的绑定与内部状态复位，必须在使用任何其他库接口之前调用。
- **`DeviceManager_SetCore`**：将初始化好的核心交给设备管理器统一管理，使后续的设备注册、回调分发等机制能够正常工作。

> ⚠️ **注意**：请确保上述代码放在 `setup()` 函数的**最前面**，且在调用任何 RR 库的其他 API（如设备读写、事件绑定等）之前执行。

**在 `loop()` 中驱动任务入口（裸机环境必须添加）**

如果您的项目未使用实时操作系统（RTOS），请务必将设备管理器的任务入口添加到 `loop()` 函数中，以驱动库内部的状态机、事件回调与数据收发。建议放在 `loop()` 的最开头：

```cpp
DeviceManager_TaskEntry(DeviceManager_GetInstance());
```

> 💡 若项目使用 RTOS，此任务由操作系统自动调度，无需手动添加。

### 2.2 设置系统（可选）

在核心（Core）完成初始化后，您可以根据项目需要向库挂载一个**系统（System）**实例。`NoneSystem` 是一个空系统实现，不依赖任何实时操作系统，适用于裸机轮询场景；若未来需要多任务调度，可替换为其他系统组件。

将以下代码添加到 `setup()` 函数中（通常放在核心初始化之后）：

```cpp
static NoneSystem sys;                         // 1. 声明一个静态 NoneSystem 对象（生命周期贯穿整个程序）
NoneSystem_Construct(&sys);                    // 2. 构造该系统对象
DeviceManager_SetSystem(DeviceManager_GetInstance(), &sys.base); // 3. 将系统注册到设备管理器
```

**代码说明**：
- **`static` 修饰符**：与核心对象同理，确保 `sys` 对象在程序运行期间只被构造一次，避免重复构造带来的内存问题。
- **`NoneSystem` 的用途**：提供轻量运行环境，为后续扩展保留统一接口。

> 💡 **提示**：此节可选，若挂载系统，无需额外操作，轮询由 2.1 中的入口统一处理。

### 2.3 初始化日志记录器（可选）

为方便调试，RR 库提供了日志输出功能。您可以通过**日志记录器（Logger）**将库内部的调试信息、错误警告等发送到指定的串行端口。

在核心初始化完成后，您可以在 `setup()` 函数中（或单独封装为一个函数）创建串行端口实例并挂载到日志记录器上。推荐的实现方式如下：

```cpp
void initLogger(void)
{
    // 1. 配置 Arduino 串行端口参数
    ArduinoSerialParameter parameter = {
        .base = ARDUINO_SERIAL_PARAMETER_BASE,
        .serial = &Serial,                      // 使用硬件 Serial（默认串口）
        .baudrate = 115200,                    // 波特率，可根据需要调整
        .rxBuffer = NULL,                      // 不使用接收缓冲区（仅输出）
        .rxBufferSize = 0,                     // 接收缓冲区大小为 0
    };

    // 2. 通过设备工厂创建串行设备实例
    BaseSerial *serial = DeviceFactory_CreateSerial(
        DeviceFactory_GetInstance(),
        ARDUINO_CORE_UART_SERIAL,
        &parameter.base);

    // 3. 将创建好的串行实例设置给日志记录器
    Logger_SetSerial(serial);
}
```

然后，在您的 `setup()` 函数中调用 `initLogger();`（建议放在核心初始化之后、其他业务代码之前）。

**代码说明**：
- **`ArduinoSerialParameter`**：封装了 Arduino 平台串口所需的全部配置信息。本例仅用于输出，故接收缓冲区设为 0。
- **`DeviceFactory_CreateSerial`**：通过工厂模式创建串行设备对象，返回抽象指针，便于跨平台适配。
- **`Logger_SetSerial`**：将串行设备绑定到全局日志记录器。此后，库内部调用 `LOGGER_I`、`LOGGER_E` 等宏时，会自动将信息通过此串口输出。

> 💡 **提示**：此节可选。如需启用日志，请确保在可能产生日志的任何库 API 调用**之前**完成初始化。若不需要，可直接跳过。

<div style="page-break-before: always;"></div>

## 3. 使用示例

本章将逐一介绍 RR 库中各模块的基本用法，每个小节均提供一个包含在库中的完整示例供参考。

### 3.1 发光二极管

发光二极管模块用于控制单个 GPIO 引脚上的发光二极管（或任何数字输出设备）的亮灭状态。您可以通过指定引脚编号和有效电平来快速创建发光二极管对象。

#### 模块说明

使用发光二极管模块只需三个步骤：

1. **构造发光二极管对象**：声明一个 `LED` 结构体实例，并通过 `LED_Construct` 指定引脚、端口和亮起逻辑电平。
2. **点亮发光二极管**：调用 `LED_TurnOn` 使引脚输出有效电平。
3. **熄灭发光二极管**：调用 `LED_TurnOff` 使引脚输出无效电平。

#### 关键代码片段

以下是一个典型的使用示例（省略了核心与系统的初始化，完整代码请见下方示例路径）：

```cpp
#include <RR.h>

// 声明 LED 对象
LED led;

void setup() {
    // ... 核心初始化（见第二章） ...

    // 构造发光二极管实例
    // 参数说明：端口(NULL表示使用Arduino原生引脚编号)，引脚号(LED_BUILTIN)，有效电平(高电平点亮)
    LED_Construct(&led, NULL, LED_BUILTIN, BASE_PORT_VALUE_HIGH);
}

void loop() {
    LED_TurnOn(&led);    // 点亮发光二极管
    delay(1000);
    LED_TurnOff(&led);   // 熄灭发光二极管
    delay(1000);
}
```

**参数说明**：
- **端口（Port）**：当核心设置为 `ArduinoCore` 时，若引脚直接使用 Arduino 板上的数字引脚编号（如 `LED_BUILTIN`、`D13` 等），端口参数传入 `NULL` 即可。仅在需要操作特定 GPIO 端口寄存器时（如使用非 Arduino 原生编号）才需指定具体端口对象。
- **引脚（Pin）**：Arduino 平台上的数字引脚编号，可以使用 `LED_BUILTIN` 板载发光二极管进行快速测试。
- **有效电平（Value）**：`BASE_PORT_VALUE_HIGH` 表示输出高电平时发光二极管点亮；若为低电平点亮则传入 `BASE_PORT_VALUE_LOW`。

#### 完整示例

库中提供了完整的 Blink 示例（闪烁发光二极管），可直接在 Arduino IDE 中打开运行：

**路径**：`examples/Blink/Blink.ino`

打开方式：在 Arduino IDE 中点击 **文件 → 示例 → RR → Blink**。

### 3.2 数字按键

数字按键模块用于检测 GPIO 引脚上按键（或开关）的按下与释放事件。您可以通过指定引脚编号和有效电平来创建按键对象，并为其绑定事件处理函数。当按键被按下时，库会自动调用您设置的事件处理程序。

#### 模块说明

使用数字按键模块只需四个步骤：

1. **构造按键对象**：声明一个 `DigitalButton` 结构体实例，并通过 `DigitalButton_Construct` 指定引脚、端口和有效电平。
2. **编写事件处理函数**：定义一个符合 `void functionName(void *sender, EventArgs *args)` 签名的回调函数。
3. **绑定事件处理函数**：调用 `DigitalButton_SetEventHandler` 将您编写的处理函数注册到按键对象上。
4. **使能扫描**：调用 `DigitalButton_EnableSample` 启用按键扫描功能，之后库会在后台自动检测按键状态变化。

#### 关键代码片段

以下是一个典型的使用示例（省略了核心与系统的初始化，完整代码请见下方示例路径）：

```cpp
#include <RR.h>

// 声明数字按键对象
DigitalButton button;

// 按键事件处理函数
void eventHandler(void *sender, EventArgs *args)
{
    // 当按键被按下时，此函数会被自动调用
    // 可在此处添加按键响应逻辑，例如点亮发光二极管或发送串口消息
}

void setup() {
    // ... 核心初始化（见第二章） ...

    // 构造数字按键实例
    // 参数说明：端口(NULL表示使用Arduino原生引脚编号)，引脚号(2)，有效电平(低电平表示按键按下)
    DigitalButton_Construct(&button, NULL, 2, BASE_PORT_VALUE_LOW);

    // 绑定事件处理函数
    DigitalButton_SetEventHandler(&button, eventHandler);

    // 使能按键扫描（true 表示开启扫描）
    DigitalButton_EnableSample(&button, true);
}

void loop() {
    // 按键扫描依赖 2.1 节中添加的 DeviceManager_TaskEntry 驱动
    // 请确保 loop() 中已包含该调用，否则事件不会被触发
    DeviceManager_TaskEntry(DeviceManager_GetInstance());
}
```

**参数说明**：
- **端口（Port）**：当核心设置为 `ArduinoCore` 时，若引脚直接使用 Arduino 板上的数字引脚编号（如 `2`、`D3` 等），端口参数传入 `NULL` 即可。
- **引脚（Pin）**：Arduino 平台上的数字引脚编号，例如外接按键的信号引脚。
- **有效电平（Value）**：`BASE_PORT_VALUE_LOW` 表示低电平时视为按键按下（常见于按键一端接 GND 的电路）；若为高电平有效则传入 `BASE_PORT_VALUE_HIGH`。

> 💡 **提示**：按键的检测依赖库内部的扫描轮询机制，因此请务必在 `loop()` 中保留 2.1 节提到的 `DeviceManager_TaskEntry` 调用。

#### 完整示例

库中提供了完整的数字按键示例，可直接在 Arduino IDE 中打开运行：

**路径**：`examples/DigitalButton/DigitalButton.ino`

打开方式：在 Arduino IDE 中点击 **文件 → 示例 → RR → DigitalButton**。

### 3.3 日志记录器

日志记录器模块用于在程序运行期间输出调试信息、状态提示或错误报告。按照 2.3 节的方法完成串行端口初始化后，您可以通过简单的宏来创建日志记录器实例，并在代码中的任意位置输出格式化日志信息。

#### 模块说明

使用日志记录器模块只需以下几个步骤：

1. **创建日志实例**：使用 `LOGGER_STATIC` 宏声明一个静态日志记录器实例，并为其指定模块名称和允许输出的最低日志等级。
2. **注册日志实例（可选）**：调用 `Logger_Register` 将该实例注册到系统中，以便框架进行统一管理。
3. **输出日志信息**：在代码中使用 `LOGGER_I`、`LOGGER_E` 等宏输出不同等级的日志内容。

#### 关键代码片段

以下是一个典型的使用示例（省略了核心与系统的初始化，完整代码请见下方示例路径）：

```cpp
#include <RR.h>

// 创建日志记录器实例
// 参数说明：模块名称("Main")，最低日志等级(LOGGER_LEVEL_INFO)
Logger logger = LOGGER_STATIC("Main", LOGGER_LEVEL_INFO);

void setup() {
    // ... 核心初始化（见第二章） ...
    // ... 2.3 节中串行端口及日志记录器的初始化 ...

    // 注册日志实例（可选），以便框架统一管理
    Logger_Register(&logger);

    // 输出一条信息级日志
    LOGGER_I(&logger, "System initialized successfully!");

    // 如果发生错误，可输出错误级日志
    // LOGGER_E(&logger, "An error occurred!");
}

void loop() {
    // 输出周期性日志
    LOGGER_I(&logger, "Hello, world!");

    delay(1000);
}
```

**参数说明**：
- **模块名称（Module Name）**：用于标识日志来源的字符串，方便在串口输出中区分不同模块的日志信息。
- **日志等级（Log Level）**：控制哪些级别的日志会被输出。可选的等级包括：
  - `LOGGER_LEVEL_DEBUG`：调试信息（最详细）
  - `LOGGER_LEVEL_INFO`：常规信息（默认）
  - `LOGGER_LEVEL_WARN`：警告信息
  - `LOGGER_LEVEL_ERROR`：错误信息（最简）
  
  只有等级**不低于**设定等级的日志才会被输出。例如设为 `LOGGER_LEVEL_INFO` 时，`LOGGER_I`、`LOGGER_W`、`LOGGER_E` 均会输出，而 `LOGGER_D`（调试）则被过滤。

- **`Logger_Register`（可选）**：注册后，框架可在运行时根据需要调整该模块的日志等级。若不注册，日志等级将固定为创建时指定的值。

> 💡 **提示**：使用日志记录器之前，请确保已按照 2.3 节完成了串行端口初始化（即调用 `initLogger()` 并将串行设备绑定到日志记录器）。否则，日志信息将无处输出，调用 `LOGGER_I` 等宏不会有任何效果。

#### 完整示例

库中提供了完整的日志记录器示例，可直接在 Arduino IDE 中打开运行：

**路径**：`examples/Logger/Logger.ino`

打开方式：在 Arduino IDE 中点击 **文件 → 示例 → RR → Logger**。

### 3.4 AT 命令

AT 命令模块用于通过串行端口接收并解析用户发送的 AT 指令，从而在运行时动态控制设备或查询状态。您需要创建一个带有接收缓冲区的串行端口实例，并将其绑定到 AT 命令管理器，然后定义自己的 AT 命令及其回调处理函数。当串行端口收到匹配的 AT 命令时，您预先绑定的处理程序会被自动调用。

#### 模块说明

使用 AT 命令模块只需以下几个步骤：

1. **配置串行端口（带接收缓冲区）**：与 2.3 节不同的是，此处需要为串行端口分配接收缓冲区，以便能够接收并解析用户输入的 AT 指令。
2. **绑定串行端口到 AT 管理器**：调用 `ATCommand_SetSerial` 将创建好的串行实例设置给 AT 命令模块。
3. **构造 AT 命令实例**：声明一个 `ATCommand` 对象，并通过 `ATCommand_Construct` 指定命令字符串（如 `"+TEST"`）和对应的处理函数。
4. **编写事件处理函数**：定义符合 `void functionName(void *sender, EventArgs *args)` 签名的回调函数，当该 AT 命令被触发时自动执行。

#### 关键代码片段

以下是一个典型的使用示例（省略了核心与系统的初始化，完整代码请见下方示例路径）：

```cpp
#include <RR.h>

// 定义接收缓冲区大小和缓冲区数组
#define BUFFER_SIZE 80U
static uint8_t buffer[BUFFER_SIZE];

// 声明 AT 命令对象
ATCommand command;

// AT 命令事件处理函数
void commandHandler(void *sender, EventArgs *args)
{
    // 当串行端口收到 "+TEST" 命令时，此函数会被自动调用
    // 可在此处添加命令响应逻辑，例如返回设备状态或执行特定操作
}

void setup() {
    // ... 核心初始化（见第二章） ...

    // 1. 配置串行端口参数（带接收缓冲区）
    ArduinoSerialParameter parameter = {
        .base = ARDUINO_SERIAL_PARAMETER_BASE,
        .serial = &Serial,                // 使用硬件 Serial（默认串口）
        .baudrate = 115200,               // 波特率，需与串口终端匹配
        .rxBuffer = buffer,               // 指定接收缓冲区
        .rxBufferSize = BUFFER_SIZE,      // 接收缓冲区大小
    };

    // 2. 通过设备工厂创建串行设备实例
    BaseSerial *serial = DeviceFactory_CreateSerial(
        DeviceManager_GetInstance(),
        ARDUINO_CORE_UART_SERIAL,
        &parameter.base);

    // 3. 将串行实例设置给 AT 命令管理器
    ATCommand_SetSerial(serial);

    // 4. 构造 AT 命令实例并绑定事件处理函数
    //    参数说明：命令字符串("+TEST")，事件处理函数(commandHandler)
    ATCommand_Construct(&command, "+TEST", commandHandler);
}

void loop() {
    // AT 命令解析依赖 2.1 节中添加的 DeviceManager_TaskEntry 驱动
    // 请确保 loop() 中已包含该调用，否则命令不会被处理
    DeviceManager_TaskEntry(DeviceManager_GetInstance());
}
```

**参数说明**：
- **接收缓冲区（rxBuffer / rxBufferSize）**：与 2.3 节的不同之处在于，此处必须指定有效的接收缓冲区，且大小应足以容纳预期的 AT 命令字符串。库通过该缓冲区接收串口数据，并在内部进行命令解析。
- **命令字符串（Command String）**：AT 命令的标识符，例如 `"+TEST"`。用户在串口终端中输入 `AT+TEST` 时，对应的处理函数即被触发。命令字符串不需要包含 `"AT"` 前缀，仅需提供命令名称部分。
- **事件处理函数（Event Handler）**：当匹配的命令被识别时调用的回调函数。您可以在其中实现状态查询、参数配置或设备控制等逻辑。

> 💡 **提示**：AT 命令的解析同样依赖库内部的轮询机制，因此请务必在 `loop()` 中保留 2.1 节提到的 `DeviceManager_TaskEntry` 调用，否则命令将无法被识别和处理。

#### 完整示例

库中提供了完整的 AT 命令示例，可直接在 Arduino IDE 中打开运行：

**路径**：`examples/ATCommand/ATCommand.ino`

打开方式：在 Arduino IDE 中点击 **文件 → 示例 → RR → ATCommand**。

### 3.5 移位寄存器

移位寄存器模块用于通过少数几个 GPIO 引脚扩展出更多的数字输出端口，适用于驱动多路 LED、数码管或继电器等场景。您只需指定数据引脚（SER）、时钟引脚（SCK）和锁存引脚（RCK），即可通过软件方式控制多个输出位。多个移位寄存器还可以级联使用，实现更多路输出。

#### 模块说明

使用移位寄存器模块只需以下几个步骤：

1. **创建寄存器与寄存器组实例**：分别声明 `ShiftRegister` 和 `RegisterGroup` 对象。
2. **配置寄存器组参数**：通过 `RegisterGroupParameter` 指定数据引脚、时钟引脚、锁存引脚以及端口（使用 Arduino 原生引脚编号时设为 `NULL`）。
3. **构造对象**：调用 `ShiftRegister_Construct` 和 `RegisterGroup_Construct` 完成初始化。
4. **将寄存器添加到寄存器组**：一个寄存器组可以包含多个级联的寄存器，通过 `RegisterGroup_AddRegister` 按顺序添加。
5. **控制输出**：使用 `RegisterGroup_SetBit` 将指定位设为高电平，或使用 `RegisterGroup_ResetBit` 将指定位设为低电平。

#### 关键代码片段

以下是一个典型的使用示例（省略了核心与系统的初始化，完整代码请见下方示例路径）：

```cpp
#include <RR.h>

// 声明移位寄存器及其寄存器组
ShiftRegister reg;
RegisterGroup group;

void setup() {
    // ... 核心初始化（见第二章） ...

    // 1. 配置寄存器组参数
    RegisterGroupParameter parameter = {
        .port = NULL,      // 使用 Arduino 原生引脚编号
        .serPin = 2,       // 数据引脚（SER）
        .sckPin = 3,       // 时钟引脚（SCK）
        .rckPin = 4,       // 锁存引脚（RCK）
    };

    // 2. 构造移位寄存器和寄存器组
    ShiftRegister_Construct(&reg);
    RegisterGroup_Construct(&group, &parameter);

    // 3. 将寄存器添加到寄存器组中
    //    如需级联多个寄存器，可多次调用本函数按顺序添加
    RegisterGroup_AddRegister(&group, &reg);

    // 4. 控制输出位
    RegisterGroup_SetBit(&group, 0);     // 将第 0 位设为高电平
    // RegisterGroup_ResetBit(&group, 0);   // 将第 0 位设为低电平
}

void loop() {
    // 可在此处添加周期性控制逻辑
}
```

**更多用法：作为组件使用**

您也可以将寄存器组作为组件添加到设备管理器中，使其作为通用 GPIO 模块供其他模块使用。例如，构建发光二极管实例时可直接将寄存器组作为端口参数传入：

```cpp
// 将寄存器组添加到设备管理器
DeviceManager_AddComponent(DeviceManager_GetInstance(), &group.base);

// 将寄存器组的第 0 位作为 GPIO 端口来构造发光二极管
LED led;
LED_Construct(&led, &group, 0, BASE_PORT_VALUE_HIGH);
```

**参数说明**：
- **端口（Port）**：使用 Arduino 原生引脚编号时传入 `NULL`。
- **SER 引脚（serPin）**：串行数据输入引脚，用于逐位送入数据。
- **SCK 引脚（sckPin）**：串行时钟引脚，每个上升沿将 SER 引脚上的数据移入寄存器。
- **RCK 引脚（rckPin）**：锁存时钟引脚，上升沿时将移位寄存器中的数据锁存到输出端。
- **级联扩展**：当需要更多输出位时，可将多个 `ShiftRegister` 实例按顺序添加到同一个 `RegisterGroup` 中，第一个添加的寄存器对应低地址位。添加数量不受限制（取决于级联芯片的数量）。

#### 完整示例

库中提供了完整的移位寄存器示例，可直接在 Arduino IDE 中打开运行：

**路径**：`examples/ShiftRegister/ShiftRegister.ino`

打开方式：在 Arduino IDE 中点击 **文件 → 示例 → RR → ShiftRegister**。

### 3.6 数据选择器

数据选择器模块用于通过多个地址引脚扩展出更多的数字输入端口，适用于读取多路按键、开关或传感器信号等场景。与移位寄存器不同，数据选择器属于单向输入设备：您指定一组地址引脚（通常占用连续的多个 GPIO）来选通不同的输入通道，然后读取该通道上的电平状态。多个数据选择器还可以级联使用，实现更多路输入。

#### 模块说明

使用数据选择器模块只需以下几个步骤：

1. **创建选择器与选择器组实例**：分别声明 `DataSelector` 和 `SelectorGroup` 对象。
2. **构造数据选择器**：调用 `DataSelector_Construct` 指定该选择器能够寻址的地址区间（起始地址与结束地址）。
3. **配置选择器组参数**：调用 `SelectorGroup_Construct` 时，需要指定具体的 GPIO 端口以及地址引脚和数据引脚的位掩码。地址引脚要求使用同一端口内的连续高位引脚，以二进制组合方式选通不同的输入通道。
4. **将选择器添加到选择器组**：一个选择器组可以包含多个级联的选择器，通过 `SelectorGroup_AddSelector` 按顺序添加。
5. **读取输入数据**：使用 `SelectorGroup_GetBit` 传入目标地址，即可读取该地址对应通道的电平状态。

#### 关键代码片段

以下是一个典型的使用示例（省略了核心与系统的初始化，完整代码请见下方示例路径）：

```cpp
#include <RR.h>

// 声明数据选择器及其选择器组
DataSelector selector;
SelectorGroup group;

void setup() {
    // ... 核心初始化（见第二章） ...

    // 1. 构造数据选择器，指定地址范围
    //    参数说明：起始地址 0x00，结束地址 0x07（即 8 个通道）
    DataSelector_Construct(&selector, 0x00, 0x07);

    // 2. 配置选择器组参数
    //    参数说明：端口(PORTD)，地址引脚掩码(0xF0)，数据引脚掩码(0x04)
    //    地址引脚掩码 0xF0 表示使用 PD4、PD5、PD6、PD7 作为地址位
    //    三个地址位（PD4~PD6）组合可产生 8 种地址，对应 8 个输入通道
    //    地址位中的最高位 PD7 用于级联扩展（本文示例未使用）
    //    数据引脚掩码 0x04 表示 PD2 为数据引脚，用于读取当前选中通道的电平
    SelectorGroup_Construct(&group, (void *)PORTD, 0xF0, 0x04);

    // 3. 将选择器添加到选择器组中
    //    如需级联多个选择器，可多次调用本函数按顺序添加
    SelectorGroup_AddSelector(&group, &selector);

    // 4. 读取指定地址的输入数据
    unsigned int value = SelectorGroup_GetBit(&group, 0x00);   // 读取地址 0x00 的电平
    // unsigned int value = SelectorGroup_GetBit(&group, 0x07);   // 读取地址 0x07 的电平
}

void loop() {
    // 可在此处添加周期性读取逻辑
}
```

**更多用法：作为组件使用**

您也可以将选择器组作为组件添加到设备管理器中，使其作为通用 GPIO 模块供其他模块使用。例如，构建数字按键实例时可直接将选择器组作为端口参数传入：

```cpp
// 将选择器组添加到设备管理器
DeviceManager_AddComponent(DeviceManager_GetInstance(), &group.base);

// 将选择器组的地址 0x00 作为 GPIO 端口来构造数字按键
DigitalButton button;
DigitalButton_Construct(&button, &group, 0x00, BASE_PORT_VALUE_LOW);
```

**参数说明**：
- **地址区间（Address Range）**：`DataSelector_Construct` 中的 `startAddress` 和 `endAddress` 定义了该选择器可寻址的地址范围。实际可用的通道数为 `endAddress - startAddress + 1`。
- **GPIO 端口（Port）**：此处必须传入具体的端口寄存器地址（如 `PORTD`），因为地址引脚需要操作连续的高位引脚。使用 `PORTD` 而非 `NULL`。
- **地址引脚掩码（Address Mask）**：指定端口内哪些引脚用作地址位。掩码中置 1 的位即为地址引脚。例如 `0xF0` 表示 `PD4`、`PD5`、`PD6`、`PD7` 为地址引脚。请注意，地址位的数量决定了可寻址通道数：3 个地址位可寻址 8 个通道（0~7），4 个地址位则可寻址 16 个通道（0~15）。
- **数据引脚掩码（Data Pin Mask）**：指定端口内用于读取当前选中通道电平的引脚。虽然通常只使用一个引脚，但参数本身为掩码形式，掩码中置 1 的位即为数据引脚。例如 `0x04` 表示 `PD2` 为数据引脚。
- **级联扩展**：当需要更多输入通道时，可将多个 `DataSelector` 实例按顺序添加到同一个 `SelectorGroup` 中。级联时，地址位中的最高位被用作片选信号，其余低位用于通道选择。

#### 完整示例

库中提供了完整的数据选择器示例，可直接在 Arduino IDE 中打开运行：

**路径**：`examples/DataSelector/DataSelector.ino`

打开方式：在 Arduino IDE 中点击 **文件 → 示例 → RR → DataSelector**。
