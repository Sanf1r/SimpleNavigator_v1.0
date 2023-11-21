FLAGS=-Wall -Wextra -Werror -std=c++17 -pedantic
FLAGSO3=-O3 -Wall -Wextra -Werror -std=c++17 -pedantic
GTEST=-lgtest -lgtest_main -pthread
COVER=-fprofile-arcs -ftest-coverage
ASAN=#-fsanitize=address

.PHONY: all
all: s21_graph.a s21_graph_algorithms.a s21_mvc.a build

.PHONY: s21_graph.a
s21_graph.a:
	g++ $(FLAGSO3) $(ASAN) -o graph.o -c Model/graph.cc
	ar rc s21_graph.a graph.o
	ranlib s21_graph.a


.PHONY: s21_graph_algorithms.a
s21_graph_algorithms.a:
	g++ $(FLAGSO3) $(ASAN) -o adj_matrix.o -c Model/adj_matrix.cc
	g++ $(FLAGSO3) $(ASAN) -o ant.o -c Model/ant.cc
	g++ $(FLAGSO3) $(ASAN) -o ants_logic.o -c Model/ants_logic.cc
	g++ $(FLAGSO3) $(ASAN) -o graph_algorithms.o -c Model/graph_algorithms.cc
	ar rc s21_graph_algorithms.a graph_algorithms.o ant.o ants_logic.o adj_matrix.o
	ranlib s21_graph_algorithms.a

.PHONY: s21_mvc.a
s21_mvc.a:
	g++ $(FLAGSO3) $(ASAN) -o model.o -c Model/model.cc
	g++ $(FLAGSO3) $(ASAN) -o view.o -c View/view.cc
	ar rc s21_mvc.a model.o view.o
	ranlib s21_mvc.a

.PHONY: build
build:
	g++ $(FLAGSO3) $(ASAN) main.cc -o SimpleNavigator -L. s21_graph.a s21_graph_algorithms.a s21_mvc.a
	rm -f *.a *.o

.PHONY: clean
clean:
	rm -f SimpleNavigator
	rm -f test
	rm -f *.a *.o
	rm -f *.info *.gcda *.gcno *.gcov
	rm -rf coverage
	rm -rf doxygen/html doxygen/latex

.PHONY: tests
tests:
	rm -f *.gcda *.gcno
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) \
	./Tests/tests.cc ./Model/model.cc ./Model/adj_matrix.cc ./Model/ants_logic.cc \
	./Model/ant.cc ./Model/graph_algorithms.cc ./Model/graph.cc -o test
	./test
	geninfo . -b . -o ./coverage.info --no-external --ignore-errors mismatch,mismatch
	genhtml coverage.info -o ./coverage

.PHONY: gcov_report
gcov_report:
	open coverage/index.html

.PHONY: dvi
dvi:
	cd doxygen && doxygen Doxyfile && open html/index.html

.PHONY: dist
dist:
	tar czvf SimpleNavigator.tar.gz ./Model ./View ./Controller ./doxygen/Doxyfile \
	main.cc Makefile

.PHONY: lint
lint:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cc ./Model/*.cc ./View/*.cc \
	./Model/*.h ./View/*.h ./Controller/*.h
	clang-format -n *.cc ./Model/*.cc ./View/*.cc \
	./Model/*.h ./View/*.h ./Controller/*.h
	rm -rf .clang-format

.PHONY: leaks
leaks:
	leaks -atExit -- ./test

.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem \
	--suppress=unusedFunction --std=c++17 --language=c++ *.cc ./Model/*.cc ./View/*.cc \
	./Model/*.h ./View/*.h ./Controller/*.h

