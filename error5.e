# Ian Braudaway #
# make error 5 #

func errorFunction[]
:
	var val1 = 1
	var val2 = "hello"

	# This is a semantic error. #
	# While legal to multiply two variables, one has a string value and the other an integer value. #
	var val3 = val1 * val2
	print[val3]
;

errorFunction[]

