SHELL = cmd.exe

CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -MMD -MP -I. -Imain/application/encryptDecrypt -Imain/application/file_handling -Imain/application/processes

MAIN_TARGET = encrypt_decrypt.exe
CRYPTION_TARGET = cryption.exe

MAIN_SRC = main.cpp \
           main/application/processes/ProcessManagement.cpp \
           main/application/file_handling/IO.cpp \
           main/application/file_handling/readEnv.cpp \
           main/application/encryptDecrypt/Cryption.cpp

CRYPTION_SRC = main/application/encryptDecrypt/CryptionMain.cpp \
               main/application/encryptDecrypt/Cryption.cpp \
               main/application/file_handling/IO.cpp \
               main/application/file_handling/readEnv.cpp

MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
CRYPTION_OBJ = $(CRYPTION_SRC:.cpp=.o)
ALL_OBJ = $(sort $(MAIN_OBJ) $(CRYPTION_OBJ))

all: $(MAIN_TARGET) $(CRYPTION_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CRYPTION_TARGET): $(CRYPTION_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-del /Q /F $(subst /,\,$(ALL_OBJ)) $(subst /,\,$(ALL_OBJ:.o=.d)) $(MAIN_TARGET) $(CRYPTION_TARGET) 2>nul

-include $(ALL_OBJ:.o=.d)

.PHONY: clean all