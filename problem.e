# Ian Braudaway #
# make problem, non-AVL #
# summing integers found in file #

func summation[file]
:
	var int = readInteger[file]
	var sum = int

	while[atFileEnd[file] != 1]
	:
		int = readInteger[file]
		sum = sum + int
	;

	# Sum of integers in my 'integers' file is 394. #
	print["Sum is: "]
	print[sum]
;

func main[]
:
    var fp = openFileForReading[getArg[2]]
    summation[fp]
    closeFile[fp]
    return 0
;

main[]
