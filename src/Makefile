WWW = -std=c++17 -Wall -Werror -Wextra -lstdc++ -g
LFLAGS=-fprofile-arcs -ftest-coverage
LIBS=-lgtest -lgmock -pthread
OS=$(shell uname -s)

all: clean test


rebuild: clean all 

test: clean containers.a
	gcc $(WWW) test.cpp containers.a -o test $(LIBS)
	./test

gcov_report: clean_test
	gcc $(WWW) --coverage test.cpp s21_*.cpp -o test $(LIBS)
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

containers.a: build_containers

build_containers:
	gcc -lstdc++ -c s21_*.cpp
	ar rcs containers.a s21_*.o
	ranlib containers.a

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

install_valgrind:
	brew install --HEAD LouisBrunner/valgrind/valgrind

install_cpch:
	brew install cppcheck

git: clean
	git add .
	git commit -m'finish'
	git push origin develop

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report

clean: clean_lib clean_test clean_obj
