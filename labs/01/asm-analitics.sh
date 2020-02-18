#!/usr/bin/python3
#!/usr/bin/pip3
import sys
 
def tokenize(file):
    f=open(file,"r")
    if f.mode == "r":
        text = f.read()
        tokens = text.split("\t")
       # print('[%s]' % ', |||'.join(map(str, tokens)))
        count = 1
       for token in tokens:
            if(count % 3 == 0):
                print (token)
            count += 1
            
#print (sys.argv[1])
tokenize(sys.argv[1])
