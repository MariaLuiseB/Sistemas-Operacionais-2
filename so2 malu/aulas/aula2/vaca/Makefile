
GIT := https://raw.githubusercontent.com/Mikhail57/cow-interpreter/master/

# vai no servidor e baixar itnterpreter.py 
interpreter.py:
	wget $(GIT)interpreter.py
# vai no servidor e baixar testcow.py 
test.cow:
	wget $(GIT)test.cow
#executar o programa python3 interpreter.py test.cow 
run: interpreter.py test.cow
	python3 interpreter.py test.cow

clean:
	rm -f *.py *.cow 