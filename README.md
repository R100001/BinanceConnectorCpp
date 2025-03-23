
# Download and Install Miniconda

https://docs.conda.io/projects/conda/en/stable/user-guide/install/linux.html

# Install CMake

sudo apt-get install cmake

# Setup a Conda env

conda create -n binanceconnectorcpp python
pip install conan

# CONAN SETUP

conan profile detect --name binanceconnectorcpp

Change compiler.cppstd=gnuXX to compiler.cppstd=gnu23 from ~/.conan2/profiles/binanceconnectorcpp

Run only the first time: 
conan install . --output-folder=build -s build_type=Debug --build=missing --profile:host binanceconnectorcpp --profile:build=binanceconnectorcpp