# SPL-Compiler
A naive SPL compiler implementation in C++.
## 依赖
  - LLVM 9.0
  
## 编译

```bash
cmake ..
make
```

## 运行

`./splc input.spl`
**splc和system.spl必须在同一目录下**

## 输出

- `output.ll`

LLVM IR。

- `output.s`
      
本机汇编代码。
可以通过 `gcc -no-pie output.s` 生成本机可执行文件。

- `mips.s`

MIPS汇编, target = mips-apple-darwin17.6.0。

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

dependency: graphviz
```bash
dot -Tpng -o ast.png ast.dot
```

3. 代码生成(default target和MIPS)

default target可在本机编译运行，检查正确性。
MIPS为实验要求。

4. 超简单的错误提示。
