# JsonMoppCore
Updated Version of JsonMoppNet.

Forked from: https://github.com/Gurten/HavokShapeListMoppCompiler

## Building

To build this, you will need two dependencies:

JsonCPP: https://github.com/open-source-parsers/jsoncpp

JsonCPP can be built by using the Visual Studio project files generated using the following script:
```
git clone https://github.com/open-source-parsers/jsoncpp.git
cd jsoncpp
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A Win32
```
Run the script from the ``JsonCPP`` folder within the root folder