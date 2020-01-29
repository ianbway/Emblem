# Ian Braudaway #
# make functions test #

func paramFunction[]
:
	var a = 1
	return a
;

func mainFunction[pFunction]
:
	func subFunction[]
	:
		return 1
	;

	print["Printing result of nested function call added to parameter function. Should be 2."]
	print[subFunction[] + pFunction]
;

# 1 + 1 = 2 #
mainFunction[paramFunction[]]