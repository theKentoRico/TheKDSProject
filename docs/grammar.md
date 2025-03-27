# Assets

A recommended asset is the kds.module file.
It specifies the name of the module and thus the *.ll file generated using `module`
and the name of the source file with `sources`.

# Directives

A directive is defined by an '@'.

## 1. `define` (KDS 3.0.1)

Defines a macro.

### Usage

> @define *x* *y*

where x is the macro name and y is the macro value.

# Keywords

## 1. `errorc` (KDS 1.0.1)

Errorc makes the program return the exit code written after it.

### Usage

> errorc *x*;

where x is an integer

## 2. `value` (KDS 2.0.3)

### Usage
> value x \{*valtype*\} = *y*;

where valtype is a variable type like long ( i64 ), int ( i32 ), char ( i8 ) or bool ( i1 ).