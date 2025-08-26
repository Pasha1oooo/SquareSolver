CXXFLAGS= -lm -D _DEBUG -ggdb3  -O0 -Wall -Wextra \
  -Waggressive-loop-optimizations -Wmissing-declarations -Wcast-align -Wcast-qual \
   -Wchar-subscripts -Wconversion -Wempty-body -Wfloat-equal \
    -Wformat-nonliteral -Wformat-security -Wformat-signedness \
    -Wformat=2 -Winline -Wlogical-op -Wopenmp-simd  -Wpacked -Wpointer-arith \
    -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=2 \
    -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wswitch-default \
    -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
    -Wno-missing-field-initializers -Wno-narrowing -Wno-varargs -Wstack-protector -fcheck-new \
    -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
    -Wstack-usage=8192 -pie -fPIE -Werror=vla \
    -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

all: MAIN

run: MAIN
	@./MAIN

# run_unit: MAIN
# 	@./MAIN -t
#
# run_file: MAIN
# 	@./MAIN "/home/pasha/p/PROJECT/coefficients.txt"

MAIN: MAIN.o SOLVER.o
	@g++ ${CXXFLAGS} MAIN.o SOLVER.o -o MAIN

MAIN.o: MAIN.cpp COLORS.h MyAssert.h SOLVER.h
	@g++ ${CXXFLAGS} -c MAIN.cpp -o MAIN.o

SOLVER.o: SOLVER.cpp
	@g++ ${CXXFLAGS} -c SOLVER.cpp -o SOLVER.o

