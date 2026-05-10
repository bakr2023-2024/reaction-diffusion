# Reaction Diffusion

A reaction diffusion simulation using Gray-Scott model from [this tutorial](https://karlsims.com/rd.html).

### build
```bash
make main
```

### usage
```bash
./rd [rDA] [rDB] [feed] [kill]
```
all arguments are optional and positional

### arguments
|argument|explanation|
|--------|-----------|
|rDA     |rate of diffusion of A (default: `1.0`)|
|rDB     |rate of diffusion of B (default: `0.5`)|
|feed     |feed rate of A (default: `0.055`)|
|kill     |kill rate of B (default: `0.062`)|