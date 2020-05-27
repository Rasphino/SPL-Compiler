# SPL-Compiler
A naive SPL compiler implementation in C++.
## 依赖
  - LLVM 9.0
  - C++ 17 standard
  
## 编译

```bash
cmake ..
make
```

## 运行

`./splc input.spl`

## 输出

- `output.ll`

LLVM IR。

- `output.s`
      
本机汇编代码。
可以通过 `gcc -no-pie output.s` 生成本机可执行文件。

- `aarch64.s`

aarch64汇编, target = aarch64-pc-linux。可以通过 `aarch64-linux-gnu-gcc -no-pie -static aarch64.s` 编译，使用 `qemu-aarch64 ./a.out` 运行。

- `ast.json`

AST节点信息，用于`visualize.html` 可视化

## Checklist
- [x] 数组 一维
- [x] record实现
- [x] 常量不可被重新赋值
- [x] 类型检查
- [x] 函数调用
- [x] 乘除
- [x] 加减区分 real integer
- [x] var: call by reference
- [x] write, writeln
- [x] read
- [ ] 变量自动赋初值
- [x] Factor: T_NOT_FACTOR T_MINUS_FACTOR
- [x] 倒序访问是否有问题
- [x] 主程序返回值

## 功能

1. SPL基本语法
2. 可视化AST

open visualize.html

3. 代码生成(default target和MIPS)

default target可在本机编译运行，检查正确性。
aarch64为扩展实现。

4. 超简单的错误提示。
