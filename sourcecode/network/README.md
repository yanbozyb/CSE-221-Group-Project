Every test here is in client-server style.

To compile, simply run
```bash
make run
```

Then copy the server binary to the server machine. Run the server binary on the server machine first, then run the client binary on the client machine.

Connection overhead is output in CPU cycles. To convert cycles to ns in our report, we use the following formula:
```
time = cycles / 2.9e9 * 1e9
```

