## Instruction set documentation

#### 32bit RISC instruction set inspired by ARM
##### Memory
All memory accesses must be aligned by 4 for simplicity and code saftey
##### Registers
4 GP0~GP3: General purpose registers\
1 PC: Program counter\
1 SP: Stack pointer\
1 BP: Stack base pointer (can also be used as a general purpose register)\
1 CR: Control register, Also includes flags

###### Control register
| Function      |Bit field      | Description   | 0             | 1             |
| -----------   | -----------   | -----------   | -----------   | -----------   |
| Zero flag     | 0             |               | Not zero      | Zero       |
| Negative flag | 1             |               | Not negative  | Negative      |
| Reserved      | 2~7           | 
| Exceptions    |  8~15         | Bitmask for exceptions|
| Reserved      | 16~31         | 

##### Exceptions
| Function                      |Bit field      | Description   |
| -----------                   | -----------   | -----------   |
| EXCEPTION_INVALID_OPCODE      | 0             |
| EXCEPTION_INVALID_OPERAND     | 1             |
| EXCEPTION_DIVISION_BY_ZERO    | 2             |
| EXCEPTION_ALIGNMENT           | 3             | Memory address not aligned by 4
|EXCEPTION_STACK_ALIGNMENT      | 4             | Stack pointer out of bounds / higher than base pointer


Instruction split into 3 sections
| Function      |Bit field |
| -----------   | ----------- |
| opcode        | 0~3      |
| operand 1     | 4~7        |
| operand 2     | 8~11        |
| operand 3     | 12~15        |
| reserved      | 16~31        |