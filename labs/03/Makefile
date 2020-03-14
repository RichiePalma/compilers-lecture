all:
	python3 code_generator.py > example.ac
	flex lexic_analyzer.l
	gcc lex.yy.c -o lexical_scan -lfl

clean:
	rm -rf example.ac
	rm -rf lexical_scan