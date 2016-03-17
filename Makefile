
LIB_TARGET=attiny_utils.a
LIB_OBJECTS=utils.o scheduler.o
LIB_HEADERS=scheduler.h  types.h utils.h

$(LIB_TARGET): $(LIB_OBJECTS)
	$(AR) cr $@ $^

%.o: %.cpp $(LIB_HEADERS)
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm $(LIB_TARGET) $(LIB_OBJECTS)

