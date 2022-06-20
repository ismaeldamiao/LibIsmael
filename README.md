[![Tip Me via PayPal](https://img.shields.io/badge/PayPal-tip%20me-green.svg?logo=paypal)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=D66EM3DGU35EE&source=url)
[![LICENSE](https://img.shields.io/badge/license-MIT-lightgrey.svg)](/LICENSE)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/ismaeldamiao/libismael)
![GitHub Release Date](https://img.shields.io/github/release-date/ismaeldamiao/libismael)
![GitHub last commit](https://img.shields.io/github/last-commit/ismaeldamiao/libismael)

# LibIsmael

Hi I'm Ismael, a Brazilian physician and a C developer. I have written this library to...

This library is a framework to:
- [ ] Linear Algebra
- [x] Random numbers
- [ ] Statistics
- [ ] Data Science

## Table of contents

1. [How to use](#how-to-use)
   1. [Portable way](#portable-way)
   2. [Install](#install)
2. [Data types](#data-types)
3. [Functions](#functions)
   1. [Random Numbers](#random-numbers)
   2. [Statistics](#statistics)
4. [License](#license)
5. [Donations](#donations)

## How to use <a name="how-to-use" />

That are two distinct ways to use the library in your project:
1) Include files (most easy); and 2) Install in your system.

### Portable way <a name="portable-way" />

The most simple and portable way to use the library is following the steps:
1. Download the library, you can use the link <https://github.com/ismaeldamiao/LibIsmael/archive/refs/heads/main.zip>.
2. Then uncompress the file downloaded.
3. Copy the directory `libismael`
to the directory of your project and include the file `libismael/ismael.h`
above and the file `libismael/ismael.c` after the `main` function, like this:

```c
#include "libismael/ismael.h"

int main(int argc, char **argv){
   /* Your code */
}

#include "libismael/ismael.c"
```

If you're using UNIX like system and have `wget` and `unzip` then the first two steps can be done by the following script:

```bash
wget https://github.com/ismaeldamiao/LibIsmael/archive/refs/heads/main.zip
unzip libismael.zip
```

### Install

Another way of use the library is installing it on this computer. To do this you need:

1. Copy the header `ismael.h` to the `include` location of you compiler.
2. Compile the library and copy it to the directory of libraries of your system.
3. Include the header `#include <libismael.h>` in your C project.
4. After compile your project you need to link it with the library.

Im step 3 your code may be look like this:
```c
#include <ismael.h>

int main(int argc, char **argv){
   /* Your code */
}
```

For example, if you're using UNIX like system and have `gcc` then in the first step you can copy the header to the directory `` as 

```bash
cp libismael/ismael.h /usr/include/
```

And the second step can be performed as


```bash
gcc -std=c99 -g -c ismael.c -o libismael.o
ar rs libismael.a libismael.o
mv libismael.a /usr/lib/
```

And the forth step can be made as

```bash
gcc your_code.c -lm -lismael
```

## Data Types <a name="data-types" />

## Functions

### Random Numbers <a name="random-numbers" />

The LibIsmael library provide some functions to generate random numbers,
for pseudo-random number generator the basic use is
`double_variable = ismael.random.GENERATOR(&seed)`
where `GENERATOR` is either `system`, `mt32` or `mt64`.
For correlated random numbers the basic use is
`double_pointer = ismael.random.GENERATOR(correlation_parameter, number_of_random_numbers, seed)`
where `GENERATOR` is either `distance`, `bernoulli` or `fourier`.

* `double ismael.random.system(int *y)`:
Generate a pseuso-random number using the default generator of C,
i.e. `rand` of `stdlib.h`.
The function return a double precision pseudo-random value in [0, 1).
The value `y` in retur point to a integer pseudo-random number in [0, RAND_MAX].
In first call `y` point to any integer to initialize the generator.
* `double ismael.random.mt32(uint32_t *y)`:
Generate a pseuso-random number using the _mersenne twister_ method
with a word of 32 bit.
The function return a double precision pseudo-random value in [0, 1).
The value `y` in retur point to a positive integer
pseudo-random number in [0, UINT32_MAX].
To initialize/reinitialize the generator change
`y` to point any positive integer.
* `double ismael.random.mt64(uint64_t *y)`:
Generate a pseuso-random number using the _mersenne twister_ method
with a word of 64 bit.
The function return a double precision pseudo-random value in [0, 1).
The value `y` in retur point to a positive integer
pseudo-random number in [0, UINT64_MAX].
To initialize/reinitialize the generator change
`y` to point any positive integer.
* `double* ismael.random.distance(double alpha, int N, int seed)`:
Generate a serie of correlated random numbers using
the serie (1).
The function return a array with the correlated random double precision numbers
in [0, 1).
`alpha > 0` is a parameter to control correlations.
`N` is the quantity of correlated numbers.
`seed` is a seed to initialize the generator.
* `double* ismael.random.bernoulli(double alpha, int N, int seed)`:
Generate a serie of correlated random numbers using
the iteration (2).
The function return a array with the correlated random double precision numbers
in [0, 1).
`alpha >= 0` is a parameter to control correlations.
`N` is the quantity of correlated numbers.
`seed` is a seed to initialize the generator.
* `double* ismael.random.fourier(double alpha, int N, int seed)`:
Generate a serie of correlated random numbers using
the serie (3).
The function return a array with the correlated random double precision numbers
in [0, 1).
`alpha >= 0` is a parameter to control correlations.
`N` is the quantity of correlated numbers.
`seed` is a seed to initialize the generator.

<div style="text-align: center;">
<img src="test/test_random.png" width=60% />
</div>

### Statistics

* `double** FDP(double *valor, int N, int particoes)`:
Generate a matrix with the points of a Probability Density Function (PDF) of the array `valor`.
Let be `y = f(x)` the PDF,
the function return a matrix with the values `matrix[0][i]` is the x value of the PDF
and `matrix[1][i]` is the y value of the PDF.
`N` is the size of the array `valor`, this array contains the sample values to compute the PDF.
`particoes` is a "bin" discretization for the computation of the PDF.

## License

This library is licensed in terms of [MIT License](LICENSE) but some free and open source functions with different license is used.

## Donations

You can donate to the creator I. F. F. dos Santos (@ismaeldamiao)
through PayPal by clicking  in the link
[https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=D66EM3DGU35EE&source=url](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=D66EM3DGU35EE&source=url).

Se você possiu conta em algum banco que opera junto ao Banco Central do Brasil
você também pode doar usando o PIX `ismaellxd@gmail.com`.
