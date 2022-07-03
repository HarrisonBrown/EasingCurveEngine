# Easing Curve Engine

## Usage
1. Run bin\x64\Release\EasingCurveEngine.exe. Other configurations are built if needed.
    * A console will be presented to you with the message "Please enter an input filepath: "
2. Enter a full filepath containing input as specified in the task description.
    * Some pre-written test files are provided in the input directory, located at the root of the project

## Compilation
If needed, compile using msbuild either within the Visual Studio IDE or by running 
> `msbuild /property:Configuration=Release src\EasingCurveEngine.vcxproj`

---
## Overall Program Structure
* The program consists of a Main function, which starts off by asking the user to input a filepath.
*  Given a correct filepath, the file is broken up into individual lines, which are stored in a vector of std::strings.
*  These lines are passed to a parsing function which validates each string in turn. Valid input lines are parsed into commands, represented by a pair of strings; the first being a valid command name and the second being the value (still as a string);
   *  This parsing function also sets a return code enum representing the state of the command passed in (i.e. curve definition, query, or a variety of errors)
      *  A future improvement could be to change this enum for a bitwise representation of errors, so multiple can be easily stored and acted upon.
*  Each command is iterated over, using the return code to determine what to do
   *  Curve definitions are composed into a struct representing the curve parameters, which is used to create the appropriate curve object. 
      *  These curve classes inherit from a parent 'Curve' class, which provides a public 'Create' factory method which will return a pointer to an instance of the correct subclass.
   *  Queries are used to query the currently loaded curve, if one is loaded