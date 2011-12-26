CXX			=	clang++
CXXFLAGS	=	-march=native -std=c++98 -pedantic -O2 -g
#CXXFLAGS	=	-O2 -ansi -pedantic -W -Wall -Wextra -Wshadow -Wformat -Winit-self -Wunused -Wfloat-equal -Wcast-qual -Wwrite-strings -Winline -Wstack-protector -Wunsafe-loop-optimizations -Wlogical-op -Wjump-misses-init -Wmissing-include-dirs -Wconversion -Wmissing-prototypes -Wmissing-declarations
LDFLAGS		=	-lm -L/usr/tools/lib

SRC			=	find_intersections.cpp dlx.cpp
.PHONY:		clean all all_app

all: $(SRC:%.cpp=%)
	etags *.cpp *.hpp
	echo $? | sed 's/ /\n/g' > .gitignore
	cat .gitignore.base >> .gitignore

clean:
	rm -rf *.o *.so *.a *~ *swp .*swp *.tmp core.* $(SRC:%.cpp=%) *.out

