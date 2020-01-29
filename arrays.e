# Ian Braudaway #
# make array test #

func arrayTest[]
:
	print["Creating new array with 5 slots."]
	var exampleArray = newArray[5]

	print["Getting value from first slot in array and displaying it. Should not be anything."]
	var one = getArray[exampleArray| 0]
	print[one]

	print["Setting first slot in array to the value: 11. Displaying 11."]
	setArray[exampleArray| 0| 11]
	print[getArray[exampleArray| 0]]

	print["Setting remaining 4 slots. They will contain values 22, 33, 44, 55. They will then be displayed."]
	setArray[exampleArray| 1| 22]
	print[getArray[exampleArray| 1]]
	setArray[exampleArray| 2| 33]
	print[getArray[exampleArray| 2]]
	setArray[exampleArray| 3| 44]
	print[getArray[exampleArray| 3]]
	setArray[exampleArray| 4| 55]
	print[getArray[exampleArray| 4]]
;

arrayTest[]