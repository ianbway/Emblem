Emblem Programming Language
Ian Braudaway

Emblem is a functional programming language. A program will contain definitions of variables and functions, and will end with a statement. 
That statement will be the "main" call to the program. This is optional, as potentially the file will just be function definitions.
The file extension for an Emblem program is ".e".

FUNCTIONS
The keyword to functions is "func". This should be followed by a function name, an open bracket, parameters delimited by bars, and a close bracket.
The body of a function is a block.

LAMBDA
The keyword to anonymous functions is "lambda". These functions need to be returned.

OBJECTS
To use object orientation features, define a function that will be the constructor. The parameters to the function will be the
fields accessible within the object. Internal methods are defined functions nested inside of the constructor. 
Inside of the constructor body block type 'return this' at the end of the constructor.
Instantiate the object by setting the constructor method return to a variable declaration. The fields can be get and set
by using the dot operator on that variable declaration. Declare the getVariable[] method to a variable, then call the variable to 'get'. To 'set' call setVariable[var] from the object you instantiated, ex: obj.setVariable[var].

VARIABLES
The keyword to variables is "var". This should be followed by a variable name, an equal sign, and an expression.

BLOCKS
A block is begins with a colon and ends with a semicolon : ;. 

COMMENTS
In Emblem comments are started and ended with the hash symbol (#).

LOOPS
The keyword to use a loop is "while". This should be followed by an open bracket, an expression, a close bracket, and a block.

CONDITIONS
The keywords for conditions are "if", "else if", and "else". The "if" and "else if" are followed by an expression and a block.

ARRAYS
To instantiate an array, use the built in function "newArray[slotNumber]", with the number of slots passed into the brackets. Set this to a variable to modify.
To get an element from an array, use the built in function "getArray[array|slot]", with the first argument being your created array and the second being 
the index within the array you wish to access.
To set an element inside of an array, use the built in function "setArray[array|slot|value]", with the first argument being your created array,
the second argument being the index within the array you wish to set, and the third argument being what you wish to set the slot to.

COMMAND LINE ARGUMENTS
There are two built-in functions to access command line arguments.
The first is getArgCount[]. It returns an integer that represents the number of command line arguments.
The second is getArg[index]. It returns the command line argument for the provided index.

FILE OPERATIONS
There are four built-in functions dealing with File Input and Output.
The first is openFileForReading[fileName]. It takes a file pointer and begins the process of reading the file stream.
The second is readInteger[filePointer]. It takes a file pointer and reads in an integer from the file, returning it.
The third is atFileEnd[filePointer]. It returns a binary value representing a boolean: true if at the file end, false if not.
The fourth is closeFile[filePointer]. It closes the file stream, reading in a pointer to the file stream to close.

RETURNING
The keyword to return is "return". Follow this by a variable or a type. 

PRINTING
The keyword to print is "print". This should be followed by an open bracket, a list of arguments, and a close bracket.

Example: 
# Example comment #

func math[param1| param2]
    :
        var varSum = param1 + param2 
        var varProduct = param1 * param2 
        var varDifference = param1 - param2 
        var varQuotient = param1 / param2 

        print[varSum] 
        print[varProduct] 
        print[varDifference] 
        print[varQuotient] 
    ;

func listOps[listParam]
    :
        var i = 0 
        var j

        while [i < 10]
        :
            if [getArray[listParam| i] == "first"]
            :
                i = i + 1 
            ;

            else if [getArray[listParam| i] == "last"]
            :
                i = 10 
            ;

            else
            :
            	print[getArray[listParam| i]]
            ;

            i++ 
        ;

        return listParam 
    ;

func compare[]
    :
        if [4 > -3]
        :
            print["4 is greater than -3."]
        ;

        if [[4 + 6] < [5 + 6]]
        :
            print["4 + 6 is less than 5 + 6."]
        ;

        if [4 == 4]
        :
            print["4 is equal to 4."]
        ;

        if [4 <= 4]
        :
            print["4 is less than or equal to 4."]
        ;

        if [4.0 >= 4.0]
        :
            print["4.0 is greater than or equal to 4.0."]
        ;

        if [6 % 3 == 0]
        :
            print["6 cleanly divides by 3."]
        ;

        if [2 != 3]
        :
            print["2 is not equal to 3"]
        ;

        if [1 and 1 == 1]
        :
            print["true logical anded with true is true."]
        ;

        if [1 or 0 == 1]
        :
            print["true logical ored with false is true."]
        ;
    ;

func nest[number]
    :
        func nestFunc[num]
        :
            var sumNums = number + num

            return sumNums
        ;

        return nestFunc
    ;

func main[]
    :
        math[4| 3] 

        compare[]

        var array = newArray[5]
        setArray[array| 0| "first"] 
        setArray[array| 1| 4] 
        setArray[array| 2| 5] 
        setArray[array| 3| 6] 
        setArray[array| 4| "last"] 

        var returnArray = listOps[array] 

        print[returnArray] 

        var nestReturn = nest[2]
        print[nestReturn]
    ;

main[]