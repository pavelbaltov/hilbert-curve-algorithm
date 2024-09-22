# Hilbert Curve Algorithms

This project is part of the course Aspects of Low-Level Programming in Game Development at the Technical University of Munich. The goal is to implement and optimize a Hilbert curve generation algorithm using 64-bit ARM assembly (AArch64) and C. The project includes three implementations.

## Documentation

### Project Overview
The Hilbert curve is a space-filling curve that traverses every point in a 2^n x 2^n grid, where n represents the degree of the curve. 

### Key Components
- **Multiple Implementations:**
  - **Pure C Recurisve Implementation:** Standard C implementation using the C17 standard.
  - **ARM Assembly without NEON:** Low-level assembly code for 64-bit ARM architecture (AArch64).
  - **ARM Assembly with NEON Extensions:** Optimized assembly version utilizing NEON extensions for SIMD (Single Instruction, Multiple Data) parallel processing.
- **Output in SVG Format:** The calculated curve points are output as an SVG file for easy visualization.

### Command-Line Options
The program accepts the following command-line options to configure the behavior of the Hilbert curve generation:

- `-V <number>`: Specifies the version of the implementation to use. Options are:
  - `-V 0`: Default version (C implementation)
  - `-V 1`: Assembly implementation without NEON extensions
  - `-V 2`: Assembly implementation with NEON extensions  
  If no `-V` option is provided, the C implementation (`-V 0`) is used by default.

- `-B <number>`: Measures the execution time of the selected implementation. You can optionally specify the number of repetitions:
  - Example: `-B 100` will run the chosen implementation 100 times and output the average runtime.

- `-n <number>`: Specifies the degree of the Hilbert curve to generate. The number n determines the size of the curve, which will generate a grid of 2^n x 2^n points.
  - Example: `-n 4` generates a degree 4 Hilbert curve.

- `-o <filename>`: Specifies the output file where the generated curve will be saved in SVG format.
  - Example: `-o curve.svg` will save the output in a file named curve.svg.

- `-h` or `--help`: Displays a help message summarizing all available options and examples of how to use the program, then exits.

### Example Command-Line Usages
- Generate a Hilbert curve of degree 3 using the C implementation and save it to `output.svg`:
  ```bash
  ./hilbert -n 3 -o output.svg -V 0
  
- Display help information:
  ```bash
  ./hilbert --help

### How to Run
1. **Clone the Repository:**
   ```bash
   git clone <repository_url>
   cd hilbert-curve-project

2. ### Compile the Program:
   ```bash
   make
3. ### Run the Program:
Use the command-line options as described above to generate Hilbert curves, benchmark different implementations, and save results to an SVG file.

### Results and Output
- **SVG Output:** The program outputs an SVG file containing the generated Hilbert curve, connecting the calculated points by lines.
- **Benchmarking Results:** If the `-B` option is used, the runtime for the selected implementation is printed, showing how the performance varies between the C version, ARM assembly without NEON, and NEON-optimized versions.





