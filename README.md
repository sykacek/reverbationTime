# Reverberation Time

 Utility for plotting and analyzing reverberation from .wav files.

## Intro

This project was made as tool for analyzing reverabation time for academic purposes. More than single executable program, the project is colection of already existing components connected together. Though there was still need to write compuation engine. Designing project this way allows higher customitization in sense of changing the components of the project.

## Install & run

For detailed instruction please see [instalation guide](docs/INSTALL.md).

## Customization

Before customization, look at 3 stages, how program works:

1. Convert audio to the text format - sox
2. Analyze data and create output data - C++ engine
3. Plot data - gnuplot

You can customize the project for your specific needs. There are many reasons why to replace some components, you may need higher performance, support more audio format or interpret data different way. C++ engine is working with text based files, so all those customizations are avaible

#### How to replace sox

For converting audio you may use different utilities, but to keep compatibility with C++ engine you need to pass data in specific format. Only accepted format is tab-separated text files.
```
  time 1    val 1
  time 2    val 2
  time 3    val 3
  time 4    val 4
  ...       ...
  time n    val n
```

#### How to replace gnuplot

Again, output files from C++ engine are in the same format as input files.
```
  time 1    val 1
  time 2    val 2
  time 3    val 3
  time 4    val 4
  ...       ...
  time n    val n
```

### Tests

Core C++ engine function were unit testes using [Google Tests](https://github.com/google/googletest). Source files for unit testing are located in `test` directory.For further information about unit testing (and results) please refer to [testing guide](docs/TESTING.md).
