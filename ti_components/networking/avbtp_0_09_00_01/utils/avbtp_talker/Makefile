SOURCES := $(wildcard source/*.cpp)
OBJS := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))

CFLAGS := -MMD -O3 -std=c++0x -Wall
INCLUDES := -Iinclude
LFLAGS := -pthread
LIBS := -lavformat

.PHONY: all clean objdir

all: objdir avbtp_talker

objdir:
	@mkdir -p obj

avbtp_talker: $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

obj/%.o: source/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	$(RM) -r obj
	$(RM) avbtp_talker

-include $(OBJS:.o=.d)
