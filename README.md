# mulle-vararg

A variable argument passing scheme used written in C (C11).

## How it works

### Remember the C argument promotion rules

1. char and short to int/unsigned int
2. float to double

### The arguments are layed out struct-like

A method like `stringWithFormat:(NSString *) format, ...`
which is called like this

```
[NSString stringWithFormat:@"%d %f %lld", (char) 'x', (float) 0.2, 1848LL];
```

could access the arguments as if they were embedded in a struct like this

```
struct
{
   NSString  *format;
   struct
   {
      int         value1;
      double      value2;
      long long   value3;
   } varargs;
} _param;
```

But accessing those values, that's what mulle-vararg does for you.
