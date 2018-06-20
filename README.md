## Polly Scop Profiler Runtime

This projects implements functions for gathering information of LLVM-Polly SCoPs during code execution. Runtime callbacks are inserted during code compilation.

More infomation about LLVM-Polly you can find [here](https://polly.llvm.org/).

## Configuration

Runtime callbacks implicitly assume that sqlite3 database is created. You can create database in default directory by typing:

''python3 CreateDatabaseScript.py''
