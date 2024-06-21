BIN_DIR = bin
CXX = g++
CPPFLAGS = -g -Wall

OBJS = $(BIN_DIR)/arithmetic.o $(BIN_DIR)/Endstatement.o $(BIN_DIR)/GoSubStatement.o \
	$(BIN_DIR)/GoToStatement.o $(BIN_DIR)/IfStatement.o $(BIN_DIR)/Interpreter.o \
	$(BIN_DIR)/LetStatement.o $(BIN_DIR)/PrintAllStatement.o $(BIN_DIR)/PrintStatement.o \
	$(BIN_DIR)/ProgramState.o $(BIN_DIR)/ReturnStatement.o

all: $(BIN_DIR)/.dirstamp Interpreter

Interpreter: $(OBJS)
	$(CXX) $(CPPFLAGS) $(OBJS) -o $@

$(BIN_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp