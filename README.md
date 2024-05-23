# NIS2336
Assignment.

## llvm配置
环境：ubuntu22.04
内存空间:20.8G
分配硬盘空间:200G（包括根目录，swap缓冲区）
实际使用硬盘空间: 135G-140G

## 编译过程：
- 获取源码
  - `wget https://github.com/llvm/llvm-project/archive/llvmorg-11.1.0.tar.gz`(可能需要一点魔法上网x）
- 解压
  - `tar -xf llvmorg-11.1.0.tar.gz`
- 创建make文件，这里用ninja交叉编译，需要先`sudo apt install ninja-build`
  - `cd llvm-project-llvmorg-11.1.0`
  - `mkdir build`
  - `cd build`
  - `cmake ../llvm -G Ninja -DLLVM_BUILD_LLVM_DYLIB=Yes -DLLVM_REQUIRES_RTTI=YES -DCMAKE_INSTALL_PREFIX=$install_path$ -DLLVM_ENABLE_PROJECTS="clang;libcxx;libcxxabi"`，这里`$install_path$`为install路径。如果内存爆炸（后续make时遇见比如终端卡死无反应，内存达到分配100%时），可以添加编译选项`-DLLVM_PARALLEL_LINK_JOBS=1`（也可以尝试修改数量）,但是会增加编译时长
- 编译
  - `ninja`
  - `ninja install`
- 测试成功
  - `export PATH="$PATH:$install_path$/bin"`
  - `clang -v`（这里编译生成clang）
  - 若输出版本，则编译成功

## 遇到问题
- 在`ninja`编译过程还是cmake过程（忘了）可能遇到undefined reference，此时在源文件中增加include path即可解决报错。（印象里某文件没include \<limits\>）

## 参考
<https://getting-started-with-llvm-core-libraries-zh-cn.readthedocs.io/zh-cn/latest/index.html>
