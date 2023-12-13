**Some tests need root privilege to run!!!**

All tests here use cycles as the unit of time.
To convert cycles to ns in our report, we use the following formula:
```
time = cycles / 2.9e9 * 1e9
```

How to run?:

```bash
# Run all tests
make run
```

if you want to run a specific test, you can cd into the directory. Please refer to the compiling script in `Makefile` for more details.
