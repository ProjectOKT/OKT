# **Tutorials for OKT**

## **✅ Information**
- OKT is bignumber operation library.
- Used for Crypto Algorithms.

### **[Features of OKT]**
  
  👍 **Word Size 8, 32, 64bits available!**
  
  👍 **Operate for 2048 bits bigint!**
   
  👍 **Enable RSA-2048 Algorithm!**

  👍 **Generate Prime by Miller-Rabin and Sage code!**

  **➡️You can run RSA_param_gen.py to generate RSA parameters!**
   

## **✅ Environment Details**

| **Attribute**         | **Details**               |
|------------------------|--------------------------|
| **Programming Language** |[![Language: C](https://img.shields.io/badge/Language-C-blue)](https://en.wikipedia.org/wiki/C_(programming_language))|
| **Supported OS**       | [![OS: Mac](https://img.shields.io/badge/OS-MacOS-brightgreen)](https://www.apple.com/macos/), [![OS: Windows](https://img.shields.io/badge/OS-Windows-blue)](https://www.microsoft.com/windows), [![OS: Linux](https://img.shields.io/badge/OS-Linux-yellowgreen)](https://www.linux.org/) |
| **Compiler**           | GCC, Clang               |
| **C versions**         | C99                      |
| **Verify Tools**       | SageMath, Python         |

## **✅ How to Run**
- You can banchmark performance of our bignum algorithm.
- Using makefile or Libmakefile.mk, you can compile.
- **Please check your python installed sympy to run RSA TEST!**
```python
!pip install sympy
```
- Setting on test parameters in test.h and word parameter in params.h  
 ### **➡️ Chose following options to Run**


1. Setting parameters in "test.h"
```c
#define TESTNUM                     10000     //number of test case
#define TESTNUM_modexp              1      //number of test case to modexp

(more test flags)
...
```

2. Setting Word Size in "params.h"
```c
#define SIZEOFWORD  (8 or 32 or 64)

#define KARA_FLAG_SQU   10   //karatsuba word_len flag
#define KARA_FLAG_MUL   10

#define MILLER_NUM      10

#define SECURE_SCA      1    //SCA_SECURE: 1, SCA_UNSECURE: 0
```

3. Make Executable File Directly.
```bash
make              //basic complie
./2024_bigint     //Run   
```

4. Make Dynamic Library and Executable File.
  
   ❗OSDIR is automatically generated with your OS
```bash
make -f Libmakefile.mk    //make directory and files
./(OSDIR)/bigint_app      //Run
```


## **✅ Code Structure**
### **[Source files]**
- **bigintfun.c**
   - Basic functions for bigint operation.
   - header : bigintfun.h
- **arrayfun.c**
   - Array functions for bigint modifying.
   - header : arrayfun.h
- **operation_tool.c**
   - Utility functions for operation(Like Single word or Same sign operation).
   - header : operation_tool.h
- **operation.c**
   - Main operation functions.
   - header : operation.h
- **test.c**
   - Single operation test or compare operation performance.
   - header : test.h
- **verify.c**
   - Memory leakage check.
   - header : verify.h
- **2024_bigint.c**
   - Include main() and run test.
### **[Utility header files]**
 - **dtype.h**
   - Define bigint structure and type of word, return value.
- **errormsg.h**
   - Define Error messages.
- **params.h**
   - Define function parameters and SIZEOFWORD, ZERORIZE.
### **[Make files]**
- makefile
   - Make Run File 2024_bigint
- Libmakefile.mk
   - Make Library file(.so or .dll) and Application file.

## **✅ GitHub**
- You can git clone OKT
```bash
git clone https://github.com/ProjectOKT/OKT.git
```
