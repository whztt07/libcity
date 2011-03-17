COMPILER=g++
COMPILER_FLAGS=-Wall -fPIC -pedantic -g

ARCHIVER=ar
ARCHIVER_FLAGS=rcs

LIB_FILENAME=libcity
TEST_FILENAME=unit_tests

UNITTESTCPP_LIB=../UnitTest++/libUnitTest++.a
UNITTESTCPP_INCLUDE_DIR=../UnitTest++/src/

.PHONY: install uninstall static dynamic clean doc header test

all: static dynamic header

# LIB Object files and sources ##########################

# Geometry package
GEOMETRY_PACKAGE=src/geometry/curve.o \
                 src/geometry/line.o \
                 src/geometry/point.o \
                 src/geometry/vector.o

# Streetgraph package
STREETGRAPH_PACKAGE=src/streetgraph/zone.o \
                    src/streetgraph/intersection.o \
                    src/streetgraph/road.o \
                    src/streetgraph/primaryroad.o \
                    src/streetgraph/secondaryroad.o \
                    src/streetgraph/streetgraph.o \
                    src/streetgraph/rasterroadpattern.o

# LSystem package
LSYSTEM_PACKAGE=src/lsystem/lsystem.o \
                src/lsystem/graphiclsystem.o \
                src/lsystem/roadlsystem.o

LIB_OBJECTS=$(GEOMETRY_PACKAGE) $(STREETGRAPH_PACKAGE) $(LSYSTEM_PACKAGE)

$(LIB_OBJECTS): %.o: %.cpp %.h
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@



# TEST Object files and sources ##########################

# Unit tests
TEST_UNITS=test/testPoint.o   \
           test/testVector.o  \
           test/testLSystem.o \
           test/testGraphicLSystem.o

TEST_MAIN=test/main.o
TEST_OBJECTS=$(TEST_UNITS) $(TEST_MAIN)

$(TEST_OBJECTS): %.o: %.cpp
	$(COMPILER) $(COMPILER_FLAGS) -I$(UNITTESTCPP_INCLUDE_DIR) -c $< -o $@

static: $(LIB_OBJECTS)
	$(ARCHIVER) $(ARCHIVER_FLAGS) $(LIB_FILENAME).a $(LIB_OBJECTS)

dynamic: $(LIB_OBJECTS)
	$(COMPILER) -shared -o $(LIB_FILENAME).so $(LIB_OBJECTS)

header:
	find src/ -name "*.h" -exec cat {} \; >libcity.h

install:
	

uninstall:
	

test: $(TEST_OBJECTS) static
	$(COMPILER) $(COMPILER_FLAGS) -I$(UNITTESTCPP_INCLUDE_DIR) -o $(TEST_FILENAME) $(TEST_OBJECTS) $(UNITTESTCPP_LIB) libcity.a

doc:
	doxygen Doxyfile

clean:
	rm -rf *.o *.so *~
	rm -rf doc
	rm $(LIB_OBJECTS)
	rm $(TEST_OBJECTS)