#Tack_4_cpu
   
   
   ### Build
   
       cmake .
       make
   

   
   ### Quick test
   
       cd examples
       ../asm helloworld.lang helloworld.langasm
       ../exec helloworld.langasm
       
       ../disasm helloworld.langasm helloworld-disasmed.lang
       ../asm helloworld-disasmed.lang helloworld-disasmed.langasm
       ../exec helloworld-disasmed.langasm
       
       ../interp helloworld.lang
       ../interp helloworld-disasmed.lang
       
   Should print `Hello, world!` 4 times.
   
   `helloworld.lang` — Hello, world! program <br>
   `helloworld.langasm` - assembled program <br>
   `helloworld-disasm.lang` — disassembled program from `helloworld.langaasm` <br>
   `helloworld-disasm.langasm` — disassembled and reassembled program
   
### Assembler

Assembles the given program into a sequence of bytes.

#### Help

    ./asm help
    ./asm h
    
#### Run

    ./asm <input source filename> <output assembley filename>

### Disassembler

Disassembles the given assembled program into a human-readable program.

#### Help

    ./disasm help
    ./disasm h
    
#### Run

    ./disasm <input assembley filename> <output source filename>

### Executor

Executes the given assembled program.

#### Help

    ./exec help
    ./exec h
    
#### Run

    ./exec <input assembley filename>

### Interpreter

Interprets the given program without creating an assembley file.

#### Help

    ./interp help
    ./interp h
    
#### Run

    ./interp <input source filename>
    
## Language  
    
### Comments

Single-line comments start with a `#`. There're no multi-line comments in lang.

    # I am a comment
    push 1 # I am a comment too

### Stack operations

#### `push`

Pushes the given argument onto stack. The argument can be a positive integer number or a char in single ticks `'`. 
When push is applied to a char, the char's ASCII-code is actually pushed onto the stack.

                # Stack:
    push 15     # [15]
    push 'a'    # [15, 97]

#### `dup`

Duplicates the last element on the stack.

                # Stack:
    push 10     # [10]
    dup         # [10, 10]

### Register operations

Registers allow to store values outside of stack. There're 26 registers from `a` to `z`.

#### `put`

Puts the top element from stack into the given argument register.

                # Stack:        # Register a:
    push 5      # [5]           # -
    put a       # []            # 5

#### `take`

Takes the value from the given argument register and pushes it on top of the stack.

                # Stack         # Register k:
    push 17     # [17]          # -
    put k       # []            # 17
    push 3      # [3]           # 17
    take k      # [3, 17]       # 17

### IO operations

#### `in`

Reads a number from the standart input and pushes it onto stack.

                # Stack:
    in          #
    << 4        # [4]

#### `out`

Prints the last element of the stack and pops it.

                # Stack:
    push 17     # [17]
    out         # []
    >> 17

#### `outchar`

Prints the last element of the stack as the corresponding ASCII-character and pops it.

                # Stack:
    push 'a'    # [97]
    push 65     # [97, 65]
    outchar     # [97]
    >> A
    outchar     # []
    >> a

### Math operations

#### `sqrt`

`sqrt` takes top number from the stack and pushes it's square root onto the stack.

                # Stack:
    push 4      # [4]
    sqrt        # [2]

#### Other math operations

Math operations pop two top numbers from the stack, perform an operation on them and push the result onto the stack.
The top number becomes the rhs and the second number becomes the lhs.

For example:

                # Stack:
    push 16     # [16]
    push 2      # [16, 2]
    divide         # [8]

All math operations:

Let's consider initial stack state to be `[a, b]`.

| Command      | Result |
| ------------ | ------ |
| `add`, `+`   | a + b  |
| `sub`, `-`   | a - b  |
| `mul`, `*`   | a * b  |
| `divide`, `/`| a / b  |
| `power`, `^` | a ^ b  |
| `mod`, `%`   | a % b  |

### Logical operations

The logical value of a number on the stack is `false`, if it is `0` and `true` in any other case.

#### `not`, `!`

Pops the top number from the stack, reverses it's logical value and pushes it back. For `0` the resulting value
will be any non-`0` number and for any non-`0` number it will be `0`.

                # Stack:
    push 16     # [16]
    not         # [0]
    push 0      # [0, 0]
    !           # [0, 1]

#### Other logical operations

All the other logical operations pop two top elements from the stack, perform an operation on them and push the result onto the stack.
The top number becomes the rhs and the second number becomes the lhs.

For example:

                # Stack:
    push 5      # [5]
    push 12     # [5, 12]
    >           # [0]

All logical operations without `not`:

Let's consider initial stack state to be `[a, b]`.

| Command        | Result  |
| -------------- | ------- |
| `less`, `<`    | a < b   |
| `more`, `>`    | a > b   |
| `lesseq`, `<=` | a <= b  |
| `moreeq`, `>=` | a >= b  |
| `eq`, `==`     | a == b  |
| `noteq`, `!=`  | a != b  |

### Control flow

#### `end`

Ends the program.

### Coming soon

- More logical operations: `and`, `or`, etc.
- Marks and `goto <mark>`
- Conditional `goto`
- Multi-file support
- Error reporting

## Examples

### Hello, world!

    push 'H' outchar
    push 'e' outchar
    push 'l' outchar
    push 'l' outchar
    push 'o' outchar
    push ',' outchar
    push ' ' outchar
    push 'w' outchar
    push 'o' outchar
    push 'r' outchar
    push 'l' outchar
    push 'd' outchar
    push '!' outchar
    push '
    ' outchar
    end

### a + b

    push 'a' outchar      # Print 'a b = '
    push ' ' outchar
    push 'b' outchar
    push ' ' outchar
    push '=' outchar
    push ' ' outchar

    in                    # Read a and print it
    dup out
    
    push ' ' outchar      # Print ' + '
    push '+' outchar
    push ' ' outchar

    in                    # Read b and print it
    dup out

    push ' ' outchar      # Print ' = '
    push '=' outchar
    push ' ' outchar

    add                   # Print a + b
    out

    push '
    ' outchar             # Print '\n'

    end                   # End program

### Square equation

    push 'a' outchar      # Print 'a = '
    push ' ' outchar
    push '=' outchar
    push ' ' outchar
    
    in                    # Read a
    put a                 # and put it in {a}
    
    push 'b' outchar      # Print 'b = '
    push ' ' outchar
    push '=' outchar
    push ' ' outchar
    
    in                    # Read b
    put b                 # and put it in {b}
    
    push 'c' outchar      # Print 'c = '
    push ' ' outchar
    push '=' outchar
    push ' ' outchar
    
    in                    # Read c
    put c                 # and put it in {c}
    
    take b                # Calculate discriminant = b^2 - 4*a*c
    take b                # and put it in {d}
    mul
    push 4
    take a
    take c
    mul
    mul
    sub
    put d
    
    push 0                # Calculate first root = (-b + sqrt(d)) / (2*a)
    take b                # and put it in {x}
    sub
    take d
    sqrt
    add
    push 2
    take a
    mul
    div
    put x
    
    push 0                # Calculate first root = (-b - sqrt(d)) / (2*a)
    take b                # and put it in {y}
    sub
    take d
    sqrt
    sub
    push 2
    take a
    mul
    div
    put y
    
    push 'x' outchar      # Print 'x1 = '
    push '1' outchar
    push ' ' outchar
    push '=' outchar
    push ' ' outchar
    
    take x                # Print first root
    out

    push '
    ' outchar             # Print '\n'

    push 'x' outchar      # Print 'x2 = '
    push '2' outchar
    push ' ' outchar
    push '=' outchar
    push ' ' outchar
    
    take y                # Print second root
    out
    
    push '
    ' outchar             # Print '\n'
    
