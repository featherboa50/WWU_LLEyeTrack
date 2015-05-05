__author__ = 'mccormk5'

newFile = open( 'EyetrackerDictionary.txt', 'w' )
prev = ""
defNum = 2

with open( 'Spanish.txt', 'r' ) as f:
    for line in f:
        line = line.rstrip()
        vals = line.split("\t")
        if vals[0] != prev :
            newFile.write( "\n" + line )
            defNum = 2
        else:
            newFile.write( ' (' + str(defNum) + ')' + line )
            defNum += 1
        prev = vals[0]
