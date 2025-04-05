| Error type | Error ID | Encountering | Fix | Thrown from |
|----------------------------------------------------------|
| Language | LNG001 | `errorc;` | Add a integer or variable to the end e.g. `errorc 2;`| parser.hpp (Parser) |
| Language | LNG002 | `value {int} = 69;` | Add a variable name e.g. `value i {int} = 69;` | parser.hpp (Parser) |
| Language | LNG003 | `value whyAmIEditingMarkdowns char = 88;` | Wrap the variable type with curly brackets. | parser.hpp (Parser) |
| Language | LNG004 | `value iShouldWriteCode {int = 0;` | Add the closing bracket or place it in the right place | parser.hpp (Parser) |
| Language | LNG005 | `value j;` | Initialize the variable | parser.hpp (Parser) |
| Language | LNG006 | `errorc 6` | Add a semicolon at the end. | parser.hpp (Parser) |
| Language | LNG007 | `value example {} = 3;` |  | parser.hpp (Parser) |
| Language | LNG008 | `gjfvnjvfnfj;` (assuming this is not defined) | Remove the line, check for typos or any case-mixups, or define the variable. | lexer.hpp (Lexer) |
| Parsing | PRS001 | Happens due to fault in the source code of KDS itself | Report the bug. | parser.hpp (Parser) |
| Parsing | PRS002 | Happens when feature is not implemented. | Switch to later version of KDS or report this bug if you are using the latest version. | parser.hpp (Parser) |
| Generation | GEN002 | Happens due to fault in the source code of KDS itself | Report the bug. | generator.hpp (Generator) |