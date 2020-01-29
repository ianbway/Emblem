# Ian Braudaway #
# make error 1 # 

func processReal[param]
    :
        # Syntax Error #
        # This should cause problems for the recognizer. There is a close block not a close bracket #
        if [4 > 3;
        :
            print["4 is greater than 3."]
        ;

        print["We are inside of the real processing function."]
    ;

processReal[3.0]