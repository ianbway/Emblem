# Ian Braudaway #
# make conditionals test #

func conditionalsTest[]
:
	# Testing if #
	if [1 > 0]
	:
		print["Conditional test 1."]
	;

	else if [1 < 0]
	:
		print["Won't make it this far."]
	;

	else
	:
		print["Else."]
	;

	# Testing else if #
	if [1 < 0]
	:
		print["This shouldn't do anything."]
	;

	else if [1 > 0]
	:
		print["Conditional test 2."]
	;

	else
	:
		print["Else."]
	;

	# Testing else #
	if [1 < 0]
	:
		print["This shouldn't do anything."]
	;

	else if [1 < 0]
	:
		print["This shouldn't do anything."]
	;

	else
	:
		print["Conditional test 3."]
	;

;

conditionalsTest[]