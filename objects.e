# Ian Braudaway #
# make objects test #

func object[value| next]
:
	func getValue[]
	:
		return value
	;

	func setValue[v]
	:
		value = v
	;

	return this
;

func main[]
:
	var n = object[5| 78]

	# Get Value. Should be 5. #
	print["getValue: 'value' field is:"]
	var value = n.getValue
	print[value[]]
	print[""]

	# Set Value. Should be 963. #
	print["setValue: 'value' field set to 963."]
	var setter = n.setValue
	setter[963]
	print[""]

	# Get Value. Should be 963. #
	print["getValue: 'value' field is:"]
	var value = n.getValue
	print[value[]]
;

main[]
