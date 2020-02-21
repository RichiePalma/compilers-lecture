#!/usr/bin/python3
#!/usr/bin/pip3
import sys
import re
 
funct = re.compile(r'<.+>:') #https://docs.python.org/3/library/re.html
instr = re.compile(r' \t[a-z]+[0-9]*[a-z]* [a-z]+[0-9]*[a-z]*\s' 
    '| \t[a-z]+[0-9]*[a-z]*\s')
addr = re.compile(r'[0-9a-fA-F]{16} ')
def tokenize(file):
    f=open(file,"r")
    if f.mode == "r":
        text = f.read()
        functions = [i.strip("<.>:") for i in funct.findall(text)]
        instructions = [i.strip() for i in instr.findall(text)]
        address = [i.strip() for i in addr.findall(text)]

        inst_count = [[y,instructions.count(y)] for y in set(instructions)]

        print("Hi, this is the output of the analysis:",
            "\n\tYou have " , len(inst_count)," kind of instructions in this object file:"
        )
        for s in inst_count:
            print("\t\t",s[0], "\t: Executed ", s[1], " times")
        
        print("\tYou have ", len(functions), " functions:")
        for i,j in zip(functions,address):
            print("\t\t",i,"\t: Located at ",j," addr")

tokenize(sys.argv[1])
