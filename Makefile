CC = g++
CXXFLAGS = -O2 -std=c++20 -I include
LDFLAGS = -L lib

BINDIR = bin
SRCDIR = src
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

APP = app

all: prepare $(APP)

prepare:
	mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/*

help:
	@echo Usage:
	echo make - build application
	echo make clean - remove build artifacts
	echo make help - show help

$(APP): $(OBJ)
	$(CC) $(OBJ) -o $(BINDIR)/$(APP) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< $(CXXFLAGS) -o $@
